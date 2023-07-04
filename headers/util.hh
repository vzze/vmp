#ifndef UTIL_HH
#define UTIL_HH

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <cstddef>
#include <string>
#include <ranges>
#include <array>
#include <span>

namespace vmp::util {
    template<typename Key, typename Value, std::size_t Size>
    struct map {
        std::array<std::pair<Key, Value>, Size> data;

        consteval Value operator [] (const Key & key) const {
            const auto itr = std::ranges::find_if(data, [&](const auto & value) {
                return value.first == key;
            });

            if(itr == data.end()) {
                throw std::logic_error{"Key does not exist."};
            }

            return itr->second;
        }
    };

    template<typename ... Args>
    void write_console(Args && ... args) noexcept {
        try {
            ((std::cout << std::forward<Args>(args)), ...);
        } catch(...) {}
    }

    template<typename ... Args>
    void write_wconsole(Args && ... args) noexcept {
        try {
            ((std::wcout << std::forward<Args>(args)), ...);
        } catch(...) {}
    }

    void version();
    void conditions();

    std::span<char*> parse_args(int, char **);

    void check_args(const std::string &);
}

#endif
