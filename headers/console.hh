#ifndef CONSOLE_HH
#define CONSOLE_HH

#include <functional>
#include <iostream>
#include <utility>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#elif defined(__unix__)
#include <sys/ioctl.h>
#include <termios.h>
#endif

#include <util.hh>

namespace vmp {
    struct coord {
        std::uint32_t x;
        std::uint32_t y;

        friend auto operator <=> (const coord &, const coord &) = default;
    };

    struct console {
        private:
            bool should_exit;
#ifdef _WIN32
            HANDLE in_handle;
            HANDLE out_handle;

            DWORD old_in_mode;
            DWORD old_out_mode;
#elif defined(__unix__)
            struct termios old_sets;
#endif
            std::vector<std::function<bool(const char)>> key_callbacks;
            std::vector<std::function<bool(const coord)>> resize_callbacks;
        public:
            template<typename Callable>
            void add_key_callback(Callable && callable) noexcept {
                try {
                    key_callbacks.emplace_back(std::forward<Callable>(callable));
                } catch(...) { should_exit = true; }
            }

            template<typename Callable>
            void add_resize_callback(Callable && callable) noexcept {
                try {
                    resize_callbacks.emplace_back(std::forward<Callable>(callable));
                } catch(...) { should_exit = true; }
            }

            console() noexcept;
            console(const console &) = default;
            console(console &&) = default;

            console & operator = (const console &) = default;
            console & operator = (console &&) = default;

            void process_events() noexcept;

            static bool refresh() noexcept;

            void main_loop() noexcept;

            ~console() noexcept;
    };
}

#endif
