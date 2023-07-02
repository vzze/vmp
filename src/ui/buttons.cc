#include <ui.hh>

void vmp::ui::button::add_highlight() {
    char move_options[] = "wasd";

    if(!w) move_options[0] = ' ';
    if(!a) move_options[1] = ' ';
    if(!s) move_options[2] = ' ';
    if(!d) move_options[3] = ' ';

    print_at_pos(1, 1, move_options);

    constexpr auto hi  = bg_colors["BRIGHT_YELLOW"];
    constexpr auto def = bg_colors["DEFAULT"];

    const auto prnt = std::string(hi.begin(), hi.end()) + " " + std::string(def.begin(), def.end());

    print_at_pos(line_hl, column_hl, prnt);
}

void vmp::ui::button::remove_highlight() {
    constexpr auto def = bg_colors["DEFAULT"];

    const auto prnt = std::string(def.begin(), def.end()) + " " + std::string(def.begin(), def.end());

    print_at_pos(line_hl, column_hl, prnt);
}

void vmp::ui::create_buttons() {
    current_button = std::make_shared<button>(3, 1);

    if(instance->queues.size()) {
        current_button->d = std::make_shared<button>(/* &instance->queues[0], */ 4, 2, nullptr, current_button);

        auto chain = current_button->d;

        for(std::size_t i = 1; i < instance->queues.size(); ++i) {
            chain->s = std::make_shared<button>(/* &instance->queues[i], */ 4 + i, 2, chain, current_button);
            chain = chain->s;
        }
    }
}

void vmp::ui::check_w(std::shared_ptr<vmp::ui::button> & button) {
    if(button->w) {
        button->remove_highlight();
        button = button->w;
        button->add_highlight();
    }
}

void vmp::ui::check_a(std::shared_ptr<vmp::ui::button> & button) {
    if(button->a) {
        button->remove_highlight();
        button = button->a;
        button->add_highlight();
    }
}

void vmp::ui::check_s(std::shared_ptr<vmp::ui::button> & button) {
    if(button->s) {
        button->remove_highlight();
        button = button->s;
        button->add_highlight();
    }
}

void vmp::ui::check_d(std::shared_ptr<vmp::ui::button> & button) {
    if(button->d) {
        button->remove_highlight();
        button = button->d;
        button->add_highlight();
    }
}
