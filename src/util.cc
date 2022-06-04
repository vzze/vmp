#include "util.h"

void download(std::vector<std::string> & args) {
    system(("youtube-dl.exe --prefer-ffmpeg --extract-audio --audio-format mp3 --limit-rate 10M -o \"~/vmp/Songs/%(title)s.%(ext)s\" " + args[0]).c_str());
}

void listMP3s(std::vector<std::string> & args) {
    size_t num = 0;
    for(auto str : mp3_list) {
        str = str.substr(str.find("\\Songs\\") + 7);
        std::cout << ++num << ". " << str.substr(0, str.find(".mp3")) << '\n';
    }
}

void createQ(std::vector<std::string> & args) {
    const char * home = getenv("USERPROFILE"); // NOLINT

    std::string queueName = args[0] + " ";
    args.erase(args.begin());

    for(auto & str : args)
        if(str != "")
            queueName += str + " ";

    queueName.pop_back();

    std::filesystem::path qloc = std::string(home) + "\\vmp\\Queues\\" + queueName;

    std::ofstream qOut(qloc); qOut.write("", 0); qOut.close();

    std::cout << "Created Queue with name: " << '"' << queueName << '"' << '\n';
}

void removeQ(std::vector<std::string> & args) {
    std::string range = args[0];
    args.erase(args.begin());

    std::string queueName = args[0] + " ";
    args.erase(args.begin());

    int lower = std::stoi(range.substr(0, range.find('-')));
    int upper = std::stoi(range.substr(range.find('-') + 1));

    if(lower > upper)
        std::swap(lower, upper);

    for(auto & str : args)
        if(str != "")
            queueName += str + " ";

    queueName.pop_back();

    try {
        auto & q = qs.at(queueName);

        if(upper > q.pFiles.size()) {
            std::cout << "There aren't that many songs.\n";
        }

        for(int i = upper - 1; i >= lower - 1; i--) {
            q.pFiles.erase(q.pFiles.begin() + i);
        }

        std::cout << "Removed " << upper - lower + 1 << " songs: \"" << queueName << "\"\n";
    } catch(...) {
        std::cout << "No Queue with the name: \"" << queueName << "\"\n";
    }
}

void addQ(std::vector<std::string> & args) {

    std::string range = args[0];
    args.erase(args.begin());

    std::string queueName = args[0] + " ";
    args.erase(args.begin());

    int lower = std::stoi(range.substr(0, range.find('-')));
    int upper = std::stoi(range.substr(range.find('-') + 1));

    for(auto & str : args)
        if(str != "")
            queueName += str + " ";

    queueName.pop_back();

    if(upper > mp3_list.size()) {
        std::cout << "There aren't that many songs.\n";
        return;
    }

    try {
        auto & ref = qs.at(queueName);
        for(int i = lower - 1; i <= upper - 1; i++) {
            ref.pFiles.push_back(mp3_list[i]);
        }
        std::cout << "Added " << upper - lower + 1 << " songs: \"" << queueName << "\"\n";
    } catch(...) {
        std::cout << "No Queue with the name: \"" << queueName << "\"\n";
    }
}

void delQ(std::vector<std::string> & args) {
    const char * home = getenv("USERPROFILE"); // NOLINT

    std::string queueName = args[0] + " ";
    args.erase(args.begin());

    for(auto & str : args)
        if(str != "")
            queueName += str + " ";

    queueName.pop_back();

    std::filesystem::path qloc = std::string(home) + "\\vmp\\Queues\\" + queueName;

    if(std::filesystem::remove(qloc)) {
        qs.at(queueName).removed = true;
        qs.erase(queueName);

        std::cout << "Removed \"" << queueName << "\"\n";
    } else {
        std::cout << "No Queue with the name: \"" << queueName << "\"\n";
    }
}

