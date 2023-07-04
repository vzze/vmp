#include <song.hh>

namespace fs = std::filesystem;

vmp::song::song(fs::path s_path) : path{std::move(s_path)} {}

std::wstring vmp::song::name() const {
    return path.stem().wstring();
}
