#ifndef _VIEW_EVENT_H
#define _VIEW_EVENT_H

#include <SDL.h>

#include "conf.h"

typedef struct event {
    struct event_vt* vt;

    SDL_Event* event;
} event;

typedef struct event_vt {
    event* (*a)();

    void (*ctor)(SDL_Event*);
    void (*dtor)();

    void (*setup)();
    void (*loop)();

} event_vt;

extern const event_vt Event;

#endif