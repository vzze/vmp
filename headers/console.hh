#ifndef CONSOLE_HH
#define CONSOLE_HH

#include <functional>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#elif defined(__unix__)

#endif

namespace vmp::con {
    extern bool should_exit;

#ifdef _WIN32

    extern HANDLE in_handle;
    extern HANDLE out_handle;

    extern DWORD old_in_mode;
    extern DWORD old_out_mode;

    BOOL ctrl_handler(DWORD);
#endif

    struct coord {
        std::uint32_t x;
        std::uint32_t y;

        friend auto operator <=> (const coord &, const coord &) = default;
    };

    extern std::vector<std::function<bool(char)>> key_callbacks;
    extern std::vector<std::function<bool(vmp::con::coord)>> resize_callbacks;

    bool init();

    void process_events();
    void terminate();

    int exit_code();
}

#endif
