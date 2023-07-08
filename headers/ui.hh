#ifndef UI_HH
#define UI_HH

#include <vector>
#include <format>
#include <ranges>

#include <console.hh>
#include <player.hh>
#include <cmake.hh>
#include <util.hh>

namespace vmp {

    struct ui {
        public:
            using u32  = std::uint32_t;
            using cu32 = const std::uint32_t;

            bool screen_is_too_small;

            struct ui_opts {
                u32 sidebar_width;
                u32 sidebar_stopping_point;
            };

            enum class ZONE : char {
                QUEUE_TITLE,
                QUEUE_LIST,
                UNSORTED_TITLE,
                UNSORTED_LIST,
                MAIN_LIST,
                ZONE_NUMBER
            };

            ZONE current_zone;

            struct button {
                u32 id;
            };

            struct zone {
                coord hl_start_pos;
                u32 currently_selected;

                std::vector<button> buttons;

                explicit zone(const coord = {0, 0});

                [[nodiscard]] const button & current() const;
            };

            [[nodiscard]] char w_available() const;
            [[nodiscard]] char a_available() const;
            [[nodiscard]] char s_available() const;
            [[nodiscard]] char d_available() const;
            [[nodiscard]] char n_available() const;
            [[nodiscard]] char m_available() const;

            void draw_available_moves() const;

            void button_add_highlight();
            void button_remove_highlight();

            struct zones {
                private:
                    std::array<zone, static_cast<std::size_t>(ZONE::ZONE_NUMBER)> zones;
                public:
                    zone & operator [] (const ZONE) noexcept;
                    const zone & operator [] (const ZONE) const noexcept;
            } zones;

            void update_zones_hl_start_pos();
            void set_zone(const ZONE);

            void button_up();
            void button_down();

            static constexpr u32 DEFAULT_SIDEBAR_STOPPING_POINT = 12;
            static constexpr u32 DEFAULT_SIDEBAR_WIDTH = 28;
            static constexpr u32 ROW_START = 3;

            static constexpr coord TOP_BAR = { 1, 2 };

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

            u32 queues_offset;
            u32 unsorted_songs_offset;

            player & instance;
        public:
            ui(player &, const ui_opts);

            void w();
            void a();
            void s();
            void d();
            void n();
            void m();

            [[nodiscard]] bool queues_next_available() const;
            [[nodiscard]] bool queues_prev_available() const;

            [[nodiscard]] bool unsorted_next_available() const;
            [[nodiscard]] bool unsorted_prev_available() const;

            [[nodiscard]] bool main_next_available(cu32) const;
            [[nodiscard]] bool main_prev_available(cu32) const;

            bool key_callback(const char);
            bool resize_callback(const coord);

            void draw_player_info();

            std::vector<std::wstring> get_main_list(cu32);
            void draw_main_list(cu32);
            void hide_main_list() const;

            void main_next_page(cu32);
            void main_prev_page(cu32);

            std::vector<std::wstring> get_queues();
            void draw_queues();

            void queues_next_page();
            void queues_prev_page();

            std::vector<std::wstring> get_unsorted_songs();
            void draw_unsorted_songs();

            void unsorted_next_page();
            void unsorted_prev_page();

            void draw_borders();

            static void format_row(std::string &, cu32, bool = true);
            [[nodiscard]] static std::wstring format_row(std::wstring, cu32, bool = true);

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

            enum class DISPLAY : u32 {
                CURSOR_TO_EOD  = 0,
                BEG_TO_CURSOR  = 1,
                ENTIRE_DISPLAY = 2,
            };

            static void erase_in_display(const DISPLAY);

            enum class LINE : u32 {
                CURSOR_TO_EOL = 0,
                BEG_TO_CURSOR = 1,
                ENTIRE_LINE   = 2
            };

            static void erase_in_line(const LINE);
    };
}

#endif
