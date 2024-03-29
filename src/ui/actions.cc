#include <ui.hh>

void vmp::ui::up() {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE   : break;
        case ZONE::UNSORTED_TITLE: set_zone(ZONE::QUEUE_TITLE); break;

        default:
            button_up();
        break;
    }
}

void vmp::ui::left() {
    switch(current_zone) {
        case ZONE::QUEUE_LIST   : redraw_default(false); break;
        case ZONE::UNSORTED_LIST: set_zone(ZONE::UNSORTED_TITLE); break;
        case ZONE::MAIN_LIST    : set_zone(ZONE::QUEUE_LIST); break;

        default: break;
    }
}

void vmp::ui::down() {
    switch(current_zone) {
        case ZONE::UNSORTED_TITLE: break;
        case ZONE::QUEUE_TITLE   : set_zone(ZONE::UNSORTED_TITLE); break;

        default:
            button_down();
        break;
    }
}

void vmp::ui::right() {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE:
            if(!zones[ZONE::QUEUE_LIST].buttons.empty()) {
                redraw_slim(false);
                draw_main_list(zones[current_zone].current().id);
            }
        break;
        case ZONE::UNSORTED_TITLE:
            if(!zones[ZONE::UNSORTED_LIST].buttons.empty())
                set_zone(ZONE::UNSORTED_LIST);
        break;
        case ZONE::QUEUE_LIST:
            if(!zones[ZONE::MAIN_LIST].buttons.empty())
                set_zone(ZONE::MAIN_LIST);
        break;

        default: break;
    }
}

void vmp::ui::scroll_up() {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE   : queues_prev_page  (); draw_available_moves(); break;
        case ZONE::UNSORTED_TITLE: unsorted_prev_page(); draw_available_moves(); break;
        case ZONE::QUEUE_LIST:
            main_prev_page(zones[current_zone].current().id);
            draw_available_moves();
        break;

        default: break;
    }
}

void vmp::ui::scroll_down() {
    switch(current_zone) {
        case ZONE::QUEUE_TITLE   : queues_next_page  (); draw_available_moves(); break;
        case ZONE::UNSORTED_TITLE: unsorted_next_page(); draw_available_moves(); break;
        case ZONE::QUEUE_LIST:
            main_next_page(zones[current_zone].current().id);
            draw_available_moves();
        break;

        default: break;
    }
}

void vmp::ui::play() {
    switch(current_zone) {
        case ZONE::QUEUE_LIST:
            if(!zones[ZONE::MAIN_LIST].buttons.empty())
                instance.play_song_from_queue(zones[ZONE::QUEUE_LIST].current().id, 0);
        break;
        case ZONE::MAIN_LIST:
            instance.play_song_from_queue(
                zones[ZONE::QUEUE_LIST].current().id,
                zones[ZONE::MAIN_LIST].current().id
            );

            draw_player_status();
        break;
        case ZONE::UNSORTED_TITLE:
            if(!zones[ZONE::UNSORTED_LIST].buttons.empty()) instance.play_song_from_unsorted(0);
        break;
        case ZONE::UNSORTED_LIST:
            instance.play_song_from_unsorted(
                zones[ZONE::UNSORTED_LIST].current().id
            );

            draw_player_status();
        break;

        default: break;
    }
}

void vmp::ui::toggle_pause_resume() {
    switch(instance.state) {
        case player::STATE::PAUSED: instance.resume(); break;
        case player::STATE::RESUMED: instance.pause(); break;
        default: break;
    }
}

void vmp::ui::volume_up() {
    instance.volume_up();
    draw_player_volume();
}

void vmp::ui::volume_down() {
    instance.volume_down();
    draw_player_volume();
}

void vmp::ui::skip() {
    instance.skip();
    draw_player_status();
}

void vmp::ui::shuffle() {
    switch(current_zone) {
        case ZONE::QUEUE_LIST:
            instance.shuffle_queue(zones[ZONE::QUEUE_LIST].current().id);
            draw_main_list(zones[ZONE::QUEUE_LIST].current().id);
        break;

        case ZONE::UNSORTED_TITLE:
            instance.shuffle_unsorted();
            draw_unsorted_songs();
        break;

        default: break;
    }
}

void vmp::ui::toggle_loop() {
    instance.toggle_loop();
    draw_player_status();
}
