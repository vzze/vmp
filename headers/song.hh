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

        void play(ma_engine *);
        void free_resources() const;

        [[nodiscard]] std::wstring name() const;
    };
}

#endif
