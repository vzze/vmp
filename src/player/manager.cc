#include <player.hh>

void vmp::player::manage(const std::stop_token & token, engine * current) {
    while(!token.stop_requested()) {
        switch(state) {
            case STATE::RESUMED: {
                const std::scoped_lock lck{audio};

                switch(song_type) {
                    case SONG_TYPE::UNSORTED:
                        if(unsorted.songs[song_id].is_at_end() && !unsorted.songs[song_id].is_looping()) {
                            unsorted.songs[song_id].free_resources();

                            ++song_id;

                            song_id = song_id % static_cast<std::uint32_t>(unsorted.songs.size());

                            unsorted.songs[song_id].play(current);
                            unsorted.songs[song_id].set_volume(static_cast<float>(volume) / 100.0F);
                        }
                    break;

                    case SONG_TYPE::IN_QUEUE:
                        if(queues[queue_id].songs[song_id].is_at_end() && !queues[queue_id].songs[song_id].is_looping()) {
                            queues[queue_id].songs[song_id].free_resources();

                            ++song_id;

                            song_id = song_id % static_cast<std::uint32_t>(queues[queue_id].songs.size());

                            queues[queue_id].songs[song_id].play(current);
                            queues[queue_id].songs[song_id].set_volume(static_cast<float>(volume) / 100.0F);
                        }
                    break;

                    default: break;
                }
            } break;

            default: break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds{1});
    }
}
