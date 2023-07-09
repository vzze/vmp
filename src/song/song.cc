#include <song.hh>

namespace fs = std::filesystem;

#include <iostream>

vmp::song::song(fs::path s_path) : path{std::move(s_path)}, resource{nullptr} {}

std::string vmp::song::name() const {
    return path.stem().string();
}

void vmp::song::play(engine * instance) {
    sound_init(instance, path.string().c_str(), &resource);
    sound_play(resource);
}

void vmp::song::free_resources() const {
    sound_free(resource);
}
