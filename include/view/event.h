#ifndef _VIEW_EVENT_H
#define _VIEW_EVENT_H

#include <SDL.h>

#include "conf.h"

typedef struct event {
    struct event_vt* vt;

} event;

typedef struct event_vt {
    event* (*a)();

    void (*ctor)();
    void (*dtor)();

    void (*setup)();
    void (*loop)();

} event_vt;

extern const event_vt Event;

#endif