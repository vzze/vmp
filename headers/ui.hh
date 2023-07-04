#ifndef UI_HH
#define UI_HH

#include <format>

#include <console.hh>
#include <player.hh>
#include <util.hh>

namespace vmp {

    struct ui {
        public:
            using u32  = std::uint32_t;
            using cu32 = const std::uint32_t;

            struct ui_opts {
                u32 sidebar_width;
                u32 sidebar_stopping_point;
            };

            inline static constexpr u32 DEFAULT_SIDEBAR_STOPPING_POINT = 12;
            inline static constexpr u32 DEFAULT_SIDEBAR_WIDTH = 28;
            inline static constexpr coord TOP_BAR = { 1, 2 };

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
        private:
            vmp::coord current_dimensions;
            u32 sidebar_width;
            u32 sidebar_stopping_point;

            player & instance;
        public:
            ui(player &, const ui_opts);

            bool key_callback(const char);
            bool resize_callback(const coord);

            void draw_borders();

            static void set_cursor_pos(const coord);
            static void print_at_pos  (const coord, const std::wstring_view);
            static void print_at_pos  (const coord, const std::string_view);
            static void print_at_pos  (const coord, const char);

            static void insert_char(cu32);
            static void delete_char(cu32);
            static void erase_char (cu32);
            static void insert_line(cu32);
            static void delete_line(cu32);

            static void dec_mode();
            static void ascii_mode();

            enum class display_opts : u32 {
                CURSOR_TO_EOD  = 0,
                BEG_TO_CURSOR  = 1,
                ENTIRE_DISPLAY = 2,
            };

            static void erase_in_display(const display_opts);

            enum class line_opts : u32 {
                CURSOR_TO_EOL = 0,
                BEG_TO_CURSOR = 1,
                ENTIRE_LINE   = 2
            };

            static void erase_in_line(const line_opts);
    };
}

#endif
