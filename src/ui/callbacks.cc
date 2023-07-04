#include <ui.hh>

bool vmp::ui::key_callback(const char key) {
    switch(key) {
        case 'q': return false; break;
        case 'n': unsorted_prev_page(); break;
        case 'm': unsorted_next_page(); break;
        default: return true; break;
    }

    return true;
}

bool vmp::ui::resize_callback(const coord coords) {
    if(current_dimensions == coords)
        return true;

    current_dimensions = coords;
    draw_borders();
    draw_queues();
    draw_unsorted_songs();

    return true;
}
