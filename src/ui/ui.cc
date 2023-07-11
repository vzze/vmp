#include <ui.hh>

vmp::ui::ui(player & current, const ui_opts opts)
    : screen_is_too_small{false},
      current_zone{ZONE::QUEUE_TITLE},
      current_dimensions{},
      sidebar_width{opts.sidebar_width},
      sidebar_stopping_point{opts.sidebar_stopping_point},
      queues_offset{0},
      unsorted_songs_offset{0},
      instance{current}
{
    handler.add_key_callback([&](const auto data) -> bool {
            return key_callback(data);
        }
    );

    handler.add_resize_callback([&](const auto data) -> bool {
        return resize_callback(data);
    });

    handler.add_notify_alive_callback([&]() -> bool {
        return notify_alive_callback();
    });

    update_zones_hl_start_pos();
}

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
