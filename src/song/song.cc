#include <song.hh>

namespace fs = std::filesystem;

vmp::song::song(const fs::path & s_path) : path{s_path} {}

std::wstring vmp::song::name() const {
    return path.stem();
}
