#ifndef UTIL_HH
#define UTIL_HH

#include <string_view>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <cstddef>
#include <string>
#include <vector>
#include <ranges>
#include <array>
#include <span>

#include <cmake.hh>

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

    inline constexpr std::string_view version_text =
        "This program comes with ABSOLUTELY NO WARRANTY;\n"
        "This is free software, and you are welcome to redistribute it\n"
        "under certain conditions; type `vmp conditions' for details.\n";

    void version();

    inline constexpr std::string_view conditions_text =
        "This program is free software: you can redistribute it and/or modify\n"
        "it under the terms of the GNU General Public License as published by\n"
        "the Free Software Foundation, either version 3 of the License, or\n"
        "(at your option) any later version.\n\n"

        "This program is distributed in the hope that it will be useful,\n"
        "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
        "GNU General Public License for more details.\n\n"

        "You should have received a copy of the GNU General Public License\n"
        "along with this program.  If not, see <https://www.gnu.org/licenses/>.\n";


    void conditions();

    std::span<char*> parse_args(int, char **);

    void check_args(const std::string_view);
}

#endif
