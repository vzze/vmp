#include <ui.hh>

void vmp::ui::unsorted_next_page() {
    const auto add = current_dimensions.y - sidebar_stopping_point - 2;

    if(unsorted_songs_offset + add < instance.unsorted.songs.size()) {
        unsorted_songs_offset += add;
        draw_unsorted_songs();
    }
}

void vmp::ui::unsorted_prev_page() {
    const auto sub = current_dimensions.y - sidebar_stopping_point - 2;
    //                       v due to integer underflow
    if(unsorted_songs_offset - sub < instance.unsorted.songs.size()) {
        unsorted_songs_offset -= sub;
        draw_unsorted_songs();
    } else if(unsorted_songs_offset != 0) {
        unsorted_songs_offset = 0;
        draw_unsorted_songs();
    }
}

std::vector<std::wstring> vmp::ui::get_unsorted_songs() {
    std::vector<std::wstring> ret;

    const auto unsorted_songs = std::ranges::subrange(
        instance.unsorted.songs.begin() + unsorted_songs_offset,
        instance.unsorted.songs.end()
    );

    u32 space = sidebar_stopping_point + 2;

    zones[ZONE::UNSORTED_LIST].buttons.clear();
    zones[ZONE::UNSORTED_LIST].currently_selected = 0;

    for(u32 button_id = unsorted_songs_offset; const auto & song : unsorted_songs) {
        if(space > current_dimensions.y) break;

        zones[ZONE::UNSORTED_LIST].buttons.push_back(button{button_id++});

        ret.push_back(format_sidebar_row(song.name()));
        ++space;
    }

    while(space <= current_dimensions.y) {
        ret.emplace_back(sidebar_width - ROW_START, L' ');
        ++space;
    }

    return ret;
}

void vmp::ui::draw_unsorted_songs() {
    print_at_pos({ 2, sidebar_stopping_point + 1 }, "Unsorted Songs");

    const auto u_songs = get_unsorted_songs();

    for(auto start = sidebar_stopping_point + 2; const auto & song : u_songs)
        print_at_pos({ ROW_START, start++ }, song);
}
