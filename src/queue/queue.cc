#include <queue.hh>

namespace fs = std::filesystem;

vmp::queue::queue(const fs::path & q_path) : path{q_path} {
    for(const auto & song : fs::directory_iterator(q_path))
        if(!song.is_directory())
            songs.emplace_back(song);

    songs.shrink_to_fit();

    order.resize(songs.size());

    std::iota(order.begin(), order.end(), 0);
}

std::wstring vmp::queue::name() const {
    return path.filename();
}
