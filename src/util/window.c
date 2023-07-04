#include "util/window.h"

static window* window_ctor(
    void (*)(event*), void (*)(renderer*), void (*)(app*),
    void (*)(event*), void (*)(renderer*), int (*)(app*));
static void window_dtor(window*);

static void window_setup(window*, app*, renderer*, event*);
static void window_loop(window*, app*, renderer*, event*);

static void window_run(window*, app*, renderer*, event*);

const window_vt Window = {
        .ctor = window_ctor,
        .dtor = window_dtor,

        ._setup = window_setup,
        ._loop = window_loop,

        .run = window_run,

        ._event_setup = NULL,
        ._renderer_setup = NULL,
        ._app_setup = NULL,
        ._event_loop = NULL,
        ._renderer_loop = NULL,
        ._app_loop = NULL
};

static window* window_ctor(
    void (*event_setup)(event*), void (*renderer_setup)(renderer*), void (*app_setup)(app*),
    void (*event_loop)(event*), void (*renderer_loop)(renderer*), int (*app_loop)(app*)
) {
    window* this = (window*)malloc(sizeof(window));

    this->vt = (window_vt*)malloc(sizeof(window_vt));
    *this->vt = Window;

    this->vt->_event_setup = event_setup;
    this->vt->_renderer_setup = renderer_setup;
    this->vt->_app_setup = app_setup;
    this->vt->_event_loop = event_loop;
    this->vt->_renderer_loop = renderer_loop;
    this->vt->_app_loop = app_loop;

    SDL_Init(SDL_INIT_VIDEO);
    this->window = SDL_CreateWindow("COOL PROJECT VIBE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    CONF.WIN_W, CONF.WIN_H, SDL_WINDOW_RESIZABLE);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);

    this->_start = 0;
    this->_delay = 1000 / 60.;
    this->_bgCol[0] = 220;
    this->_bgCol[1] = 220;
    this->_bgCol[2] = 220;

    return this;
}

static void window_dtor(window* this)
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    free(this->vt);
    free(this);
}

static void window_run(window* this, app* app, renderer* renderer, event* event)
{
    this->vt->_setup(this, app, renderer, event);
    this->vt->_loop(this, app, renderer, event);
}

static void window_setup(window* this, app* app, renderer* renderer, event* event)
{
    this->vt->_event_setup(event);
    this->vt->_app_setup(app);
    this->vt->_renderer_setup(renderer);
}

static void window_loop(window* this, app* app, renderer* renderer, event* event)
{
    while(TRUE) {
        SDL_PollEvent(&this->event);
        if(this->event.type == SDL_QUIT) {
            break;
        }
        this->vt->_event_loop(event);

        if(this->vt->_app_loop(app) == FALSE) {
            break;
        }

        SDL_SetRenderDrawColor(this->renderer,this->_bgCol[0],
                               this->_bgCol[1],this->_bgCol[2],255);
        SDL_RenderClear(this->renderer);
        this->vt->_renderer_loop(renderer);
        SDL_RenderPresent(this->renderer);

        this->_end = SDL_GetTicks();
        if(this->_end - this->_start < this->_delay) {
            SDL_Delay(this->_delay + this->_start - this->_end);
        }
        this->_start = this->_end;
    }
}
