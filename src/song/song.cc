#include <song.hh>

namespace fs = std::filesystem;

#include <iostream>

vmp::song::song(fs::path s_path) : path{std::move(s_path)}, resource{nullptr} {}

std::wstring vmp::song::name() const {
    return path.stem().wstring();
}

void vmp::song::play(engine * instance) {
    sound_init_w(instance, path.wstring().c_str(), &resource);
    sound_play(resource);
}

void vmp::song::free_resources() const {
    sound_free(resource);
}
