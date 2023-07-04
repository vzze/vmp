#include <ui.hh>

bool vmp::ui::key_callback(const char key) {
    switch(key) {
        case 'q': return false; break;
    }

    return true;
}

bool vmp::ui::resize_callback(const coord coords) {
    if(current_dimensions == coords)
        return true;

    current_dimensions = coords;
    draw_borders();

    return true;
}
