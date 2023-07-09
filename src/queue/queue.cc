#include <queue.hh>

namespace fs = std::filesystem;

vmp::queue::queue(fs::path q_path) : path{std::move(q_path)} {
    for(const auto & song : fs::directory_iterator(path))
        if(!song.is_directory())
            songs.emplace_back(song);

    songs.shrink_to_fit();
}

std::string vmp::queue::name() const {
    return path.filename().string();
}
