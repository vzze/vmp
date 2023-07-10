#include <console.hh>
#include <player.hh>
#include <util.hh>
#include <ui.hh>

int main(int argc, char ** argv) {
    const auto args = vmp::util::parse_args(argc, argv);

    switch(args.size()) {
        case 1: {
            vmp::player player{args[0]};
            vmp::ui tui{player, {vmp::ui::DEFAULT_SIDEBAR_WIDTH, vmp::ui::DEFAULT_SIDEBAR_STOPPING_POINT}};

            tui.handler.main_loop(vmp::ui::HEARTBEAT);
        } break;

        default: vmp::util::check_args(args[1]); break;
    }

    return 0;
}
