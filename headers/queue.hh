#ifndef QUEUE_HH
#define QUEUE_HH

#include <filesystem>
#include <cstddef>
#include <numeric>
#include <vector>
#include <string>

#include <song.hh>

namespace vmp {
    struct queue {
        std::filesystem::path path;
        std::vector<song> songs;
        std::vector<std::size_t> order;

        queue() = default;
        explicit queue(const std::filesystem::path &);

        [[nodiscard]] std::wstring name() const;
    };
}

#endif
