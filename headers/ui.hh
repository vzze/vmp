#ifndef UI_HH
#define UI_HH

#include <vector>
#include <format>
#include <ranges>

#include <console.hh>
#include <player.hh>
#include <VMP_cmake.hh>
#include <util.hh>

namespace vmp {

    struct ui {
        public:
            console handler;

            using u32   = std::uint32_t;
            using cu32  = const std::uint32_t;
            using coord = console::coord;

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

            static constexpr struct possible_actions {
                static constexpr char quit        = 'q';

                static constexpr char up          = 'w'; // NOLINT(readability-identifier-length)
                static constexpr char down        = 's';
                static constexpr char left        = 'a';
                static constexpr char right       = 'd';

                static constexpr char scroll_up   = 'n';
                static constexpr char scroll_down = 'm';

                static constexpr char play        = 'p';

                static constexpr char toggle_pause_resume = 'v';

                static constexpr char volume_up   = 'C';
                static constexpr char volume_down = 'c';

                static constexpr char toggle_loop = 'l';

                static constexpr char skip        = 'S';

                static constexpr char shuffle     = 'e';

                static constexpr char unavailable = ' ';
            } actions = {};

            [[nodiscard]] char up_available() const;
            [[nodiscard]] char down_available() const;
            [[nodiscard]] char left_available() const;
            [[nodiscard]] char right_available() const;
            [[nodiscard]] char scroll_up_available() const;
            [[nodiscard]] char scroll_down_available() const;

            void draw_available_moves();

            void button_add_highlight();
            void button_remove_highlight();

            void add_highlight_selected(const coord, const std::string_view, const std::string_view);

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
            static constexpr u32 ROW_START = 2;

            static constexpr coord TOP_BAR = { 1, 2 };
            static constexpr coord AVAILABLE_MOVES_CUTOFF = { 8, 1 };
            static constexpr coord VOLUME_CUTOFF          = { AVAILABLE_MOVES_CUTOFF.column + 14, 1 };

            static constexpr auto HEARTBEAT = std::chrono::milliseconds{200};

            static constexpr auto QUEUE_LIST_TITLE = "Queues";
            static constexpr auto UNSORTED_LIST_TITLE = "Unsorted Songs";
        private:
            coord current_dimensions;
            u32 sidebar_width;
            u32 sidebar_stopping_point;

            u32 queues_offset;
            u32 unsorted_songs_offset;

            player & instance;
        public:
            ui(player &, const ui_opts);

            void up();
            void left();
            void down();
            void right();

            void scroll_up();
            void scroll_down();

            void play();

            void volume_up();
            void volume_down();

            void skip();
            void shuffle();

            void toggle_pause_resume();
            void toggle_loop();

            [[nodiscard]] bool queues_next_available() const;
            [[nodiscard]] bool queues_prev_available() const;

            [[nodiscard]] bool unsorted_next_available() const;
            [[nodiscard]] bool unsorted_prev_available() const;

            [[nodiscard]] bool main_next_available(cu32) const;
            [[nodiscard]] bool main_prev_available(cu32) const;

            bool key_callback(const char);
            bool resize_callback(const coord);
            bool notify_alive_callback();

            void draw_player_volume();
            void draw_player_status();
            void draw_player_info();

            std::vector<std::string> get_main_list(cu32);
            void draw_main_list(cu32);
            void hide_main_list();

            void main_next_page(cu32);
            void main_prev_page(cu32);

            std::vector<std::string> get_queues();
            void draw_queues();

            void queues_next_page();
            void queues_prev_page();

            std::vector<std::string> get_unsorted_songs();
            void draw_unsorted_songs();

            void unsorted_next_page();
            void unsorted_prev_page();

            void draw_borders();

            [[nodiscard]] static std::string format_row(std::string, cu32, bool = true);
            static void format_str_len(std::string &, cu32, bool = true);
    };
}

#endif
