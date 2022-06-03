#pragma once

#include "mp3file.h"

struct Queue {
    std::filesystem::path location;
    std::vector<std::filesystem::path> pFiles;

    bool removed = false;

    void Init();

    ~Queue();
};

extern std::unordered_map<std::string, Queue> qs;

void loadQs();
