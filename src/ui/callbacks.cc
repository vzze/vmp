#include <ui.hh>

bool vmp::ui::notify_alive_callback() {
    draw_player_status();

    return handler.refresh();
}

bool vmp::ui::key_callback(const char key) {
    if(screen_is_too_small) return true;

    switch(key) {
        case actions.quit       : return  false; break;

        case actions.up         : up         (); break;
        case actions.left       : left       (); break;
        case actions.down       : down       (); break;
        case actions.right      : right      (); break;

        case actions.scroll_up  : scroll_up  (); break;
        case actions.scroll_down: scroll_down(); break;

        case actions.play       : play       (); break;
        case actions.volume_up  : volume_up  (); break;
        case actions.volume_down: volume_down(); break;

        case actions.toggle_pause_resume:
            toggle_pause_resume();
        break;

        default: break;
    }

    return handler.refresh();
}

bool vmp::ui::resize_callback(const coord coords) {
    if(current_dimensions == coords)
        return true;

    current_dimensions = coords;

    if(current_dimensions.row <= sidebar_stopping_point + 1 || current_dimensions.column <= sidebar_width + ROW_START) {
        screen_is_too_small = true;

        handler.erase_in_display(console::DISPLAY::ENTIRE_DISPLAY);

        handler.print_at_pos({ 1, 1 }, "Please make terminal bigger!");
    } else {
        screen_is_too_small = false;

        draw_borders();
        draw_queues();
        draw_unsorted_songs();
        draw_player_info();
        draw_player_status();
        draw_player_volume();

        set_zone(ZONE::QUEUE_TITLE);
    }

    return handler.refresh();
}
