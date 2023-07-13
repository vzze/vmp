#include <ui.hh>

void vmp::ui::queues_next_page() {
    const auto add = sidebar_stopping_point - TOP_BAR.row - 2;

    if(queues_offset + add < instance.queues.size()) {
        queues_offset += add;
        draw_queues();
    }
}

void vmp::ui::queues_prev_page() {
    const auto sub = sidebar_stopping_point - TOP_BAR.row - 2;
    //                     v due to integer underflow
    if(queues_offset - sub < instance.queues.size()) {
        queues_offset -= sub;
        draw_queues();
    } else if(queues_offset != 0) {
        queues_offset = 0;
        draw_queues();
    }
}

std::vector<std::string> vmp::ui::get_queues(bool reset_buttons) {
    std::vector<std::string> ret;

    const auto queues = std::ranges::subrange(instance.queues.begin() + queues_offset, instance.queues.end());

    u32 space = TOP_BAR.row + 2;

    if(reset_buttons)
        zones[ZONE::QUEUE_LIST].buttons.clear();

    for(u32 button_id = queues_offset; const auto & queue : queues) {
        if(space == sidebar_stopping_point) break;

        if(reset_buttons)
            zones[ZONE::QUEUE_LIST].buttons.push_back(button{button_id++});

        ret.push_back(format_row(queue.name(), sidebar_width - ROW_START));
        ++space;
    }

    if(reset_buttons)
        zones[ZONE::QUEUE_LIST].currently_selected %= static_cast<u32>(
            zones[ZONE::QUEUE_LIST].buttons.size()
        );

    while(space != sidebar_stopping_point) { // fill up the remaining rows with blank strings
        ret.emplace_back(sidebar_width - ROW_START, ' ');
        ++space;
    }

    return ret;
}

void vmp::ui::draw_queues(bool redraw_title, bool reset_buttons) {
    if(redraw_title)
        handler.print_at_pos({ 1, TOP_BAR.row + 1 }, QUEUE_LIST_TITLE);

    const auto queues = get_queues(reset_buttons);

    for(auto start = TOP_BAR.row + 2; const auto & queue : queues)
        handler.print_at_pos({ ROW_START, start++ }, queue);
}
