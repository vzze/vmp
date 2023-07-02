#include <ui.hh>

void vmp::ui::set_cursor_pos(std::uint32_t line, std::uint32_t column) {
    std::cout << std::format("\x1b[{};{}H", line, column);
}

void vmp::ui::print_at_pos(std::uint32_t line, std::uint32_t column, const std::wstring_view txt) {
    std::wcout << std::format(L"\x1b[{};{}H{}", line, column, txt);
}

void vmp::ui::print_at_pos(std::uint32_t line, std::uint32_t column, const std::string_view txt) {
    std::cout << std::format("\x1b[{};{}H{}", line, column, txt);
}

void vmp::ui::print_at_pos(std::uint32_t line, std::uint32_t column, const char txt) {
    std::cout << std::format("\x1b[{};{}H{}", line, column, txt);
}

void vmp::ui::insert_char(std::uint32_t n) {
    std::cout << std::format("\x1b[{}@", n);
}

void vmp::ui::delete_char(std::uint32_t n) {
    std::cout << std::format("\x1b[{}P", n);
}

void vmp::ui::erase_char(std::uint32_t n) {
    std::cout << std::format("\x1b[{}X", n);
}

void vmp::ui::insert_line(std::uint32_t n) {
    std::cout << std::format("\x1b[{}L", n);
}

void vmp::ui::delete_line(std::uint32_t n) {
    std::cout << std::format("\x1b[{}M", n);
}

void vmp::ui::erase_in_display(std::uint32_t mode) {
    std::cout << std::format("\x1b[{}J", mode);
}

void vmp::ui::erase_in_line(std::uint32_t mode) {
    std::cout << std::format("\x1b[{}K", mode);
}

void vmp::ui::dec_mode() {
    std::cout << "\x1b(0";
}

void vmp::ui::ascii_mode() {
    std::cout << "\x1b(B";
}

void vmp::ui::init(player & current_player) {
    instance = &current_player;

    create_buttons();

#ifdef VMP_DEBUG
    std::cout << current_button->line_hl << ' ' << current_button->column_hl << '\n';
#endif

    std::cout << "\x1b[?1049h";
    std::cout << "\x1b[?25l";
}

void vmp::ui::exit() {
    std::cout << "\x1b[?1049l";
    std::cout << "\x1b[!p";
    std::cout << "\x1b[?25h";
}
