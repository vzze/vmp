#include "queue.h"

void Queue::Init() {
    std::ifstream f(location);

    std::filesystem::path mp3loc;
    while(f >> mp3loc)
        pFiles.push_back(mp3loc);
}

Queue::~Queue() {
    if(removed == false) {
        std::ofstream o(location);
        for(auto & file : pFiles)
            o << file << '\n';
    }
}

std::unordered_map<std::string, Queue> qs = {};

void loadQs() {
    const char * home = getenv("USERPROFILE"); // NOLINT

    std::filesystem::path qloc = std::string(home) + "\\vmp\\Queues";

    auto fiterator = std::filesystem::directory_iterator(qloc);

    for(auto & f : fiterator) {
        Queue q = {f.path(), {}};
        qs[f.path().filename().string()] = q;
        qs.at(f.path().filename().string()).Init();
        q.removed = true;
    }
}
