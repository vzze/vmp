#include <ui.hh>

bool vmp::ui::w() {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE   : return true; break;
        case ZONE::UNSORTED_TITLE: set_zone(ZONE::QUEUE_TITLE); break;

        default:
            button_up();

            if(current_zone == ZONE::QUEUE_LIST)
                draw_main_list(zones[current_zone].current().id);
        break;
    }

    return true;
}

bool vmp::ui::a() {
    switch(current_zone) {
        case ZONE::QUEUE_LIST   : set_zone(ZONE::QUEUE_TITLE); break;
        case ZONE::UNSORTED_LIST: set_zone(ZONE::UNSORTED_TITLE); break;
        case ZONE::MAIN_LIST    : set_zone(ZONE::QUEUE_LIST); break;

        default: return true; break;
    }

    return true;
}

bool vmp::ui::s() {
    switch(current_zone) {
        case ZONE::UNSORTED_TITLE: return true; break;
        case ZONE::QUEUE_TITLE   : set_zone(ZONE::UNSORTED_TITLE); break;

        default:
            button_down();

            if(current_zone == ZONE::QUEUE_LIST)
                draw_main_list(zones[current_zone].current().id);
        break;
    }

    return true;
}

bool vmp::ui::d() {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE:
            if(!zones[ZONE::QUEUE_LIST].buttons.empty()) {
                set_zone(ZONE::QUEUE_LIST);
                draw_main_list(zones[current_zone].current().id);
            }
        break;
        case ZONE::UNSORTED_TITLE:
            if(!zones[ZONE::UNSORTED_LIST].buttons.empty())
                set_zone(ZONE::UNSORTED_LIST);
        break;
        case ZONE::QUEUE_LIST:
            if(!zones[ZONE::MAIN_LIST].buttons.empty())
                set_zone(ZONE::MAIN_LIST);
        break;

        default: return true; break;
    }

    return true;
}

bool vmp::ui::n() {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE   : queues_prev_page(); break;
        case ZONE::UNSORTED_TITLE: unsorted_prev_page(); break;
        case ZONE::QUEUE_LIST:
            main_prev_page(zones[current_zone].current().id);
        break;

        default: return true; break;
    }

    return true;
}

bool vmp::ui::m() {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE   : queues_next_page(); break;
        case ZONE::UNSORTED_TITLE: unsorted_next_page(); break;
        case ZONE::QUEUE_LIST:
            main_next_page(zones[current_zone].current().id);
        break;

        default: return true; break;
    }

    return true;
}
