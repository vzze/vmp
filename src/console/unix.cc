#include <iostream>

#include <console.hh>

vmp::console::console() noexcept : should_exit{false}, old_sets{} {
    struct termios new_sets{};

    tcgetattr(fileno(stdin), &new_sets);

    old_sets = new_sets;

    new_sets.c_lflag &= static_cast<unsigned>(~ICANON & ~ECHO); // NOLINT(hicpp-signed-bitwise)

    tcsetattr(fileno(stdin), TCSANOW, &new_sets);

    util::write_console("\x1b[?1049h");
    util::write_console("\x1b[?25l");
}

void vmp::console::process_events() noexcept { // NOLINT
    struct winsize window{};

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window); // NOLINT(cppcoreguidelines-pro-type-vararg, hicpp-vararg)

    for(const auto & callback : resize_callbacks)
        if(!callback({ window.ws_col, window.ws_row })) should_exit = true;

    struct timeval time{10, 0}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

    fd_set set{};

    FD_ZERO(&set); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
    FD_SET(fileno(stdin), &set); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index, hicpp-signed-bitwise)

    const auto res = select(fileno(stdin) + 1, &set, nullptr, nullptr, &time);

    if(res > 0) {
        char key{};
        [[maybe_unused]] const auto x = read(fileno(stdin), &key, 1);

        for(const auto & callback : key_callbacks)
            if(!callback(key)) should_exit = true;
    }
}

void vmp::console::main_loop() noexcept {
    while(!should_exit) {
        process_events();

        std::this_thread::sleep_for(std::chrono::milliseconds{1});
    }
}

vmp::console::~console() noexcept {
    tcsetattr(fileno(stdin), TCSANOW, &old_sets);

    util::write_console("\x1b[?1049l");
    util::write_console("\x1b[!p");
    util::write_console("\x1b[?25h");
}
