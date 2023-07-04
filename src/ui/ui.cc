#include <ui.hh>

vmp::ui::ui(player & current, const ui_opts opts)
    : current_dimensions{},
      sidebar_width{opts.sidebar_width},
      sidebar_stopping_point{opts.sidebar_stopping_point},
      queue_offset{0},
      instance{current}
{}