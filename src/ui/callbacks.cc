#include <ui.hh>

vmp::con::coord vmp::ui::current_dimensions{0, 0};
std::uint32_t vmp::ui::sidebar_width{28};
std::uint32_t vmp::ui::sidebar_stopping_point{12};
vmp::player * vmp::ui::instance{nullptr};
std::shared_ptr<vmp::ui::button> vmp::ui::current_button;

bool vmp::ui::on_keypress(char key) {
    switch(key) {
        case 'q': return false; break;
        case 'w': check_w(current_button); break;
        case 'a': check_a(current_button); break;
        case 's': check_s(current_button); break;
        case 'd': check_d(current_button); break;
    }

    return true;
}

bool vmp::ui::on_resize(vmp::con::coord coord) {
    if(current_dimensions != coord) {
        current_dimensions = coord;

        draw_borders();
        draw_queue_list();
        draw_unsorted_list();
        current_button->add_highlight();
    }

    return true;
}
