#include "ui.h"

std::vector<std::future<void>> async_q = {};

bool _brkEvLoop = false;
bool _internal_pause = false;
bool _shuffleEnabled = false;
bool _internal_FirstShuffle = false;

void SetTextColor(console::text::VALUE val) {
    console::text::fmt::SetGR(
        console::text::VALUE::NO_BOLD_BRIGHT,
        console::text::VALUE::NO_UNDERLINE,
        console::text::VALUE::POSITIVE,
        val
    );
}

void PrintButton(char button) {
    SetTextColor(console::text::VALUE::BFG_YELLOW);
    printf("[");

    SetTextColor();
    printf("%c", button);

    SetTextColor(console::text::VALUE::BFG_YELLOW);
    printf("]");

    SetTextColor();
}

void NewSongCallback(std::string s) {
    console::cursor::Position(1, 1);
    printf("Playing");
    SetTextColor(console::text::VALUE::BFG_YELLOW);
    printf(":");
    SetTextColor();
    s.resize(console::GetColumns() - 10, ' ');
    printf(" %s", s.c_str());
    console::text::mod::EraseInLine();
}

void UpdateVol() {
    console::cursor::Position(2, 1);
    printf("Volume");
    SetTextColor(console::text::VALUE::BFG_YELLOW);
    printf(":");
    SetTextColor();
    printf(" %i", fVolume);
    console::text::mod::EraseInLine();
}

void UpdateShuffle() {
    console::cursor::Position(console::GetRows() - 4, 1);

    PrintButton('h');

    printf(" Shuffle");
    SetTextColor(console::text::VALUE::BFG_YELLOW);
    printf(":");
    SetTextColor();

    if(_shuffleEnabled)
        printf(" Enabled");
    else
        printf(" Disabled");
    console::text::mod::EraseInLine();
}

void UpdateLoop() {
    console::cursor::Position(console::GetRows() - 3, 1);

    PrintButton('l');

    if(to_loop)
        printf(" Looping Track");
    else
        printf(" Not looping");
    console::text::mod::EraseInLine();
}

void UpdatePause() {
    console::cursor::Position(console::GetRows() - 2, 1);

    PrintButton('p');

    printf(" Current status");
    SetTextColor(console::text::VALUE::BFG_YELLOW);
    printf(":");
    SetTextColor();

    if(_internal_pause)
        printf(" Paused");
    else
        printf(" Playing");
    console::text::mod::EraseInLine();
}

void DrawUi() {
    UpdateVol();

    console::cursor::Position(3, 1);
    console::text::mod::EraseInLine();

    UpdateShuffle();

    console::cursor::Position(console::GetRows() - 5, 1);
    console::text::mod::EraseInLine();

    UpdateLoop();
    UpdatePause();

    console::cursor::Position(console::GetRows() - 1, 1);

    PrintButton('s');
    printf(" Skip");
    console::text::mod::EraseInLine();

    console::cursor::Position(console::GetRows(), 1);

    PrintButton('q');
    printf(" Quit.");
    console::text::mod::EraseInLine();

    for(size_t row = 4; row < console::GetRows() - 5; row++) {
        console::cursor::Position(row, 1);
        console::text::mod::EraseInLine();
    }
}

void KeyCallback(int code) {
    if(code == (int)console::keys::SPECIAL_KEYS::DOWN_ARROWN) {
        fVolume -= 10;
        if(fVolume < 0)
            fVolume = 0;
        UpdateVol();
    }

    if(code == (int)console::keys::SPECIAL_KEYS::UP_ARROWN) {
        fVolume += 10;
        if(fVolume > 1000)
            fVolume = 1000;
        UpdateVol();
    }

    if(code == 'l') {
        to_loop = !to_loop;
        UpdateLoop();
    }

    if(code == 'p') {
        paused = true;
        _internal_pause = !_internal_pause;
        UpdatePause();
    }

    if(code == 'h') {
        _shuffleEnabled = !_shuffleEnabled;
        UpdateShuffle();
    }

    if(code == 's') {
        mpbreak = true;
        _internal_pause = false;
    }

    if(code == 'q') {
        mpbreak = true;
        _brkEvLoop = true;
    }
}

void ResizeCallback(int col, int rows) {
    NewSongCallback(currently_playing);
    DrawUi();
}

