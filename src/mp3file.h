#pragma once

#include <Windows.h>

#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <future>
#include <chrono>
#include <thread>
#include <queue>
#include <cstring>
#include <functional>

extern int fVolume;

struct MP3File {
    std::filesystem::path MP3location;
};

extern std::mutex mut;

extern std::string currently_playing;

extern std::atomic<bool> loaded_file;
extern std::atomic<bool> mpbreak;
extern std::atomic<bool> paused;
extern std::atomic<bool> to_loop;

extern std::function<void(std::string)> new_song_callback;

void playMP3(MP3File & mp3);

extern std::unordered_map<std::string, MP3File> files;
extern std::vector<std::string> mp3_list;

void loadMP3Files();
