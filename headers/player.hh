#ifndef PLAYER_HH
#define PLAYER_HH

#include <string_view>
#include <filesystem>
#include <algorithm>
#include <vector>

#include <queue.hh>
#include <util.hh>

namespace vmp {
    struct player {
        private:
            engine * instance;
        public:

            static constexpr std::string_view data = "vmp-data";

            std::vector<queue> queues;
            queue unsorted;

            explicit player(const std::filesystem::path &);

            player(const player &) = default;
            player(player &&) = default;

            player & operator = (const player &) = default;
            player & operator = (player &&) = default;

            struct info {
                std::size_t queues;
                std::size_t songs_in_queues;
                std::size_t unsorted_songs;
                std::size_t total_songs;
            };

            info get_info();

            static std::string location();

            ~player();
    };
}

#endif
