#ifndef _VIEW_EVENT_H
#define _VIEW_EVENT_H

#include <SDL.h>

#include "conf.h"

#include "env.h"

typedef struct event {
    struct event_vt* vt;

    SDL_Event* event;
    env* env;
} event;

typedef struct event_vt {
    event* (*a)();

    void (*ctor)(SDL_Event*, env*);
    void (*dtor)();

    void (*setup)();
    void (*loop)();

} event_vt;

extern const event_vt Event;

#endif