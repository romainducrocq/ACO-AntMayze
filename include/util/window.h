#ifndef _UTIL_WINDOW_H
#define _UTIL_WINDOW_H

#include <stdlib.h>

#include <SDL.h>

#include "conf.h"

typedef struct window {
    struct window_vt* vt;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    double _start;
    double _end;
    double _delay;
    int _bgCol[3];
} window;

typedef struct app app;
typedef struct renderer renderer;
typedef struct event event;

typedef struct window_vt {
    window* (*a)();

    void (*ctor)(
        void (*)(app*), void (*)(event*), void (*)(renderer*),
        int (*)(app*), void (*)(event*), void (*)(renderer*));

    void (*dtor)();

    void (*_setup)(app*, event*, renderer*);
    void (*_loop)(app*, event*, renderer*);

    void (*run)(app*, event*, renderer*);

    void (*_event_setup)(event*);
    void (*_renderer_setup)(renderer*);
    void (*_app_setup)(app*);
    void (*_event_loop)(event*);
    void (*_renderer_loop)(renderer*);
    int (*_app_loop)(app*);

} window_vt;

extern const window_vt Window;

#endif