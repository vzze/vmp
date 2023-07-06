#include <console.hh>

vmp::console::console() noexcept
    : should_exit{true}, in_handle{GetStdHandle(STD_INPUT_HANDLE)}, out_handle{GetStdHandle(STD_OUTPUT_HANDLE)} ,
      old_in_mode{0}, old_out_mode{0}
{
    std::cout.setf(std::ios::unitbuf);
    std::wcout.setf(std::ios::unitbuf);

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast, performance-no-int-to-ptr)
    if(out_handle == INVALID_HANDLE_VALUE) return;

    using unsigned_t = std::make_unsigned_t<DWORD>;

    unsigned_t mode = 0;

    if(GetConsoleMode(out_handle, &mode) == 0) return;

    old_out_mode = mode;

    mode |=
        static_cast<unsigned_t>(ENABLE_VIRTUAL_TERMINAL_PROCESSING) |
        static_cast<unsigned_t>(DISABLE_NEWLINE_AUTO_RETURN);

    if(SetConsoleMode(out_handle, mode) == 0) return;

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast, performance-no-int-to-ptr)
    if(in_handle == INVALID_HANDLE_VALUE) return;

    if(GetConsoleMode(in_handle, &mode) == 0) return;

    old_in_mode = mode;

    mode = ENABLE_EXTENDED_FLAGS;

    mode |=
        static_cast<unsigned_t>(ENABLE_WINDOW_INPUT) |
        static_cast<unsigned_t>(ENABLE_MOUSE_INPUT);

    if(SetConsoleMode(in_handle, mode) == 0) return;

    should_exit = false;

    util::write_console("\x1b[?1049h");
    util::write_console("\x1b[?25l");
}

void vmp::console::process_events() noexcept {
    DWORD read{};

    GetNumberOfConsoleInputEvents(in_handle, &read);

    // NOLINTNEXTLINE(hicpp-avoid-c-arrays, modernize-avoid-c-arrays, cppcoreguidelines-avoid-c-arrays)
    std::unique_ptr<INPUT_RECORD[]> event_buffer{nullptr};

    try {
        // NOLINTNEXTLINE(hicpp-avoid-c-arrays, modernize-avoid-c-arrays, cppcoreguidelines-avoid-c-arrays)
        event_buffer = std::make_unique<INPUT_RECORD[]>(read);
    } catch(...) { should_exit = true; return; }


    ReadConsoleInput(in_handle, event_buffer.get(), read, &read);

    // NOLINTBEGIN(cppcoreguidelines-pro-type-union-access)
    for(DWORD i = 0; i < read; ++i)
        switch(event_buffer[i].EventType) {
            case KEY_EVENT:
                if(event_buffer[i].Event.KeyEvent.bKeyDown != 0)
                    for(const auto & callback : key_callbacks)
                        if(!callback(event_buffer[i].Event.KeyEvent.uChar.AsciiChar)) should_exit = true;
            break;

            case WINDOW_BUFFER_SIZE_EVENT:
                for(const auto & callback : resize_callbacks)
                    if(!callback({
                        static_cast<std::uint32_t>(event_buffer[i].Event.WindowBufferSizeEvent.dwSize.X),
                        static_cast<std::uint32_t>(event_buffer[i].Event.WindowBufferSizeEvent.dwSize.Y)
                    })) should_exit = true;
            break;
        }
    // NOLINTEND(cppcoreguidelines-pro-type-union-access)
}

void vmp::console::main_loop() noexcept {
    while(!should_exit) {
        process_events();

        std::this_thread::sleep_for(std::chrono::milliseconds{1});
    }
}

vmp::console::~console() noexcept {
    util::write_console("\x1b[?1049l");
    util::write_console("\x1b[!p");
    util::write_console("\x1b[?25h");

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast, performance-no-int-to-ptr)
    if(in_handle != INVALID_HANDLE_VALUE)
        SetConsoleMode(in_handle, old_in_mode);

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast, performance-no-int-to-ptr)
    if(out_handle != INVALID_HANDLE_VALUE)
        SetConsoleMode(out_handle, old_out_mode);
}
