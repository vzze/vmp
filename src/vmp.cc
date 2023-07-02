#include <console.hh>
#include <player.hh>
#include <util.hh>
#include <ui.hh>

int main(int argc, char ** argv) {
    if(argc == 2) return vmp::util::check_args(argv[1]);
    if(!vmp::con::init()) return 0;

    vmp::player player{*argv};

    vmp::con::key_callbacks.emplace_back(vmp::ui::on_keypress);
    vmp::con::resize_callbacks.emplace_back(vmp::ui::on_resize);

    vmp::ui::init(player);
    vmp::con::process_events();
    vmp::ui::exit();

    return vmp::con::exit_code();
}