void peekQ(std::vector<std::string> & args) {
    std::string queueName = args[0] + " ";
    args.erase(args.begin());

    for(auto & str : args)
        if(str != "")
            queueName += str + " ";

    queueName.pop_back();

    try {
        auto & q = qs.at(queueName);
        size_t num = 0;

        for(auto & n : q.pFiles)
            std::cout << ++num << ". " << n.filename().string().substr(0, n.filename().string().find(".mp3")) << '\n';
    } catch (...) {
        std::cout << "No Queue with the name: \"" << queueName << "\"\n";
    }
}

void listQs(std::vector<std::string> & args) {
    size_t num = 0;
    for(auto & [n, q] : qs) {
        std::cout << "Queue " << ++num << ". " << "\"" << n << "\"" << " Songs: " << q.pFiles.size() << '\n';
    }
}

void qCommands(std::vector<std::string> &args) {
    static std::unordered_map<std::string, void(*)(std::vector<std::string>&)> cmds = {
        {"create", createQ},
        {"remove", removeQ},
        {"add", addQ},
        {"delete", delQ},
        {"peek", peekQ},
        {"list", listQs}
    };
    try {
        const auto cmd = *args.begin();
        args.erase(args.begin());
        cmds.at(cmd)(args);
    } catch(...) {
        std::cout << "nonexistent command";
    }
}

void helpcmd(std::vector<std::string> &args) {
    static std::unordered_map<std::string, std::string> h = {
        {"download", "download [String]\n\nExample:\ndownload https://www.youtube.com/watch?v=8IIniEWky64\ndownload 8IIniEWky64"},
        {"play", "play [CMD]\n\nAll possibilities:\nplay queue [NAME]\nplay all\nplay [RANGE]\n\nExample:\nplay 1-5"},
        {"queue", "queue [CMD]\n\nExample:\nqueue create [NAME]"},
        {"list", "Lists all globally installed songs.\nWhen using the queue commands the range is selected from here.\n\nExample:\nlist"},

        {"help", "Standard Help Command\n\nAll queues are looped by default.\nYou can loop the current track.\n\nList of commands:\n\ndownload\nplay\nqueue\nlist\nqueue create\nqueue remove\nqueue add\nqueue delete\nqueue peek\nqueue list"},
        {"", "Standard Help Command\n\nAll queues are looped by default.\nYou can loop the current track.\n\nList of commands:\n\ndownload\nplay\nqueue\nlist\nqueue create\nqueue remove\nqueue add\nqueue delete\nqueue peek\nqueue list"},

        {"queue create", "Creates a new queue.\nIf a queue already has the name it will be overridden.\n\nExample:\nqueue create [NAME]"},
        {"queue remove", "Removes a range of songs from a queue.\nqueue remove [RANGE] [NAME]\n\nExample:\nqueue remove 1-15 my queue"},
        {"queue add", "Adds a range of songs into a queue.\nqueue add [RANGE] [NAME]\n\nExample:\nqueue add 1-17 my queue"},
        {"queue delete", "Deletes a queue.\nqueue delete [NAME]"},
        {"queue peek", "Displays all the songs in a queue.\nqueue peek [NAME]"},
        {"queue list", "Lists all of the created queues.\n\nExample:\nqueue list"}
    };

    try {
        std::string cmd = "";
        for(auto & str : args) cmd += str + " ";
        if(cmd != "")
            cmd.pop_back();
        auto & info = h.at(cmd);
        std::cout << info << '\n';
    } catch(...) {
        std::cout << "nonexistent command";
    }
}

void processCMD(std::vector<std::string> & args) {
    static std::unordered_map<std::string, void(*)(std::vector<std::string>&)> cmds = {
        {"download", download},
        {"play", initUi},
        {"queue", qCommands},
        {"list", listMP3s},
        {"help", helpcmd}
    };

    try {
        const auto cmd = *args.begin();
        args.erase(args.begin());
        cmds.at(cmd)(args);
    } catch(...) {
        std::cout << "nonexistent command";
    }
}
