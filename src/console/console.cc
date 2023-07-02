#include <console.hh>

bool vmp::con::should_exit{false};

std::vector<std::function<bool(char)>> vmp::con::key_callbacks{};
std::vector<std::function<bool(vmp::con::coord)>> vmp::con::resize_callbacks{};

#ifdef _WIN32

HANDLE vmp::con::in_handle{};
HANDLE vmp::con::out_handle{};

DWORD vmp::con::old_in_mode{};
DWORD vmp::con::old_out_mode{};

BOOL vmp::con::ctrl_handler(DWORD) {
    should_exit = true;
    return TRUE;
}

#endif

bool vmp::con::init() {
#ifdef _WIN32
    out_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(out_handle == INVALID_HANDLE_VALUE) return false;

    DWORD mode = 0;

    if(!GetConsoleMode(out_handle, &mode)) return false;

    old_out_mode = mode;

    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;

    if(!SetConsoleMode(out_handle, mode)) return false;

    in_handle = GetStdHandle(STD_INPUT_HANDLE);

    if(in_handle == INVALID_HANDLE_VALUE) return false;

    if(!GetConsoleMode(in_handle, &mode)) return false;

    old_in_mode = mode;

    mode = ENABLE_EXTENDED_FLAGS;

    mode |= ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;

    if(!SetConsoleMode(in_handle, mode)) return false;

    if(!SetConsoleCtrlHandler(vmp::con::ctrl_handler, TRUE)) return false;
#endif

    return true;
}

void vmp::con::process_events() {
    while(!should_exit) {
#ifdef _WIN32

        DWORD read;

        GetNumberOfConsoleInputEvents(in_handle, &read);

        auto event_buffer = std::make_unique<INPUT_RECORD[]>(read);
        ReadConsoleInput(in_handle, event_buffer.get(), read, &read);

        for(DWORD i = 0; i < read; ++i)
            switch(event_buffer[i].EventType) {
                case KEY_EVENT:
                    if(event_buffer[i].Event.KeyEvent.bKeyDown)
                        for(const auto & cb : key_callbacks)
                            if(!cb(event_buffer[i].Event.KeyEvent.uChar.AsciiChar)) should_exit = true;
                break;

                case WINDOW_BUFFER_SIZE_EVENT:
                    for(const auto & cb : resize_callbacks)
                        if(!cb({
                            static_cast<std::uint32_t>(event_buffer[i].Event.WindowBufferSizeEvent.dwSize.X),
                            static_cast<std::uint32_t>(event_buffer[i].Event.WindowBufferSizeEvent.dwSize.Y)
                        })) should_exit = true;
                break;
            }
#endif

        std::this_thread::sleep_for(std::chrono::milliseconds{1});
    }
}

void vmp::con::terminate() { should_exit = true; }

int vmp::con::exit_code() {
#ifdef _WIN32

    if(!SetConsoleMode(out_handle, old_out_mode)) return 42;
    if(!SetConsoleMode(in_handle, old_in_mode)) return 43;

#endif

    return 0;
}
