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

void vmp::ui::add_highlight_selected(const coord pos, const std::string_view start, const std::string_view end) {
    handler.set_cursor_pos(pos);
    handler.write(start);

    switch(current_zone) {
        case ZONE::QUEUE_TITLE:
            handler.write(QUEUE_LIST_TITLE);
        break;
        case ZONE::UNSORTED_TITLE:
            handler.write(UNSORTED_LIST_TITLE);
        break;
        case ZONE::QUEUE_LIST:
            handler.write(
                format_row(
                    instance.queues[zones[ZONE::QUEUE_LIST].current().id].name(),
                    sidebar_width - ROW_START,
                    false
                )
            );
        break;
        case ZONE::UNSORTED_LIST:
            handler.write(
                format_row(
                    instance.unsorted.songs[zones[ZONE::UNSORTED_LIST].current().id].name(),
                    sidebar_width - ROW_START,
                    false
                )
            );
        break;
        case ZONE::MAIN_LIST:
            handler.write(
                format_row(
                    instance.queues[zones[ZONE::QUEUE_LIST].current().id].songs[zones[ZONE::MAIN_LIST].current().id].name(),
                    current_dimensions.column - ROW_START - sidebar_width + 1,
                    false
                )
            );
        break;

        default: break;
    }

    handler.write(end);
}
