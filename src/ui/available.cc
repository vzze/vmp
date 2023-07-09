#include <ui.hh>

bool vmp::ui::queues_prev_available() const { return queues_offset != 0; }
bool vmp::ui::unsorted_prev_available() const { return unsorted_songs_offset != 0; }
bool vmp::ui::main_prev_available(cu32 queue_id) const { return instance.queues[queue_id].draw_offset != 0; }

bool vmp::ui::queues_next_available() const {
    return
        queues_offset + sidebar_stopping_point - TOP_BAR.y - 2 <
        instance.queues.size();
}

bool vmp::ui::unsorted_next_available() const {
    return
        unsorted_songs_offset + current_dimensions.y - sidebar_stopping_point - 2 <
        instance.unsorted.songs.size();
}

bool vmp::ui::main_next_available(cu32 queue_id) const {
    return instance.queues[queue_id].draw_offset + current_dimensions.y - TOP_BAR.y - 1 <
        instance.queues[queue_id].songs.size();
}

char vmp::ui::up_available() const {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE: return ' '; break;

        case ZONE::QUEUE_LIST:
        case ZONE::UNSORTED_LIST:
        case ZONE::MAIN_LIST:
            if(zones[current_zone].buttons.size() == 1) return ' ';
            else return keys.up;
        break;

        default: return keys.up; break;
    }
}

char vmp::ui::left_available() const {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE:
        case ZONE::UNSORTED_TITLE:
            return ' ';
        break;

        default: return keys.left; break;
    }
}

char vmp::ui::down_available() const {
    switch(current_zone) {
        case ZONE::UNSORTED_TITLE: return ' '; break;

        case ZONE::QUEUE_LIST:
        case ZONE::UNSORTED_LIST:
        case ZONE::MAIN_LIST:
            if(zones[current_zone].buttons.size() == 1) return ' ';
            else return keys.down;
        break;

        default: return keys.down; break;
    }
}

char vmp::ui::right_available() const {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE:
            if(zones[ZONE::QUEUE_LIST].buttons.empty()) return ' ';
            else return keys.right;
        break;

        case ZONE::QUEUE_LIST:
            if(zones[ZONE::MAIN_LIST].buttons.empty()) return ' ';
            else return keys.right;
        break;

        case ZONE::UNSORTED_TITLE:
            if(zones[ZONE::UNSORTED_LIST].buttons.empty()) return ' ';
            else return keys.right;
        break;

        default: return ' '; break;
    }
}

char vmp::ui::scroll_up_available() const {
    bool n_av{false};

    switch(current_zone) {
        case ZONE::QUEUE_TITLE   : n_av = queues_prev_available(); break;
        case ZONE::QUEUE_LIST    : n_av = main_prev_available(zones[current_zone].current().id); break;
        case ZONE::UNSORTED_TITLE: n_av = unsorted_prev_available(); break;

        default: return ' '; break;
    }

    if(n_av) return keys.scroll_up;
    else return ' ';
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

        default: return ' '; break;
    }

    if(m_av) return keys.scroll_down;
    else return ' ';
}

void vmp::ui::draw_available_moves() const {
    std::string available;

    available.push_back(up_available());
    available.push_back(left_available());
    available.push_back(down_available());
    available.push_back(right_available());
    available.push_back(scroll_up_available());
    available.push_back(scroll_down_available());

    print_at_pos({ 1, 1 }, available);

    dec_mode();

    static constexpr auto one_down = coord{
        AVAILABLE_MOVES_CUTOFF.x,
        AVAILABLE_MOVES_CUTOFF.y + 1
    };

    print_at_pos(AVAILABLE_MOVES_CUTOFF, dec_chars["ve"]);
    print_at_pos(one_down, dec_chars["t3"]);

    ascii_mode();
}
