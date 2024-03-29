#include <ui.hh>

bool vmp::ui::queues_prev_available() const { return queues_offset != 0; }
bool vmp::ui::unsorted_prev_available() const { return unsorted_songs_offset != 0; }
bool vmp::ui::main_prev_available(cu32 queue_id) const { return instance.queues[queue_id].draw_offset != 0; }

bool vmp::ui::queues_next_available() const {
    return
        queues_offset + sidebar_stopping_point - TOP_BAR.row - 2 <
        instance.queues.size();
}

bool vmp::ui::unsorted_next_available() const {
    return
        unsorted_songs_offset + current_dimensions.row - sidebar_stopping_point - 2 <
        instance.unsorted.songs.size();
}

bool vmp::ui::main_next_available(cu32 queue_id) const {
    return instance.queues[queue_id].draw_offset + current_dimensions.row - TOP_BAR.row - 1 <
        instance.queues[queue_id].songs.size();
}

char vmp::ui::up_available() const {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE: return actions.unavailable; break;

        case ZONE::QUEUE_LIST:
        case ZONE::UNSORTED_LIST:
        case ZONE::MAIN_LIST:
            if(zones[current_zone].buttons.size() == 1) return actions.unavailable;
            else return actions.up;
        break;

        default: return actions.up; break;
    }
}

char vmp::ui::left_available() const {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE:
        case ZONE::UNSORTED_TITLE:
            return actions.unavailable;
        break;

        default: return actions.left; break;
    }
}

char vmp::ui::down_available() const {
    switch(current_zone) {
        case ZONE::UNSORTED_TITLE: return actions.unavailable; break;

        case ZONE::QUEUE_LIST:
        case ZONE::UNSORTED_LIST:
        case ZONE::MAIN_LIST:
            if(zones[current_zone].buttons.size() == 1) return actions.unavailable;
            else return actions.down;
        break;

        default: return actions.down; break;
    }
}

char vmp::ui::right_available() const {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE:
            if(zones[ZONE::QUEUE_LIST].buttons.empty()) return actions.unavailable;
            else return actions.right;
        break;

        case ZONE::QUEUE_LIST:
            if(zones[ZONE::MAIN_LIST].buttons.empty()) return actions.unavailable;
            else return actions.right;
        break;

        case ZONE::UNSORTED_TITLE:
            if(zones[ZONE::UNSORTED_LIST].buttons.empty()) return actions.unavailable;
            else return actions.right;
        break;

        default: return actions.unavailable; break;
    }
}

char vmp::ui::scroll_up_available() const {
    bool n_av{false};

    switch(current_zone) {
        case ZONE::QUEUE_TITLE   : n_av = queues_prev_available(); break;
        case ZONE::QUEUE_LIST    : n_av = main_prev_available(zones[current_zone].current().id); break;
        case ZONE::UNSORTED_TITLE: n_av = unsorted_prev_available(); break;

        default: return actions.unavailable; break;
    }

    if(n_av) return actions.scroll_up;
    else return actions.unavailable;
}

char vmp::ui::scroll_down_available() const {
    bool m_av{false};

    switch(current_zone) {
        case ZONE::QUEUE_TITLE:
            m_av = queues_next_available();
        break;
        case ZONE::QUEUE_LIST:
            m_av = main_next_available(zones[current_zone].current().id);
        break;
        case ZONE::UNSORTED_TITLE:
            m_av = unsorted_next_available();
        break;

        default: return actions.unavailable; break;
    }

    if(m_av) return actions.scroll_down;
    else return actions.unavailable;
}

void vmp::ui::draw_available_moves() {
    std::string available;

    available.push_back(up_available());
    available.push_back(left_available());
    available.push_back(down_available());
    available.push_back(right_available());
    available.push_back(scroll_up_available());
    available.push_back(scroll_down_available());

    handler.print_at_pos({ 1, 1 }, available);

    handler.dec_mode();

    static constexpr auto one_down = coord{
        AVAILABLE_MOVES_CUTOFF.column,
        AVAILABLE_MOVES_CUTOFF.row + 1
    };

    handler.print_at_pos(AVAILABLE_MOVES_CUTOFF, console::DEC["ve"]);
    handler.print_at_pos(one_down, console::DEC["t3"]);

    handler.ascii_mode();
}
