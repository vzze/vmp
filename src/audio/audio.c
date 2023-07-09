#include <stdlib.h>

#include <audio.h>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

bool engine_init(engine ** instance) {
    *instance = malloc(sizeof(engine));

    return ma_engine_init(NULL, *instance) == MA_SUCCESS;
}

bool sound_init(engine * instance, const char * file, sound ** current) {
    *current = malloc(sizeof(sound));

    return ma_sound_init_from_file(
        instance,
        file,
        MA_SOUND_FLAG_DECODE,
        NULL,
        NULL,
        *current
    ) == MA_SUCCESS;
}

void sound_play       (sound * current              ) {        ma_sound_start            (current        ); }
void sound_stop       (sound * current              ) {        ma_sound_stop             (current        ); }
void sound_rewind     (sound * current              ) {        ma_sound_seek_to_pcm_frame(current, 0     ); }
void sound_set_volume (sound * current, float volume) {        ma_sound_set_volume       (current, volume); }
bool sound_is_playing (sound * current              ) { return ma_sound_is_playing       (current        ); }
void sound_set_looping(sound * current, bool loop   ) {        ma_sound_set_looping      (current, loop  ); }
bool sound_is_looping (sound * current              ) { return ma_sound_is_looping       (current        ); }
bool sound_is_at_end  (sound * current              ) { return ma_sound_at_end           (current        ); }

void sound_free(sound * current) {
    ma_sound_uninit(current);
    free(current);
}

void engine_free(engine * instance) {
    ma_engine_uninit(instance);
    free(instance);
}
