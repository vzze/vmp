#include <ui.hh>

void vmp::ui::queues_next_page() {
    const auto add = sidebar_stopping_point - TOP_BAR.y - 2;

    if(queues_offset + add < instance.queues.size()) {
        queues_offset += add;
        draw_queues();
    }
}

void vmp::ui::queues_prev_page() {
    const auto sub = sidebar_stopping_point - TOP_BAR.y - 2;
    //                     v due to integer underflow
    if(queues_offset - sub < instance.queues.size()) {
        queues_offset -= sub;
        draw_queues();
    } else if(queues_offset != 0) {
        queues_offset = 0;
        draw_queues();
    }
}

std::vector<std::wstring> vmp::ui::get_queues() {
    std::vector<std::wstring> ret;

    const auto queues = std::ranges::subrange(instance.queues.begin() + queues_offset, instance.queues.end());

    u32 space = TOP_BAR.y + 2;

    zones[ZONE::QUEUE_LIST].buttons.clear();
    zones[ZONE::QUEUE_LIST].currently_selected = 0;

    for(u32 button_id = queues_offset; const auto & queue : queues) {
        if(space == sidebar_stopping_point) break;

        zones[ZONE::QUEUE_LIST].buttons.push_back(button{button_id++});

        ret.push_back(format_row(queue.name(), sidebar_width - ROW_START));
        ++space;
    }

    while(space != sidebar_stopping_point) { // fill up the remaining rows with blank strings
        ret.emplace_back(sidebar_width - ROW_START, L' ');
        ++space;
    }

    return ret;
}

void vmp::ui::draw_queues() {
    print_at_pos({ TOP_BAR.x + 1, TOP_BAR.y + 1 }, "Queues");

    const auto queues = get_queues();

    for(auto start = TOP_BAR.y + 2; const auto & queue : queues)
        print_at_pos({ ROW_START, start++ }, queue);
}
