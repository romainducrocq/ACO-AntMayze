#include "view/renderer.h"

static renderer* renderer_a();

static void renderer_ctor(SDL_Renderer*);
static void renderer_dtor();

static void renderer_setup();
static void renderer_loop();

static renderer* INSTANCE(renderer* instance)
{
    static renderer* singleton;
    if(instance != NULL) {
        singleton = instance;
    }
    return singleton;
}

static renderer* renderer_a()
{
    return INSTANCE(NULL);
}

const renderer_vt Renderer = {
    .a = renderer_a,

    .ctor = renderer_ctor,
    .dtor = renderer_dtor,

    .setup = renderer_setup,
    .loop = renderer_loop
};

static void renderer_ctor(SDL_Renderer* _renderer)
{
    INSTANCE((renderer*)malloc(sizeof(renderer)));

    Renderer.a()->vt = (renderer_vt*)malloc(sizeof(renderer_vt));
    *Renderer.a()->vt = Renderer;

    Renderer.a()->renderer = _renderer;
}

static void renderer_dtor()
{
    free(Renderer.a()->vt);
    free(Renderer.a());
}

static void renderer_setup()
{
    Renderer.a()->rect.x = 50;
    Renderer.a()->rect.y = 50;
    Renderer.a()->rect.w = 50;
    Renderer.a()->rect.h = 50;
}

static void renderer_loop()
{
    SDL_SetRenderDrawColor(Renderer.a()->renderer, 0, 0, 255, 255 );
    SDL_RenderFillRect(Renderer.a()->renderer, &Renderer.a()->rect);
}
