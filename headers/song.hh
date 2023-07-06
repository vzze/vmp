#ifndef SONG_HH
#define SONG_HH

#include <filesystem>
#include <utility>
#include <string>

namespace vmp {
    struct song {
        std::filesystem::path path;

        explicit song(std::filesystem::path);

        [[nodiscard]] std::wstring name() const;
    };
}

#endif
