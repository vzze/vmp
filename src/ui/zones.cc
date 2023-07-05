#include <ui.hh>

void vmp::ui::update_zones_hl_start_pos() {
    zones.current_zone = ZONE::QUEUE_TITLE;

    zones[ZONE::QUEUE_TITLE].hl_start_pos = { TOP_BAR.x, TOP_BAR.y + 1 };
    zones[ZONE::UNSORTED_TITLE].hl_start_pos = { 1, sidebar_stopping_point + 1 };
}

vmp::ui::zone::zone(const coord pos) : hl_start_pos{pos}, currently_selected{0} {}

vmp::ui::button & vmp::ui::zone::current() {
    return buttons[currently_selected];
}

void vmp::ui::button_add_highlight() {
    auto pos = zones[zones.current_zone].hl_start_pos;

    if(zones.current_zone == ZONE::MAIN_LIST || zones.current_zone == ZONE::UNSORTED_LIST || zones.current_zone == ZONE::QUEUE_LIST)
        pos.y += zones[zones.current_zone].currently_selected;

    static constexpr auto col = bg_colors["BRIGHT_YELLOW"];
    static constexpr auto def = bg_colors["DEFAULT"];

    const auto prnt = std::string(col.begin(), col.end()) + " " + std::string(def.begin(), def.end());

    print_at_pos(pos, prnt);
}

void vmp::ui::button_remove_highlight() {
    auto pos = zones[zones.current_zone].hl_start_pos;

    if(zones.current_zone == ZONE::MAIN_LIST || zones.current_zone == ZONE::UNSORTED_LIST || zones.current_zone == ZONE::QUEUE_LIST)
        pos.y += zones[zones.current_zone].currently_selected;

    static constexpr auto def = bg_colors["DEFAULT"];

    const auto prnt = std::string(def.begin(), def.end()) + " " + std::string(def.begin(), def.end());

    print_at_pos(pos, prnt);
}

void vmp::ui::set_zone(const ZONE zone) {
    button_remove_highlight();
    zones.current_zone = zone;
    button_add_highlight();
}

vmp::ui::zone & vmp::ui::zones::operator [] (const ZONE zone) noexcept {
    return zones.at(static_cast<std::size_t>(zone));
}
