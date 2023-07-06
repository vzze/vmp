#ifndef QUEUE_HH
#define QUEUE_HH

#include <filesystem>
#include <cstddef>
#include <numeric>
#include <utility>
#include <string>
#include <vector>

#include <song.hh>

namespace vmp {
    struct queue {
        std::filesystem::path path;
        std::vector<song> songs;

        queue() = default;
        explicit queue(std::filesystem::path);

        [[nodiscard]] std::wstring name() const;
    };
}

#endif
