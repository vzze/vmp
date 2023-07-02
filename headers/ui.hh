#ifndef UI_HH
#define UI_HH

#include <string_view>
#include <iostream>
#include <variant>
#include <cstdint>
#include <memory>
#include <format>

#include <console.hh>
#include <player.hh>
#include <util.hh>

namespace vmp::ui {
    extern vmp::con::coord current_dimensions;
    extern std::uint32_t sidebar_width;
    extern std::uint32_t sidebar_stopping_point;
    extern player * instance;

    struct button {
        std::shared_ptr<button> w, a, s, d;
        std::uint32_t line_hl, column_hl;

        button(
            std::uint32_t line,
            std::uint32_t col,
            std::shared_ptr<button> _w = nullptr,
            std::shared_ptr<button> _a = nullptr,
            std::shared_ptr<button> _s = nullptr,
            std::shared_ptr<button> _d = nullptr
        ) : w{_w}, a{_a}, s{_s}, d{_d}, line_hl{line}, column_hl{col} {}

        void add_highlight();
        void remove_highlight();
    };

    extern std::shared_ptr<button> current_button;

    static constexpr vmp::util::map<std::string_view, std::string_view, 17> fg_colors{{{
        { "BLACK"  , "\x1b[30m" },
        { "RED"    , "\x1b[31m" },
        { "GREEN"  , "\x1b[32m" },
        { "YELLOW" , "\x1b[33m" },
        { "BLUE"   , "\x1b[34m" },
        { "MAGENTA", "\x1b[35m" },
        { "CYAN"   , "\x1b[36m" },
        { "WHITE"  , "\x1b[37m" },

        { "BRIGHT_BLACK"  , "\x1b[90m" },
        { "BRIGHT_RED"    , "\x1b[91m" },
        { "BRIGHT_GREEN"  , "\x1b[92m" },
        { "BRIGHT_YELLOW" , "\x1b[93m" },
        { "BRIGHT_BLUE"   , "\x1b[94m" },
        { "BRIGHT_MAGENTA", "\x1b[95m" },
        { "BRIGHT_CYAN"   , "\x1b[96m" },
        { "BRIGHT_WHITE"  , "\x1b[97m" },

        { "DEFAULT", "\x1b[39m" }
    }}};

    static constexpr vmp::util::map<std::string_view, std::string_view, 17> bg_colors{{{
        { "BLACK"  , "\x1b[40m" },
        { "RED"    , "\x1b[41m" },
        { "GREEN"  , "\x1b[42m" },
        { "YELLOW" , "\x1b[43m" },
        { "BLUE"   , "\x1b[44m" },
        { "MAGENTA", "\x1b[45m" },
        { "CYAN"   , "\x1b[46m" },
        { "WHITE"  , "\x1b[47m" },

        { "BRIGHT_BLACK"  , "\x1b[100m" },
        { "BRIGHT_RED"    , "\x1b[101m" },
        { "BRIGHT_GREEN"  , "\x1b[102m" },
        { "BRIGHT_YELLOW" , "\x1b[103m" },
        { "BRIGHT_BLUE"   , "\x1b[104m" },
        { "BRIGHT_MAGENTA", "\x1b[105m" },
        { "BRIGHT_CYAN"   , "\x1b[106m" },
        { "BRIGHT_WHITE"  , "\x1b[107m" },

        { "DEFAULT", "\x1b[49m" }
    }}};

    static constexpr vmp::util::map<std::string_view, char, 11> dec_chars{{{
        /* ┘ */ { "br", 'j' },
        /* ┐ */ { "tr", 'k' },
        /* ┌ */ { "tl", 'l' },
        /* └ */ { "bl", 'm' },
        /* ┼ */ { "cr", 'n' },
        /* ─ */ { "ho", 'q' },
        /* │ */ { "ve", 'x' },
        /* ├ */ { "t1", 't' },
        /* ┤ */ { "t2", 'u' },
        /* ┴ */ { "t3", 'v' },
        /* ┬ */ { "t4", 'w' },
    }}};

    bool on_keypress(char);
    bool on_resize(vmp::con::coord);

    // line, column
    void set_cursor_pos(std::uint32_t, std::uint32_t);

    // line, column, text
    void print_at_pos(std::uint32_t, std::uint32_t, const std::wstring_view);

    // line, column, text
    void print_at_pos(std::uint32_t, std::uint32_t, const std::string_view);

    // line, column, char
    void print_at_pos(std::uint32_t, std::uint32_t, char);

    // insert n spaces into terminal
    void insert_char(std::uint32_t);

    // delete n chars, shifts text
    void delete_char(std::uint32_t);

    // replace n chars with space character
    void erase_char(std::uint32_t);

    // insert n lines, lines below will be shifted
    void insert_line(std::uint32_t);

    // delete n lines, starting from the row the cursor is on
    void delete_line(std::uint32_t);

    /* 0 erases from the current cursor position (inclusive) to the end of the line/display;
    1 erases from the beginning of the line/display up to and including the current cursor position;
    2 erases the entire line/display;
    replaces all text in viewport/screen with ' ' */
    void erase_in_display(std::uint32_t);

    /* 0 erases from the current cursor position (inclusive) to the end of the line/display;
    1 erases from the beginning of the line/display up to and including the current cursor position;
    2 erases the entire line/display;
    replaces all text in line with ' ' */
    void erase_in_line(std::uint32_t);

    void dec_mode();
    void ascii_mode();

    void init(player &);

    void exit();

    void draw_borders();
    void draw_queue_list();
    void draw_unsorted_list();

    void create_buttons();

    void check_w(std::shared_ptr<button> &);
    void check_a(std::shared_ptr<button> &);
    void check_s(std::shared_ptr<button> &);
    void check_d(std::shared_ptr<button> &);
}

#endif
