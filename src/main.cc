#include "queue.h"
#include "util.h"

int main(int argc, char ** argv) {
    std::vector<std::string> args;
    for(int i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }

    loadMP3Files();
    loadQs();

    processCMD(args);
}
