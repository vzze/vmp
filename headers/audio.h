#ifndef AUDIO_H
#define AUDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cplusplus
#include <stdbool.h>
#include <wchar.h>
#endif

struct ma_engine;
struct ma_sound;

#ifndef __cplusplus
typedef struct ma_engine engine;
typedef struct ma_sound sound;
#else
using engine = struct ma_engine;
using sound  = struct ma_sound;
#endif

bool engine_init(engine **);

bool sound_init(engine *, const char *, sound **);
bool sound_init_w(engine *, const wchar_t *, sound **);

void sound_play       (sound *       );
void sound_stop       (sound *       );
void sound_rewind     (sound *       );
void sound_set_volume (sound *, float);
bool sound_is_playing (sound *       );
void sound_set_looping(sound *, bool );
bool sound_is_looping (sound *       );

void sound_free(sound *);
void engine_free(engine *);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
