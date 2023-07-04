#ifndef PLAYER_HH
#define PLAYER_HH

#include <filesystem>
#include <iostream>
#include <vector>
#include <string>

#include <queue.hh>
#include <util.hh>

namespace vmp {
    struct player {
        inline static constexpr std::string cwd = "vmp";
        std::vector<queue> queues;
        queue unsorted;

        explicit player(const std::filesystem::path &);
    };
}

#endif