void initUi(std::vector<std::string> & args) {
    if(!console::Init())
        throw;

    console::SetKeyCallback(KeyCallback);
    console::SetWindowBufferResizeCallback(ResizeCallback);
    console::cursor::HorizontalVerticalPosition();
    console::text::mod::EraseInDisplay(2);
    console::cursor::Hide();

    printf("Loading ...");

    if(args[0] == "queue") {
        args.erase(args.begin());
        std::string x = "";
        for(auto & ar : args) x += ar + " ";
        x.pop_back();
        try {
            auto l = qs.at(x);

            if(l.pFiles.size() == 0) {
                console::Exit();
                std::cout << "Queue is empty.";
                return;
            }

            auto lam = [&]() -> void {
                std::random_device rd;
                std::mt19937 mt(rd());
                auto cpy = qs.at(x);  // copy
                qs.at(x).removed = true;
                while(true) { // permanent loop for any selection
                    {
                        if(_shuffleEnabled) {
                            std::lock_guard<decltype(mut)> lck(mut);
                            std::shuffle(cpy.pFiles.begin(), cpy.pFiles.end(), mt);
                        }
                    }
                    for(auto & m : cpy.pFiles) {
                        loaded_file = false;
                        playMP3(files[m.string()]);
                        std::lock_guard<decltype(mut)> lck(mut);
                        if(_shuffleEnabled && !_internal_FirstShuffle) {
                            _internal_FirstShuffle = true;
                            std::shuffle(cpy.pFiles.begin(), cpy.pFiles.end(), mt);
                        }
                        if(_brkEvLoop) break;
                    }
                    if(_brkEvLoop) break;
                }
            };

            async_q.push_back(std::async(std::launch::async, lam));
        } catch(...) {
            console::Exit();
            return;
        }
    } else if(args[0] == "all") {

        auto lam = [&]() -> void {
            std::random_device rd;
            std::mt19937 mt(rd());
            while(true) { // permanent loop
                {
                    if(_shuffleEnabled) {
                        std::lock_guard<decltype(mut)> lck(mut);
                        std::shuffle(mp3_list.begin(), mp3_list.end(), mt);
                    }
                }
                for(auto & m : mp3_list) {
                    loaded_file = false;
                    playMP3(files[m]);
                    std::lock_guard<decltype(mut)> lck(mut);
                    if(_shuffleEnabled && !_internal_FirstShuffle) {
                        _internal_FirstShuffle = true;
                        std::shuffle(mp3_list.begin(), mp3_list.end(), mt);
                    }
                    if(_brkEvLoop) break;
                }
                if(_brkEvLoop) break;
            }
        };

        async_q.push_back(std::async(std::launch::async, lam));
    } else {
        try {
            std::string range = args.at(0);
            args.erase(args.begin());

            int lower = std::stoi(range.substr(0, range.find('-')));
            int upper = std::stoi(range.substr(range.find('-') + 1));

            mp3_list.resize(upper);
            mp3_list.erase(mp3_list.begin(), mp3_list.begin() + lower - 1);

            auto lam = [&]() -> void {
                std::random_device rd;
                std::mt19937 mt(rd());
                while(true) { // permanent loop
                    {
                        if(_shuffleEnabled) {
                            std::lock_guard<decltype(mut)> lck(mut);
                            std::shuffle(mp3_list.begin(), mp3_list.end(), mt);
                        }
                    }
                    for(auto & m : mp3_list) {
                        loaded_file = false;
                        playMP3(files[m]);
                        std::lock_guard<decltype(mut)> lck(mut);
                        if(_shuffleEnabled && !_internal_FirstShuffle) {
                            _internal_FirstShuffle = true;
                            std::shuffle(mp3_list.begin(), mp3_list.end(), mt);
                        }
                        if(_brkEvLoop) break;
                    }
                    if(_brkEvLoop) break;
                }
            };

            async_q.push_back(std::async(std::launch::async, lam));

        } catch (...) {
            console::Exit();
            return;
        }
    }

    new_song_callback = NewSongCallback;

    while(!loaded_file) {
        std::this_thread::sleep_for(std::chrono::milliseconds(128));
    }

    while(console::ProcessEvents() && !_brkEvLoop) {}

    console::cursor::Show();
    console::Exit();
}
