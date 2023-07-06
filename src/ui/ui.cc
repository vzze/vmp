#include <ui.hh>

vmp::ui::ui(player & current, const ui_opts opts)
    : screen_is_too_small{false},
      current_zone{ZONE::QUEUE_TITLE},
      current_dimensions{},
      sidebar_width{opts.sidebar_width},
      sidebar_stopping_point{opts.sidebar_stopping_point},
      queues_offset{0},
      unsorted_songs_offset{0},
      main_offset{0},
      instance{current}
{
    update_zones_hl_start_pos();
}
