#include <ui.hh>

void vmp::ui::draw_borders() {
    dec_mode();

    erase_in_display(2);

    print_at_pos(2, 1, std::string(current_dimensions.x, dec_chars["ho"]));

    print_at_pos(2, sidebar_width, dec_chars["t4"]);

    for(std::uint32_t x = 1; x < sidebar_width; ++x)
        print_at_pos(sidebar_stopping_point, x, dec_chars["ho"]);

    for(std::uint32_t y = 3; y <= current_dimensions.y; ++y)
        print_at_pos(y, sidebar_width, dec_chars["ve"]);

    print_at_pos(sidebar_stopping_point, sidebar_width, dec_chars["t2"]);

    print_at_pos(2, 5, dec_chars["t3"]);
    print_at_pos(1, 5, dec_chars["ve"]);

    ascii_mode();
}
