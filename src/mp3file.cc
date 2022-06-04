#include "mp3file.h"

int fVolume = 100;

std::mutex mut;

std::string currently_playing;

std::atomic<bool> loaded_file;

std::function<void(std::string)> new_song_callback = [](std::string s) -> void {};

std::atomic<bool> mpbreak = false;
std::atomic<bool> paused = false;
std::atomic<bool> to_loop = false;

void playMP3(MP3File & mp3) {
    mciSendStringW((L"open \"" + mp3.MP3location.wstring() + L"\" alias mp3 wait").c_str(), NULL, 0, NULL);
    mciSendStringW((L"setaudio mp3 volume to " + std::to_wstring(fVolume)).c_str(), NULL, 0, NULL);
    mciSendStringW(L"play mp3", NULL, 0, NULL);

    {
        std::lock_guard lck(mut);
        std::string filename = mp3.MP3location.filename().string();
        currently_playing = filename.substr(0, filename.find(".mp3"));
        new_song_callback(currently_playing);
    }

    loaded_file = true;

    char status[128] = {};

    int currVol = fVolume;

    mciSendString("status mp3 mode", status, 128, NULL);

    while(strcmp(status, "playing") == 0 || strcmp(status, "paused") == 0) {
        mciSendString("status mp3 mode", status, 128, NULL);

        std::lock_guard lck(mut);

        if(mpbreak) {
            mciSendString("stop mp3", NULL, 0, NULL);
            mciSendString("close mp3", NULL, 0, NULL);
            mpbreak = false;
            return;
        }

        if(paused) {
            if(strcmp(status, "playing") == 0)
                mciSendString("pause mp3", NULL, 0, NULL);
            else if(strcmp(status, "paused") == 0)
                mciSendString("resume mp3", NULL, 0, NULL);
            paused = false;
        }

        if(currVol != fVolume) {
            currVol = fVolume;
            mciSendStringW((L"setaudio mp3 volume to " + std::to_wstring(fVolume)).c_str(), NULL, 0, NULL);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(128));
    }

    mciSendString("stop mp3", NULL, 0, NULL);
    mciSendString("close mp3", NULL, 0, NULL);
    mpbreak = false;

    if(to_loop) playMP3(mp3);
}

std::unordered_map<std::string, MP3File> files = {};

std::vector<std::string> mp3_list;

void loadMP3Files() {
    const char * home = getenv("USERPROFILE"); // NOLINT

    std::filesystem::path mp3loc = std::string(home) + "\\vmp\\Songs";

    for(auto & f : std::filesystem::directory_iterator(mp3loc)) {
        mp3_list.push_back(f.path().string());
        files[f.path().string()] = {f};
    }
}
