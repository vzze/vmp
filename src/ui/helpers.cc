#include <ui.hh>

void vmp::ui::format_str_len(std::string & name, cu32 max_len, bool elongate) {
    static constexpr std::string_view filler = "...";

    if(name.length() >= max_len) {
        name.resize(max_len - filler.size());
        name += filler;
    } else if(elongate) {
        name.resize(max_len, ' ');
    }
}

std::string vmp::ui::format_row(std::string name, cu32 max_len, bool elongate) {
    static constexpr std::string_view filler = "...";

    if(name.length() >= max_len) {
        name.resize(max_len - filler.size());
        name += filler;
    } else if(elongate) {
        name.resize(max_len, ' ');
    }

    return name;
}
