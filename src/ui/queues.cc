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
    }
}

std::vector<std::wstring> vmp::ui::get_queues() {
    std::vector<std::wstring> ret;

    const auto queues = std::ranges::subrange(instance.queues.begin() + queues_offset, instance.queues.end());

    u32 space = TOP_BAR.y + 2;

    for(const auto & queue : queues) {
        if(space == sidebar_stopping_point) break;
        ret.push_back(format_sidebar_row(queue.name()));
        ++space;
    }

    while(space != sidebar_stopping_point) { // fill up the remaining rows with blank strings
        ret.emplace_back(sidebar_width - SIDEBAR_ROW_START, L' ');
        ++space;
    }

    return ret;
}

void vmp::ui::draw_queues() {
    print_at_pos({ TOP_BAR.x + 1, TOP_BAR.y + 1 }, "Queues");

    const auto queues = get_queues();

    for(auto start = TOP_BAR.y + 2; const auto & queue : queues)
        print_at_pos({ SIDEBAR_ROW_START, start++ }, queue);
}
