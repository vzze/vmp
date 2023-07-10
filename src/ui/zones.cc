#include <ui.hh>

void vmp::ui::update_zones_hl_start_pos() {
    current_zone = ZONE::QUEUE_TITLE;

    zones[ZONE::QUEUE_TITLE].hl_start_pos = { TOP_BAR.column, TOP_BAR.row + 1 };

    zones[ZONE::QUEUE_LIST].hl_start_pos = {
        zones[ZONE::QUEUE_TITLE].hl_start_pos.column + 1 ,
        zones[ZONE::QUEUE_TITLE].hl_start_pos.row + 1
    };

    zones[ZONE::UNSORTED_TITLE].hl_start_pos = { 1, sidebar_stopping_point + 1 };

    zones[ZONE::UNSORTED_LIST].hl_start_pos = {
        zones[ZONE::UNSORTED_TITLE].hl_start_pos.column + 1 ,
        zones[ZONE::UNSORTED_TITLE].hl_start_pos.row + 1
    };

    zones[ZONE::MAIN_LIST].hl_start_pos = { sidebar_width + ROW_START - 1, TOP_BAR.row + 1 };
}

vmp::ui::zone::zone(const coord pos) : hl_start_pos{pos}, currently_selected{0} {}

const vmp::ui::button & vmp::ui::zone::current() const {
    return buttons[currently_selected];
}

void vmp::ui::button_add_highlight() {
    auto pos = zones[current_zone].hl_start_pos;

    if(current_zone == ZONE::MAIN_LIST || current_zone == ZONE::UNSORTED_LIST || current_zone == ZONE::QUEUE_LIST)
        pos.row += zones[current_zone].currently_selected;

    static constexpr auto col = console::BG["BRIGHT_YELLOW"];
    static constexpr auto def = console::BG["DEFAULT"];

    const auto prnt = std::string(col) + " " + std::string(def);

    handler.print_at_pos(pos, prnt);

    if(current_zone == ZONE::QUEUE_LIST)
        draw_main_list(zones[ZONE::QUEUE_LIST].current().id);

    draw_available_moves();
}

void vmp::ui::button_remove_highlight() {
    auto pos = zones[current_zone].hl_start_pos;

    if(current_zone == ZONE::MAIN_LIST || current_zone == ZONE::UNSORTED_LIST || current_zone == ZONE::QUEUE_LIST)
        pos.row += zones[current_zone].currently_selected;

    static constexpr auto def = console::BG["DEFAULT"];

    const auto prnt = std::string(def) + " " + std::string(def);

    handler.print_at_pos(pos, prnt);
}

void vmp::ui::set_zone(const ZONE new_zone) {
    button_remove_highlight();
    current_zone = new_zone;
    button_add_highlight();
}

void vmp::ui::button_up() {
    button_remove_highlight();

    auto & location = zones[current_zone];

    if(location.currently_selected != 0) {
        --location.currently_selected;
    } else {
        location.currently_selected = static_cast<u32>(location.buttons.size()) - 1U;
    }

    button_add_highlight();
}

void vmp::ui::button_down() {
    button_remove_highlight();

    auto & location = zones[current_zone];

    ++location.currently_selected;
    location.currently_selected %= static_cast<u32>(location.buttons.size());

    button_add_highlight();
}

vmp::ui::zone & vmp::ui::zones::operator [] (const ZONE zone) noexcept {
    return zones.at(static_cast<std::size_t>(zone));
}

const vmp::ui::zone & vmp::ui::zones::operator [] (const ZONE zone) const noexcept {
    return zones.at(static_cast<std::size_t>(zone));
}
