#include <console.hh>

void vmp::console::main_loop() noexcept {
    std::cout.setf(std::ios::unitbuf);
    std::wcout.setf(std::ios::unitbuf);

    util::write_console("\x1b[?1049h");
    util::write_console("\x1b[?25l");

    while(!should_exit) {
        process_events();

        std::this_thread::sleep_for(std::chrono::milliseconds{1});
    }

    util::write_console("\x1b[?1049l");
    util::write_console("\x1b[!p");
    util::write_console("\x1b[?25h");
}
