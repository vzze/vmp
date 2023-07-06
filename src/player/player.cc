#include <player.hh>

namespace fs = std::filesystem;

vmp::player::player(const fs::path & cwd) {
    fs::current_path(cwd.parent_path());

    const auto new_cwd = fs::current_path() / player::cwd;

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

#ifdef VMP_DEBUG
    util::write_wconsole(L"LOADED QUEUES:\n");

    for(const auto & queue : queues) {
        util::write_wconsole(queue.name(), L'\n');

        for(const auto & song : queue.songs)
            util::write_wconsole(L"  ", song.name(), L'\n');

        util::write_wconsole(L'\n');
    }

    util::write_wconsole(L"UNSORTED SONGS:\n");

    for(const auto & song : unsorted.songs)
        util::write_wconsole(L"  ", song.name(), L'\n');
#endif
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
        fs::current_path().string() : fs::absolute(fs::current_path()).string();
}
