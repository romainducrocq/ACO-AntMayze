#ifndef _VIEW_H
#define _VIEW_H

#include <SDL.h>
#include <SDL_image/SDL_image.h>

#include "conf.h"

typedef struct window {
    struct window_vt* vt;

    SDL_Window* window;
    SDL_Renderer* renderer;

    double start;
    double end;
    double delay;
} window;

typedef struct window_vt {
    window* (*ctor)();
    void (*dtor)(window*);

    void (*render)(window*);
} window_vt;

extern const window_vt Window;

#endif