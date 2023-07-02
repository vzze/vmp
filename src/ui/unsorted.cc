#include <ui.hh>

void vmp::ui::draw_unsorted_list() {
    print_at_pos(sidebar_stopping_point + 1, 2, "Unsorted Songs");

    for(std::uint32_t y = sidebar_stopping_point + 2; const auto & s : instance->unsorted.songs) {
        if(y > current_dimensions.y) break;

        auto name = s.name();

        if(name.length() >= sidebar_width - 3) {
            name.resize(sidebar_width - 6);
            name += L"...";
        }

        print_at_pos(y, 3, name);

        ++y;
    }
}
