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

    if(state == STATE::RESUMED) stop_current_audio();
    else state = STATE::RESUMED;

    queue_id  = q_id;
    song_id   = s_id;
    song_type = SONG_TYPE::IN_QUEUE;

    queues[queue_id].songs[song_id].play(instance);
    queues[queue_id].songs[song_id].set_volume(static_cast<float>(volume) / 100.0F);
}

void vmp::player::play_song_from_unsorted(const std::uint32_t s_id) {
    const std::scoped_lock lck{audio};

    if(state == STATE::RESUMED) stop_current_audio();
    else state = STATE::RESUMED;

    song_id   = s_id;
    song_type = SONG_TYPE::UNSORTED;

    unsorted.songs[song_id].play(instance);
    unsorted.songs[song_id].set_volume(static_cast<float>(volume) / 100.0F);
}

void vmp::player::pause() {
    if(state == STATE::NOT_PLAYING) return;
    if(state == STATE::PAUSED) return;

    const std::scoped_lock lck{audio};

    switch(song_type) {
        case SONG_TYPE::UNSORTED:
            unsorted.songs[song_id].stop();
            state = STATE::PAUSED;
        break;

        case SONG_TYPE::IN_QUEUE:
            queues[queue_id].songs[song_id].stop();
            state = STATE::PAUSED;
        break;

        default: break;
    }
}

void vmp::player::resume() {
    if(state == STATE::NOT_PLAYING) return;
    if(state == STATE::RESUMED) return;

    const std::scoped_lock lck{audio};

    switch(song_type) {
        case SONG_TYPE::UNSORTED:
            unsorted.songs[song_id].play(instance);
            state = STATE::RESUMED;
        break;

        case SONG_TYPE::IN_QUEUE:
            queues[queue_id].songs[song_id].play(instance);
            state = STATE::RESUMED;
        break;

        default: break;
    }
}

void vmp::player::update_track_volume() {
    if(state == STATE::NOT_PLAYING) return;

    const std::scoped_lock lck{audio};

    switch(song_type) {
        case SONG_TYPE::IN_QUEUE: queues[queue_id].songs[song_id].set_volume(static_cast<float>(volume) / 100.0F); break;
        case SONG_TYPE::UNSORTED: unsorted.songs[song_id].set_volume(static_cast<float>(volume) / 100.0F); break;

        default: break;
    }

}

void vmp::player::volume_up() {
    if(volume == VOLUME_MAX) return;

    volume += VOLUME_MODIFIER;

    update_track_volume();
}

void vmp::player::volume_down() {
    if(volume == VOLUME_MIN) return;

    volume -= VOLUME_MODIFIER;

    update_track_volume();
}

void vmp::player::toggle_loop() {
    if(state == STATE::NOT_PLAYING) return;

    const std::scoped_lock lck{audio};

    switch(song_type) {
        case SONG_TYPE::IN_QUEUE:
            queues[queue_id].songs[song_id].loop(
                !queues[queue_id].songs[song_id].is_looping()
            );
        break;

        case SONG_TYPE::UNSORTED:
            unsorted.songs[song_id].loop(
                !unsorted.songs[song_id].is_looping()
            );
        break;

        default: break;
    }
}

// helper to convert atomic<uint32> to uint32
std::uint32_t vmp::player::get_volume() const { return volume; }
