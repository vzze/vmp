#ifndef PLAYER_HH
#define PLAYER_HH

#include <string_view>
#include <filesystem>
#include <algorithm>
#include <cstddef>
#include <numeric>
#include <utility>
#include <string>
#include <atomic>
#include <vector>
#include <memory>
#include <random>
#include <thread>
#include <mutex>

#include <util.hh>
#include <audio.h>

namespace vmp {
    struct song {
        std::filesystem::path path;
        sound * resource;

        explicit song(std::filesystem::path);

        void play(engine *);

        void stop() const;
        void rewind() const;

        void set_volume(float) const;
        void loop(bool) const;

        [[nodiscard]] bool is_playing() const;
        [[nodiscard]] bool is_looping() const;

        [[nodiscard]] bool is_at_end()  const;

        void free_resources();

        [[nodiscard]] std::string name() const;
    };

    struct queue {
        std::filesystem::path path;
        std::vector<song> songs;
        std::uint32_t draw_offset{0};

        queue() = default;
        explicit queue(std::filesystem::path);

        [[nodiscard]] std::string name() const;
    };

    struct player {
        private:
            engine * instance;

            std::atomic<std::uint32_t> queue_id, song_id;

            std::mutex audio;

            void manage(const std::stop_token &, engine *);

            std::jthread audio_manager;

            std::atomic<std::uint32_t> volume;

            static constexpr std::uint32_t VOLUME_MODIFIER = 5;
            static constexpr std::uint32_t VOLUME_DEFAULT  = 100;

            static constexpr std::uint32_t VOLUME_MIN = 0;
            static constexpr std::uint32_t VOLUME_MAX = 100;

            void update_track_volume();

            void stop_current_audio();

            std::unique_ptr<std::mt19937_64> mersenne;
        public:
            enum class SONG_TYPE : char {
                UNSORTED,
                IN_QUEUE,
                NONE
            };

            std::atomic<SONG_TYPE> song_type;

            enum class STATE : char {
                NOT_PLAYING,
                PAUSED,
                RESUMED
            };

            std::atomic<STATE> state;

            static constexpr std::string_view data = "vmp-data";

            std::vector<queue> queues;
            queue unsorted;

            explicit player(const std::filesystem::path &);

            player(const player &) = delete;
            player(player &&) = delete;

            player & operator = (const player &) = delete;
            player & operator = (player &&) = delete;

            struct info {
                std::size_t queues;
                std::size_t songs_in_queues;
                std::size_t unsorted_songs;
                std::size_t total_songs;
            };

            info get_info();

            static std::string location();

            void play_song_from_queue(const std::uint32_t, const std::uint32_t);
            void play_song_from_unsorted(const std::uint32_t);

            void pause();
            void resume();

            void toggle_loop();

            void volume_up();
            void volume_down();

            void skip();

            [[nodiscard]] std::string current_song() const;

            [[nodiscard]] bool current_track_looping() const;

            std::uint32_t current_volume() const;
            std::uint32_t current_queue_id() const;
            std::uint32_t current_song_id() const;

            bool has_started() const;

            void shuffle_queue(const std::uint32_t);
            void shuffle_unsorted();

            ~player();
    };
}

#endif
