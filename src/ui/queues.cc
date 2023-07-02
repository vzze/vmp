#include <ui.hh>

void vmp::ui::draw_queue_list() {
    print_at_pos(3, 2, "Queues");

    for(std::uint32_t y = 4; const auto & q : instance->queues) {
        if(y == sidebar_stopping_point) break;

        auto name = q.name();

        if(name.length() >= sidebar_width - 3) {
            name.resize(sidebar_width - 6);
            name += L"...";
        } else {
            name.resize(sidebar_width - 4, L' ');
        }

        print_at_pos(y, 3, name);

        ++y;
    }
}
