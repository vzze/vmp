#include <ui.hh>

bool vmp::ui::key_callback(const char key) {
    if(screen_is_too_small) return true;

    switch(key) {
        case 'q': return false; break;
        case 'w': w(); break;
        case 'a': a(); break;
        case 's': s(); break;
        case 'd': d(); break;
        case 'n': n(); break;
        case 'm': m(); break;

        default: break;
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
        draw_player_info();

        set_zone(ZONE::QUEUE_TITLE);
    }

    return true;
}
