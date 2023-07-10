#include <ui.hh>

void vmp::ui::draw_borders() {
    handler.dec_mode();

    handler.erase_in_display(console::DISPLAY::ENTIRE_DISPLAY);

    handler.print_at_pos(TOP_BAR, std::string(current_dimensions.column, console::DEC["ho"]));

    handler.print_at_pos({ sidebar_width, TOP_BAR.row }, console::DEC["t4"]);

    handler.print_at_pos({ 1, sidebar_stopping_point }, std::string(sidebar_width - 1, console::DEC["ho"]));

    for(u32 line = TOP_BAR.row + 1; line <= current_dimensions.row; ++line)
        handler.print_at_pos({ sidebar_width, line }, console::DEC["ve"]);

    handler.print_at_pos({ sidebar_width, sidebar_stopping_point }, console::DEC["t2"]);

    handler.ascii_mode();
}
