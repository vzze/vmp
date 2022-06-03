#pragma once

#include <console.h>
#include <random>

#include "queue.h"

extern std::vector<std::future<void>> song_q;

void DrawUi();

void KeyCallback(int code);
void ResizeCallback(int col, int rows);
void NewSongCallback(std::string s);

extern bool _brkEvLoop;
extern bool _internal_pause;
extern bool _shuffleEnabled;
extern bool _internal_FirstShuffle;

void initUi(std::vector<std::string> & args);
