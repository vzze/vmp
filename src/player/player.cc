#include <player.hh>

namespace fs = std::filesystem;

vmp::player::player(const fs::path & cwd) {
    fs::current_path(cwd.parent_path());

    const fs::path new_cwd = fs::current_path() / player::data;

    if(!fs::exists(new_cwd))
        fs::create_directory(new_cwd);

    fs::current_path(new_cwd);

    unsorted = queue{new_cwd};

    if(!fs::exists(fs::current_path()))
        fs::create_directory(fs::current_path());

    for(const auto & queue : fs::directory_iterator(fs::current_path()))
        if(queue.is_directory())
            queues.emplace_back(queue);

    queues.shrink_to_fit();
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
