#include "view.h"

static window* window_ctor();
static void window_dtor(window*);

static void window_render(window*);

const window_vt Window = {
        .ctor = window_ctor,
        .dtor = window_dtor,

        .render = window_render
};

static window* window_ctor()
{
    window* this = (window*)malloc(sizeof(window));

    this->vt = (window_vt*)malloc(sizeof(window_vt));
    *this->vt = Window;

    SDL_Init(SDL_INIT_VIDEO);
    this->window = SDL_CreateWindow("COOL PROJECT VIBE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    CONF.WIN_W, CONF.WIN_H, SDL_WINDOW_RESIZABLE);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);

    this->start = 0;
    this->delay = 1000 / 60.;

    return this;
}

static void window_dtor(window* this)
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    free(this->vt);
    free(this);
}

static void window_render(window* this)
{
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->renderer);
//
    SDL_RenderPresent(this->renderer);

    this->end = SDL_GetTicks();
    if(this->end - this->start < this->delay) {
        SDL_Delay(this->delay + this->start - this->end);
    }
    this->start = this->end;
}

