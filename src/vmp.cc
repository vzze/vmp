#include <console.hh>
#include <player.hh>
#include <util.hh>
#include <ui.hh>

bool key_cb(char key) {
    return key != 'q';
}

int main(int argc, char ** argv) {
    const auto args = vmp::util::parse_args(argc, argv);

    switch(args.size()) {
        case 1: {
            vmp::player player{*argv};
            vmp::console console{};
            vmp::ui console_ui{player, {vmp::ui::DEFAULT_SIDEBAR_WIDTH, vmp::ui::DEFAULT_SIDEBAR_STOPPING_POINT}};

            console.add_key_callback([&](const auto data) -> bool {
                return console_ui.key_callback(data);
            });

            console.add_resize_callback([&](const auto data) -> bool {
                return console_ui.resize_callback(data);
            });

            console.main_loop();
        } break;

        default: vmp::util::check_args(args[1]); break;
    }

    return 0;
}
