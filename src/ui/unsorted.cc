#include <ui.hh>

void vmp::ui::unsorted_next_page() {
    const auto add = current_dimensions.row - sidebar_stopping_point - 2;

    if(unsorted_songs_offset + add < instance.unsorted.songs.size()) {
        unsorted_songs_offset += add;
        draw_unsorted_songs();
    }
}

void vmp::ui::unsorted_prev_page() {
    const auto sub = current_dimensions.row - sidebar_stopping_point - 2;
    //                       v due to integer underflow
    if(unsorted_songs_offset - sub < instance.unsorted.songs.size()) {
        unsorted_songs_offset -= sub;
        draw_unsorted_songs();
    } else if(unsorted_songs_offset != 0) {
        unsorted_songs_offset = 0;
        draw_unsorted_songs();
    }
}

std::vector<std::string> vmp::ui::get_unsorted_songs(bool reset_buttons) {
    std::vector<std::string> ret;

    const auto unsorted_songs = std::ranges::subrange(
        instance.unsorted.songs.begin() + unsorted_songs_offset,
        instance.unsorted.songs.end()
    );

    u32 space = sidebar_stopping_point + 2;

    if(reset_buttons)
        zones[ZONE::UNSORTED_LIST].buttons.clear();

    for(u32 button_id = unsorted_songs_offset; const auto & song : unsorted_songs) {
        if(space > current_dimensions.row) break;

        if(reset_buttons)
            zones[ZONE::UNSORTED_LIST].buttons.push_back(button{button_id++});

        ret.push_back(format_row(song.name(), sidebar_width - ROW_START));
        ++space;
    }

    if(reset_buttons)
        zones[ZONE::UNSORTED_LIST].currently_selected %= static_cast<u32>(
            zones[ZONE::UNSORTED_LIST].buttons.size()
        );

    while(space <= current_dimensions.row) {
        ret.emplace_back(sidebar_width - ROW_START, ' ');
        ++space;
    }

    return ret;
}

void vmp::ui::draw_unsorted_songs(bool redraw_title, bool reset_buttons) {
    if(redraw_title)
        handler.print_at_pos({ 1, sidebar_stopping_point + 1 }, UNSORTED_LIST_TITLE);

    const auto u_songs = get_unsorted_songs(reset_buttons);

    for(auto start = sidebar_stopping_point + 2; const auto & song : u_songs)
        handler.print_at_pos({ ROW_START, start++ }, song);
}
