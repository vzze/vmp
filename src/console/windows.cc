#include <console.hh>
#include <consoleapi.h>
#include <handleapi.h>
#include <winbase.h>

vmp::console::console() noexcept
    : should_exit{true}, in_handle{GetStdHandle(STD_INPUT_HANDLE)}, out_handle{GetStdHandle(STD_OUTPUT_HANDLE)} ,
      old_in_mode{0}, old_out_mode{0}
{
    if(out_handle == INVALID_HANDLE_VALUE) return; // NOLINT (WIN API)

    using unsigned_t = std::make_unsigned_t<DWORD>;

    unsigned_t mode = 0;

    if(GetConsoleMode(out_handle, &mode) == 0) return;

    old_out_mode = mode;

    mode |=
        static_cast<unsigned_t>(ENABLE_VIRTUAL_TERMINAL_PROCESSING) |
        static_cast<unsigned_t>(DISABLE_NEWLINE_AUTO_RETURN);

    if(SetConsoleMode(out_handle, mode) == 0) return;

    if(in_handle == INVALID_HANDLE_VALUE) return; // NOLINT (WIN API)

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

    std::unique_ptr<INPUT_RECORD[]> event_buffer{nullptr}; // NOLINT (INPUT_RECORD[] is not a C-style array)

    try {
        event_buffer = std::make_unique<INPUT_RECORD[]>(read); // NOLINT (INPUT_RECORD[] is not a C-style array)
    } catch(...) { should_exit = true; }


    ReadConsoleInput(in_handle, event_buffer.get(), read, &read);

    for(DWORD i = 0; i < read; ++i)
        switch(event_buffer[i].EventType) {
            case KEY_EVENT:
                if(event_buffer[i].Event.KeyEvent.bKeyDown != 0) // NOLINT (WIN API)
                    for(const auto & callback : key_callbacks)
                        if(!callback(event_buffer[i].Event.KeyEvent.uChar.AsciiChar)) should_exit = true; // NOLINT (WIN API)
            break;

            case WINDOW_BUFFER_SIZE_EVENT:
                for(const auto & callback : resize_callbacks)
                    if(!callback({
                        static_cast<std::uint32_t>(event_buffer[i].Event.WindowBufferSizeEvent.dwSize.X), // NOLINT (WIN API)
                        static_cast<std::uint32_t>(event_buffer[i].Event.WindowBufferSizeEvent.dwSize.Y)  // NOLINT (WIN API)
                    })) should_exit = true;
            break;
        }
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

    if(in_handle != INVALID_HANDLE_VALUE) // NOLINT (WIN API)
        SetConsoleMode(in_handle, old_in_mode);

    if(out_handle != INVALID_HANDLE_VALUE) // NOLINT (WIN API)
        SetConsoleMode(out_handle, old_out_mode);
}
