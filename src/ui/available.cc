#include <ui.hh>

char vmp::ui::w_available() const {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE: return ' '; break;

        case ZONE::QUEUE_LIST:
        case ZONE::UNSORTED_LIST:
        case ZONE::MAIN_LIST:
            if(zones[current_zone].buttons.size() == 1) return ' ';
            else return 'w';
        break;

        default: return 'w'; break;
    }
}

char vmp::ui::a_available() const {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE:
        case ZONE::UNSORTED_TITLE:
            return ' ';
        break;

        default: return 'a'; break;
    }
}

char vmp::ui::s_available() const {
    switch(current_zone) {
        case ZONE::UNSORTED_TITLE: return ' '; break;

        case ZONE::QUEUE_LIST:
        case ZONE::UNSORTED_LIST:
        case ZONE::MAIN_LIST:
            if(zones[current_zone].buttons.size() == 1) return ' ';
            else return 's';
        break;

        default: return 's'; break;
    }
}

char vmp::ui::d_available() const {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE:
            if(zones[ZONE::QUEUE_LIST].buttons.empty()) return ' ';
            else return 'd';
        break;

        case ZONE::QUEUE_LIST:
            if(zones[ZONE::MAIN_LIST].buttons.empty()) return ' ';
            else return 'd';
        break;

        case ZONE::UNSORTED_TITLE:
            if(zones[ZONE::UNSORTED_LIST].buttons.empty()) return ' ';
            else return 'd';
        break;

        default: return ' '; break;
    }
}

char vmp::ui::n_available() const {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE:
        case ZONE::QUEUE_LIST:
        case ZONE::UNSORTED_TITLE:
            return 'n';
        break;

        default: return ' '; break;
    }
}

char vmp::ui::m_available() const {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE:
        case ZONE::QUEUE_LIST:
        case ZONE::UNSORTED_TITLE:
            return 'm';
        break;

        default: return ' '; break;
    }
}

void vmp::ui::draw_available_moves() const {
    std::string available;

    available.push_back(w_available());
    available.push_back(a_available());
    available.push_back(s_available());
    available.push_back(d_available());
    available.push_back(n_available());
    available.push_back(m_available());

    print_at_pos({ 1, 1 }, available);
}
