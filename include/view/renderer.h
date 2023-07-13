#ifndef _VIEW_RENDERER_H
#define _VIEW_RENDERER_H

#include <stdlib.h>

#include <SDL.h>
#include <SDL_image/SDL_image.h>

#include "conf.h"

#include "app/env.h"
#include "view/mazeSDL.h"

typedef struct renderer {
    struct renderer_vt* vt;

    SDL_Renderer* renderer;
    env* env;

    mazeSDL* mazeSDL;
} renderer;

typedef struct renderer_vt {
    renderer* (*a)();

    void (*ctor)(SDL_Renderer*, env*);
    void (*dtor)();

    void (*setup)();
    void (*loop)();

} renderer_vt;

extern const renderer_vt Renderer;

#endif