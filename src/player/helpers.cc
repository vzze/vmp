#include <player.hh>

void vmp::player::stop_current_audio() {
    switch(song_type) {
        case SONG_TYPE::UNSORTED:
            unsorted.songs[song_id].stop();
            unsorted.songs[song_id].free_resources();
        break;

        case SONG_TYPE::IN_QUEUE:
            queues[queue_id].songs[song_id].stop();
            queues[queue_id].songs[song_id].free_resources();
        break;

        default: break;
    }
}

void vmp::player::play_song_from_queue(const std::uint32_t q_id, const std::uint32_t s_id) {
    const std::scoped_lock lck{audio};

    if(state == PLAYER_STATE::RESUMED) stop_current_audio();
    else state = PLAYER_STATE::RESUMED;

    queue_id  = q_id;
    song_id   = s_id;
    song_type = SONG_TYPE::IN_QUEUE;

    queues[queue_id].songs[song_id].play(instance);
}

void vmp::player::play_song_from_unsorted(const std::uint32_t s_id) {
    const std::scoped_lock lck{audio};

    if(state == PLAYER_STATE::RESUMED) stop_current_audio();
    else state = PLAYER_STATE::RESUMED;

    song_id   = s_id;
    song_type = SONG_TYPE::UNSORTED;

    unsorted.songs[song_id].play(instance);
}
