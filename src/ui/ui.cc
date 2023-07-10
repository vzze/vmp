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
