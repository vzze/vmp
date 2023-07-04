#include <ui.hh>

void vmp::ui::draw_borders() {
    dec_mode();

    erase_in_display(display_opts::ENTIRE_DISPLAY);

    print_at_pos(TOP_BAR, std::string(current_dimensions.x, dec_chars["ho"]));

    print_at_pos({ sidebar_width, TOP_BAR.y }, dec_chars["t4"]);

    print_at_pos({ 1, sidebar_stopping_point }, std::string(sidebar_width - 1, dec_chars["ho"]));

    for(u32 line = TOP_BAR.y + 1; line <= current_dimensions.y; ++line)
        print_at_pos({ sidebar_width, line }, dec_chars["ve"]);

    print_at_pos({ sidebar_width, sidebar_stopping_point }, dec_chars["t2"]);

    ascii_mode();
}
