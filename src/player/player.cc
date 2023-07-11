#include <player.hh>

namespace fs = std::filesystem;

vmp::player::player([[maybe_unused]] const fs::path & cwd)
    : instance{nullptr},
      queue_id{0},
      song_id{0},
      volume{VOLUME_DEFAULT},
      song_type{SONG_TYPE::NONE},
      state{STATE::NOT_PLAYING}
{
    engine_init(&instance);

    fs::current_path(cwd.parent_path());

    const fs::path new_cwd = fs::current_path() / player::data;

    if(!fs::exists(new_cwd))
        fs::create_directory(new_cwd);

    fs::current_path(new_cwd);

    if(!fs::exists(fs::current_path()))
        fs::create_directory(fs::current_path());

    unsorted = queue{new_cwd};

    for(const auto & queue : fs::directory_iterator(fs::current_path()))
        if(queue.is_directory())
            queues.emplace_back(queue);

    queues.shrink_to_fit();

    audio_manager = std::jthread([&](const std::stop_token & token, engine * current) {
        manage(token, current);
    }, instance);

    audio_manager.detach();
}

vmp::player::info vmp::player::get_info() {
    const auto num_songs_in_qs = std::accumulate(
        queues.begin(),
        queues.end(),
        std::size_t{0},
        [](const auto acc, const auto & queue) {
            return acc + queue.songs.size();
        }
    );

    return {
        queues.size(),
        num_songs_in_qs,
        unsorted.songs.size(),
        num_songs_in_qs + unsorted.songs.size()
    };
}

std::string vmp::player::location() {
    return fs::current_path().is_absolute() ?
            fs::current_path()
                .parent_path().string()
        :
            fs::absolute(
                fs::current_path()
            ).parent_path().string();
}

std::string vmp::player::current_song() {
    switch(song_type) {
        case SONG_TYPE::UNSORTED: return unsorted.songs[song_id].name(); break;
        case SONG_TYPE::IN_QUEUE: return queues[queue_id].songs[song_id].name(); break;

        default: return ""; break;
    }
}

vmp::player::~player() {
    state = STATE::NOT_PLAYING;
    song_type = SONG_TYPE::NONE;

    engine_free(instance);
}
