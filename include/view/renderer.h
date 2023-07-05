#ifndef _VIEW_RENDERER_H
#define _VIEW_RENDERER_H

#include <SDL.h>
#include <SDL_image/SDL_image.h>

#include "conf.h"

typedef struct renderer {
    struct renderer_vt* vt;

} renderer;

typedef struct renderer_vt {
    renderer* (*a)();

    void (*ctor)();
    void (*dtor)();

    void (*setup)();
    void (*loop)();

} renderer_vt;

extern const renderer_vt Renderer;

#endif