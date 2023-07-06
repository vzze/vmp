#include <ui.hh>

void vmp::ui::main_next_page(cu32 queue_id) {
    const auto add = current_dimensions.y - TOP_BAR.y - 1;

    if(main_offset + add < instance.queues[queue_id].songs.size()) {
        main_offset += add;
        draw_main_list(queue_id);
    }
}

void vmp::ui::main_prev_page(cu32 queue_id) {
    const auto sub = current_dimensions.y - TOP_BAR.y - 1;

    if(main_offset - sub < instance.queues[queue_id].songs.size()) {
        main_offset -= sub;
        draw_main_list(queue_id);
    } else if(main_offset != 0) {
        main_offset = 0;
        draw_main_list(queue_id);
    }
}

std::vector<std::wstring> vmp::ui::get_main_list(cu32 queue_id) {
    std::vector<std::wstring> ret;

    const auto songs = std::ranges::subrange(
        instance.queues[queue_id].songs.begin() + main_offset,
        instance.queues[queue_id].songs.end()
    );

    u32 space = TOP_BAR.y + 1;

    zones[ZONE::MAIN_LIST].buttons.clear();
    zones[ZONE::MAIN_LIST].currently_selected = 0;

    for(u32 button_id = main_offset; const auto & song : songs) {
        if(space > current_dimensions.y) break;

        zones[ZONE::MAIN_LIST].buttons.push_back(button{button_id++});

        ret.push_back(format_row(song.name(), current_dimensions.x - ROW_START - sidebar_width + 1, false));
        ++space;
    }

    while(space <= current_dimensions.y) {
        ret.emplace_back(1, L' ');
        ++space;
    }

    return ret;
}

void vmp::ui::draw_main_list(cu32 queue_id) {
    const auto songs = get_main_list(queue_id);

    for(auto start = TOP_BAR.y + 1; const auto & song : songs) {
        print_at_pos({ ROW_START + sidebar_width, start++ }, song);
        erase_in_line(LINE::CURSOR_TO_EOL);
    }
}

void vmp::ui::hide_main_list() const {
    for(auto start = TOP_BAR.y + 1; start <= current_dimensions.y; ++start) {
        set_cursor_pos({ ROW_START + sidebar_width, start });
        erase_in_line(LINE::CURSOR_TO_EOL);
    }
}
