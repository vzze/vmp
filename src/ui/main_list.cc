#include <ui.hh>

void vmp::ui::main_next_page(cu32 queue_id) {
    const auto add = current_dimensions.row - TOP_BAR.row - 1;

    auto & main_offset = instance.queues[queue_id].draw_offset;

    if(main_offset + add < instance.queues[queue_id].songs.size()) {
        main_offset += add;
        draw_main_list(queue_id);
    }
}

void vmp::ui::main_prev_page(cu32 queue_id) {
    const auto sub = current_dimensions.row - TOP_BAR.row - 1;

    auto & main_offset = instance.queues[queue_id].draw_offset;

    if(main_offset - sub < instance.queues[queue_id].songs.size()) {
        main_offset -= sub;
        draw_main_list(queue_id);
    } else if(main_offset != 0) {
        main_offset = 0;
        draw_main_list(queue_id);
    }
}

std::vector<std::string> vmp::ui::get_main_list(cu32 queue_id) {
    std::vector<std::string> ret;

    auto & main_offset = instance.queues[queue_id].draw_offset;

    const auto songs = std::ranges::subrange(
        instance.queues[queue_id].songs.begin() + main_offset,
        instance.queues[queue_id].songs.end()
    );

    u32 space = TOP_BAR.row + 1;

    zones[ZONE::MAIN_LIST].buttons.clear();
    zones[ZONE::MAIN_LIST].currently_selected = 0;

    for(u32 button_id = main_offset; const auto & song : songs) {
        if(space > current_dimensions.row) break;

        zones[ZONE::MAIN_LIST].buttons.push_back(button{button_id++});

        ret.push_back(format_row(song.name(), current_dimensions.column - ROW_START - sidebar_width + 1, false));
        ++space;
    }

    while(space <= current_dimensions.row) {
        ret.emplace_back(1, ' ');
        ++space;
    }

    return ret;
}

void vmp::ui::draw_main_list(cu32 queue_id) {
    const auto songs = get_main_list(queue_id);

    for(auto start = TOP_BAR.row + 1; const auto & song : songs) {
        handler.print_at_pos({ ROW_START + sidebar_width, start++ }, song);
        handler.erase_in_line(console::LINE::CURSOR_TO_EOL);
    }
}

void vmp::ui::hide_main_list() {
    for(auto start = TOP_BAR.row + 1; start <= current_dimensions.row; ++start) {
        handler.set_cursor_pos({ ROW_START + sidebar_width, start });
        handler.erase_in_line(console::LINE::CURSOR_TO_EOL);
    }
}
