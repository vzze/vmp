#ifndef SONG_HH
#define SONG_HH

#include <filesystem>
#include <utility>
#include <string>
#include <memory>

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
}

#endif
