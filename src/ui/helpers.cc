#include <ui.hh>

std::wstring vmp::ui::format_sidebar_row(std::wstring name) const {
    static constexpr std::wstring_view filler = L"...";

    if(name.length() >= sidebar_width - SIDEBAR_ROW_START) {
        name.resize(sidebar_width - SIDEBAR_ROW_START - filler.size());
        name += filler;
    } else {
        name.resize(sidebar_width - SIDEBAR_ROW_START, L' ');
    }

    return name;
}

void vmp::ui::set_cursor_pos(const coord coords) {
    util::write_console(std::format("\x1b[{};{}H", coords.y, coords.x));
}

void vmp::ui::print_at_pos(const coord coords, const std::wstring_view txt) {
    util::write_wconsole(std::format(L"\x1b[{};{}H{}", coords.y, coords.x, txt));
}

void vmp::ui::print_at_pos(const coord coords, const std::string_view txt) {
    util::write_console(std::format("\x1b[{};{}H{}", coords.y, coords.x, txt));
}

void vmp::ui::print_at_pos(const coord coords, const char txt) {
    util::write_console(std::format("\x1b[{};{}H{}", coords.y, coords.x, txt));
}

void vmp::ui::insert_char(cu32 count) {
    util::write_console(std::format("\x1b[{}@", count));
}

void vmp::ui::delete_char(cu32 count) {
    util::write_console(std::format("\x1b[{}P", count));
}

void vmp::ui::erase_char(cu32 count) {
    util::write_console(std::format("\x1b[{}X", count));
}

void vmp::ui::insert_line(cu32 count) {
    util::write_console(std::format("\x1b[{}L", count));
}

void vmp::ui::delete_line(cu32 count) {
    util::write_console(std::format("\x1b[{}M", count));
}

void vmp::ui::erase_in_display(const display_opts mode) {
    util::write_console(std::format("\x1b[{}J", static_cast<u32>(mode)));
}

void vmp::ui::erase_in_line(const line_opts mode) {
    util::write_console(std::format("\x1b[{}K", static_cast<u32>(mode)));
}

void vmp::ui::dec_mode() {
    util::write_console("\x1b(0");
}

void vmp::ui::ascii_mode() {
    util::write_console("\x1b(B");
}
