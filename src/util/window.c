#include "util/window.h"

static window* window_a();

static void window_ctor(
    void (*)(app*), void (*)(event*), void (*)(renderer*),
    int (*)(app*), void (*)(event*), void (*)(renderer*));
static void window_dtor();

static void window_setup(app*, event*, renderer*);
static void window_loop(app*, event*, renderer*);

static void window_run(app*, event*, renderer*);

const window_vt Window = {
        .a = window_a,

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

static window* INSTANCE(window* instance)
{
    static window* singleton;
    if(instance != NULL) {
        singleton = instance;
    }
    return singleton;
}

static window* window_a()
{
    return INSTANCE(NULL);
}

static void window_ctor(
    void (*app_setup)(app*), void (*event_setup)(event*), void (*renderer_setup)(renderer*),
    int (*app_loop)(app*), void (*event_loop)(event*), void (*renderer_loop)(renderer*)
) {
    INSTANCE((window*)malloc(sizeof(window)));

    Window.a()->vt = (window_vt*)malloc(sizeof(window_vt));
    *Window.a()->vt = Window;

    Window.a()->vt->_event_setup = event_setup;
    Window.a()->vt->_renderer_setup = renderer_setup;
    Window.a()->vt->_app_setup = app_setup;
    Window.a()->vt->_event_loop = event_loop;
    Window.a()->vt->_renderer_loop = renderer_loop;
    Window.a()->vt->_app_loop = app_loop;

    SDL_Init(SDL_INIT_VIDEO);
    Window.a()->window = SDL_CreateWindow("THE NICHE META PROJECT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    CONF.WINDOW_WIDTH, CONF.WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    Window.a()->renderer = SDL_CreateRenderer(Window.a()->window, -1, SDL_RENDERER_SOFTWARE);

    Window.a()->_start = 0;
    Window.a()->_delay = 1000 / 60.;
    Window.a()->_bgCol[0] = 51;
    Window.a()->_bgCol[1] = 51;
    Window.a()->_bgCol[2] = 51;
}

static void window_dtor()
{
    SDL_DestroyRenderer(Window.a()->renderer);
    SDL_DestroyWindow(Window.a()->window);

    free(Window.a()->vt);
    free(Window.a());
}

static void window_run(app* app, event* event, renderer* renderer)
{
    Window.a()->vt->_setup(app, event, renderer);
    Window.a()->vt->_loop(app, event, renderer);
}

static void window_setup(app* app, event* event, renderer* renderer)
{
    Window.a()->vt->_event_setup(event);
    Window.a()->vt->_app_setup(app);
    Window.a()->vt->_renderer_setup(renderer);
}

static void window_loop(app* app, event* event, renderer* renderer)
{
    while(TRUE) {
        SDL_PollEvent(&Window.a()->event);
        if(Window.a()->event.type == SDL_QUIT) {
            break;
        }
        Window.a()->vt->_event_loop(event);

        if(Window.a()->vt->_app_loop(app) == FALSE) {
            break;
        }

        SDL_SetRenderDrawColor(Window.a()->renderer,Window.a()->_bgCol[0],
                               Window.a()->_bgCol[1],Window.a()->_bgCol[2],255);
        SDL_RenderClear(Window.a()->renderer);
        Window.a()->vt->_renderer_loop(renderer);
        SDL_RenderPresent(Window.a()->renderer);

        Window.a()->_end = SDL_GetTicks();
        if(Window.a()->_end - Window.a()->_start < Window.a()->_delay) {
            SDL_Delay(Window.a()->_delay + Window.a()->_start - Window.a()->_end);
        }
        Window.a()->_start = Window.a()->_end;
    }
}
