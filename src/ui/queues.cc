#include <ui.hh>

void vmp::ui::queues_next_page() {
    const auto add = sidebar_stopping_point - TOP_BAR.y - 2;

    if(queue_offset + add < instance.queues.size()) {
        queue_offset += add;
        draw_queues();
    }
}

void vmp::ui::queues_prev_page() {
    const auto sub = sidebar_stopping_point - TOP_BAR.y - 2;
    //                    v due to integer underflow
    if(queue_offset - sub < instance.queues.size()) {
        queue_offset -= sub;
        draw_queues();
    }
}

std::wstring vmp::ui::format_queue_name(std::wstring name) const {
    static constexpr std::wstring_view filler = L"...";

    if(name.length() >= sidebar_width - QUEUE_LIST_STARTING_POINT) {
        name.resize(sidebar_width - QUEUE_LIST_STARTING_POINT - filler.size());
        name += filler;
    } else {
        name.resize(sidebar_width - QUEUE_LIST_STARTING_POINT, L' ');
    }

    return name;
}

std::vector<std::wstring> vmp::ui::get_queues() {
    std::vector<std::wstring> ret;

    const auto queues = std::ranges::subrange(instance.queues.begin() + queue_offset, instance.queues.end());

    u32 space = TOP_BAR.y + 2;

    for(const auto & queue : queues) {
        if(space == sidebar_stopping_point) break;
        ret.push_back(format_queue_name(queue.name()));
        ++space;
    }

    while(space != sidebar_stopping_point) { // fill up the remaining rows with blank strings
        ret.emplace_back(sidebar_width - QUEUE_LIST_STARTING_POINT, L' ');
        ++space;
    }

    return ret;
}

void vmp::ui::draw_queues() {
    print_at_pos({ TOP_BAR.x + 1, TOP_BAR.y + 1 }, "Queues");

    const auto queues = get_queues();

    for(auto start = TOP_BAR.y + 2; const auto & queue : queues)
        print_at_pos({ QUEUE_LIST_STARTING_POINT, start++ }, queue);
}
