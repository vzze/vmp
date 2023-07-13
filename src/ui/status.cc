#include <ui.hh>

void vmp::ui::draw_player_volume() {
    static constexpr coord after_keys = {
        .column = AVAILABLE_MOVES_CUTOFF.column + 2,
        .row    = AVAILABLE_MOVES_CUTOFF.row
    };

    handler.print_at_pos(after_keys, std::format("Volume: {:<3}", instance.current_volume()));

    handler.dec_mode();

    static constexpr coord one_down = {
        .column = VOLUME_CUTOFF.column,
        .row    = VOLUME_CUTOFF.row + 1
    };

    handler.print_at_pos(VOLUME_CUTOFF, console::DEC["ve"]);
    handler.print_at_pos(one_down, console::DEC["t3"]);

    handler.ascii_mode();
}

void vmp::ui::draw_player_status() {
    static constexpr coord after_keys = {
        .column = VOLUME_CUTOFF.column + 2,
        .row    = VOLUME_CUTOFF.row
    };

    switch(instance.state) {
        case player::STATE::NOT_PLAYING:
            handler.print_at_pos(after_keys, "Currently not playing.");
        break;

        case player::STATE::PAUSED:
            handler.print_at_pos(
                after_keys,
                format_row(
                    std::format("Paused on: {}", instance.current_song()),
                    current_dimensions.column - after_keys.column + 1
                )
            );
        break;

        case player::STATE::RESUMED:
            handler.print_at_pos(
                after_keys,
                format_row(
                    [&]() -> std::string {
                        const auto queue_id = instance.current_queue_id() + 1;
                        const auto song_id  = instance.current_song_id() + 1;

                        if(instance.current_track_looping()) {
                            switch(instance.song_type) {
                                case player::SONG_TYPE::IN_QUEUE:
                                    return std::format("Looping ({}/{}): {}", queue_id, song_id, instance.current_song());
                                break;
                                case player::SONG_TYPE::UNSORTED:
                                    return std::format("Looping ({}): {}", song_id, instance.current_song());
                                break;

                                default: return ""; break;
                            }
                        } else {
                            switch(instance.song_type) {
                                case player::SONG_TYPE::IN_QUEUE:
                                    return std::format("Playing ({}/{}): {}", queue_id, song_id, instance.current_song());
                                break;
                                case player::SONG_TYPE::UNSORTED:
                                    return std::format("Playing ({}): {}", song_id, instance.current_song());
                                break;

                                default: return ""; break;
                            }
                        }
                    }(),
                    current_dimensions.column - after_keys.column + 1
                )
            );
        break;
    }
}

void vmp::ui::draw_player_info() {
    const auto info = instance.get_info();

    std::array text{
        std::string("Player Information"),

        std::string(""),

        std::format("Location: {}", instance.location()),

        std::string(""),

        std::format("Number of {}: {}", QUEUE_LIST_TITLE, info.queues),
        std::format("Number of Songs in {}: {}", QUEUE_LIST_TITLE, info.songs_in_queues),
        std::format("Number of {}: {}", UNSORTED_LIST_TITLE, info.unsorted_songs),

        std::string(""),

        std::format("Total Songs: {}", info.total_songs),

        std::string(""),

        std::format("Move keys: {}/{}/{}/{}", actions.up, actions.left, actions.down, actions.right),
        std::format("Scroll keys: {}/{}", actions.scroll_up, actions.scroll_down),

        std::string(""),

        std::format("Play: {}", actions.play),
        std::format("Looping: {}", actions.toggle_loop),

        std::string(""),

        std::format("Pause/Resume: {}", actions.toggle_pause_resume),
        std::format("Volume: {}/{}", actions.volume_down, actions.volume_up),

        std::string(""),

        std::format("Skip: {}", actions.skip),
        std::format("Shuffle: {}", actions.shuffle),

        std::string(""),

        std::format("Quit: {}", actions.quit),

        std::string(""),

        std::string("Version ") + std::string(cmake::VMP::version),
    };

    for(auto & line : text)
        format_str_len(line, current_dimensions.column - sidebar_width - ROW_START + 1, false);

    for(coord location = { sidebar_width + ROW_START, TOP_BAR.row + 1 }; const auto & line : text) {
        if(location.row > current_dimensions.row) break;

        handler.print_at_pos(location, line);

        ++location.row;
    }
}
