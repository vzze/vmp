#include <player.hh>

namespace fs = std::filesystem;

vmp::song::song(fs::path s_path) : path{std::move(s_path)}, resource{nullptr} {}

std::string vmp::song::name() const {
    return path.stem().string();
}

void vmp::song::play(engine * instance) {
    if(resource == nullptr)
        sound_init(instance, path.string().c_str(), &resource);

    sound_play(resource);
}

void vmp::song::stop()                   const { return sound_stop       (resource        ); }
void vmp::song::rewind()                 const { return sound_rewind     (resource        ); }
void vmp::song::set_volume(float volume) const { return sound_set_volume (resource, volume); }
bool vmp::song::is_playing()             const { return sound_is_playing (resource        ); }
void vmp::song::loop(bool mode)          const { return sound_set_looping(resource, mode  ); }
bool vmp::song::is_looping()             const { return sound_is_looping (resource        ); }
bool vmp::song::is_at_end()              const { return sound_is_at_end  (resource        ); }

void vmp::song::free_resources() {
    sound_free(resource);
    resource = nullptr;
}
