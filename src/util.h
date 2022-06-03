#pragma once

#include "queue.h"
#include "ui.h"

void download(std::vector<std::string> & args);

void listMP3s(std::vector<std::string> & args);

void createQ(std::vector<std::string> & args);
void removeQ(std::vector<std::string> & args);
void addQ(std::vector<std::string> & args);
void delQ(std::vector<std::string> & args);
void peekQ(std::vector<std::string> & args);
void listQs(std::vector<std::string> & args);

void helpcmd(std::vector<std::string> & args);

void qCommands(std::vector<std::string> & args);

void processCMD(std::vector<std::string> & args);
