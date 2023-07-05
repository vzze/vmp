#include <ui.hh>

bool vmp::ui::key_callback(const char key) {
    if(screen_is_too_small) return true;

    switch(key) {
        case 'q': return false; break;
        case 'w':
            switch(zones.current_zone) {
                case ZONE::QUEUE_TITLE   : return true; break;
                case ZONE::UNSORTED_TITLE: set_zone(ZONE::QUEUE_TITLE); break;
                default: return true; break;
            }
        break;

        case 's':
            switch(zones.current_zone) {
                case ZONE::UNSORTED_TITLE: return true; break;
                case ZONE::QUEUE_TITLE   : set_zone(ZONE::UNSORTED_TITLE); break;
                default: return true; break;
            }
        break;

        case 'n':
            switch(zones.current_zone) {
                case ZONE::QUEUE_TITLE   : queues_prev_page(); break;
                case ZONE::UNSORTED_TITLE: unsorted_prev_page(); break;

                default: return true; break;
            }
        break;
        case 'm':
            switch(zones.current_zone) {
                case ZONE::QUEUE_TITLE   : queues_next_page(); break;
                case ZONE::UNSORTED_TITLE: unsorted_next_page(); break;

                default: return true; break;
            }
        break;
        default: return true; break;
    }

    return true;
}

bool vmp::ui::resize_callback(const coord coords) {
    if(current_dimensions == coords)
        return true;

    current_dimensions = coords;

    if(current_dimensions.y <= sidebar_stopping_point + 1 || current_dimensions.x <= sidebar_width + ROW_START) {
        screen_is_too_small = true;

        erase_in_display(DISPLAY::ENTIRE_DISPLAY);

        print_at_pos({ 1, 1 }, "Please make terminal bigger!");
    } else {
        screen_is_too_small = false;

        draw_borders();
        draw_queues();
        draw_unsorted_songs();

        set_zone(ZONE::QUEUE_TITLE);
    }

    return true;
}
