#include <ui.hh>

void vmp::ui::draw_player_info() {
    const auto info = instance.get_info();

    const auto fmt = [](std::string & name, cu32 max_len, bool elongate) {
        static constexpr std::string_view filler = "...";

        if(name.length() >= max_len) {
            name.resize(max_len - filler.size());
            name += filler;
        } else if(elongate) {
            name.resize(max_len, ' ');
        }
    };

    std::array text{
        std::string("Player Information"),

        std::string(""),

        std::format("Location: {}", instance.location()),

        std::string(""),

        std::format("Number of Queues: {}", info.queues),
        std::format("Number of Songs in Queues: {}", info.songs_in_queues),
        std::format("Number of Unsorted Songs: {}", info.unsorted_songs),

        std::string(""),

        std::format("Total Songs: {}", info.total_songs),

        std::string(""),

        std::format("Move keys: {}/{}/{}/{}", actions.up, actions.left, actions.down, actions.right),
        std::format("Scroll keys: {}/{}", actions.scroll_up, actions.scroll_down),

        std::format("Play: {}", actions.play),
        std::format("Quit: {}", actions.quit),

        std::string(""),

        std::string("Version ") + std::string(cmake::VMP::version),
    };

    for(auto & line : text)
        fmt(line, current_dimensions.column - sidebar_width - ROW_START + 1, false);

    for(coord location = { sidebar_width + ROW_START, TOP_BAR.row + 1 }; const auto & line : text) {
        if(location.row > current_dimensions.row) break;

        handler.print_at_pos(location, line);

        ++location.row;
    }
}
