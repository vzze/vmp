#pragma once

#include <console.h>
#include <random>

#include "queue.h"

extern std::vector<std::future<void>> async_q;

void SetTextColor(console::text::VALUE val = console::text::VALUE::FG_DEFAULT);
void PrintButton(char button);

void UpdateVol();
void UpdateShuffle();
void UpdateLoop();
void UpdatePause();

void DrawUi();

void KeyCallback(int code);
void ResizeCallback(int col, int rows);
void NewSongCallback(std::string s);

extern bool _brkEvLoop;
extern bool _internal_pause;
extern bool _shuffleEnabled;
extern bool _internal_FirstShuffle;
extern std::atomic<bool> resize_timeout;

void initUi(std::vector<std::string> & args);
