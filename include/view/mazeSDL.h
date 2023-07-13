#ifndef _VIEW_MAZESDL_H
#define _VIEW_MAZESDL_H

#include <stdlib.h>

#include <SDL.h>

#include "conf.h"

#include "app/env.h"

typedef struct mazeSDL {
    struct mazeSDL_vt* vt;

    env* env;
    SDL_Rect bgSDL;
    int wallSDLsLength;
    SDL_Rect* wallSDLs;
} mazeSDL;

typedef struct mazeSDL_vt {
    mazeSDL* (*ctor)(env*);
    void (*dtor)(mazeSDL*);

    void (*_makeMazeSDL)(mazeSDL*);
    
    void (*renderMazeSDL)(mazeSDL*, SDL_Renderer*);
} mazeSDL_vt;

extern const mazeSDL_vt MazeSDL;

#endif