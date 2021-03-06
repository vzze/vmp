#include "ui.h"

std::vector<std::future<void>> async_q = {};

Queue _current_q;
std::size_t _q_offset = 0;

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
    printf(" %s", s.c_str());
    console::text::mod::EraseInLine();
    UpdateVol();
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
        UpdatePause();
    }

    if(code == 'q') {
        mpbreak = true;
        _brkEvLoop = true;
    }
}

std::atomic<bool> resize_timeout = true;

void ResizeCallback(int col, int rows) {
    if(rows >= 9 && resize_timeout) {
        NewSongCallback(currently_playing);
        DrawUi();
        resize_timeout = false;
        async_q.push_back(std::async(std::launch::async, [&]() -> void {
            std::this_thread::sleep_for(std::chrono::milliseconds(128));
            std::lock_guard<decltype(mut)> lck(mut);
            NewSongCallback(currently_playing);
            DrawUi();
            resize_timeout = true;
        }));
    }
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
            auto & l = qs.at(x);

            if(l.pFiles.size() == 0) {
                console::Exit();
                std::cout << "Queue is empty.";
                return;
            }

            l.removed = true;

            _current_q = l;
        } catch(...) {
            console::Exit();
            return;
        }
    } else if(args[0] == "all") {
        if(mp3_list.size() == 0) {
            console::Exit();
            std::cout << "No songs installed.";
            return;
        }

        Queue cpy;

        cpy.removed = true;

        for(auto & s : mp3_list)
            cpy.pFiles.push_back(s);

        _current_q = cpy;
    } else {
        try {
            std::string range = args.at(0);
            args.erase(args.begin());

            int lower = std::stoi(range.substr(0, range.find('-')));
            int upper = std::stoi(range.substr(range.find('-') + 1));

            mp3_list.resize(upper);
            mp3_list.erase(mp3_list.begin(), mp3_list.begin() + lower - 1);

            Queue cpy;

            cpy.removed = true;

            for(auto & s : mp3_list)
                cpy.pFiles.push_back(s);

            _current_q = cpy;
        } catch (...) {
            console::Exit();
            std::cout << "Probably a malformed range.";
            return;
        }
    }

    auto lam = [&]() -> void {
        std::random_device rd;
        std::mt19937 mt(rd());

        auto cpy = _current_q;

        _current_q.removed = true;
        cpy.removed = true;
        while(true) {
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
                ++_q_offset;
            }
            _q_offset = 0;
            if(_brkEvLoop) break;
        }
    };

    async_q.push_back(std::async(std::launch::async, lam));
    new_song_callback = NewSongCallback;

    while(!loaded_file) {
        std::this_thread::sleep_for(std::chrono::milliseconds(128));
    }

    while(console::ProcessEvents() && !_brkEvLoop) {}

    console::cursor::Show();
    console::Exit();
}
