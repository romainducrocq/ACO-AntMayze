#ifndef _VIEW_EVENT_H
#define _VIEW_EVENT_H

#include "conf.h"

typedef struct event {
    struct event_vt* vt;

} event;

typedef struct event_vt {
    event* (*ctor)();
    void (*dtor)(event*);

    void (*setup)(event*);
    void (*loop)(event*);

} event_vt;

extern const event_vt Event;

#endif