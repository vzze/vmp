#include <ui.hh>

void vmp::ui::draw_player_info() {
    const auto info = instance.get_info();

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

        std::string("Move keys: w/a/s/d"),
        std::string("Scroll keys: n/m"),
        std::string("Quit: q"),

        std::string(""),

        std::string("Version ") + std::string(cmake::project_version),
    };

    for(auto & line : text)
        format_row(line, current_dimensions.x - sidebar_width - ROW_START + 1, false);

    for(coord location = { sidebar_width + ROW_START, TOP_BAR.y + 1 }; const auto & line : text) {
        if(location.y > current_dimensions.y) break;

        print_at_pos(location, line);

        ++location.y;
    }
}
