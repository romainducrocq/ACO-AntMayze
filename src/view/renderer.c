#include "view/renderer.h"

static renderer* renderer_a();

static void renderer_ctor(SDL_Renderer*, env*);
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

static void renderer_ctor(SDL_Renderer* _renderer, env* _env)
{
    INSTANCE((renderer*)malloc(sizeof(renderer)));

    Renderer.a()->vt = (renderer_vt*)malloc(sizeof(renderer_vt));
    *Renderer.a()->vt = Renderer;

    Renderer.a()->renderer = _renderer;
    Renderer.a()->env = _env;

    Renderer.a()->mazeSDL = MazeSDL.ctor(Renderer.a()->env);
}

static void renderer_dtor()
{
    MazeSDL.dtor(Renderer.a()->mazeSDL);
    free(Renderer.a()->vt);
    free(Renderer.a());
}

static void renderer_setup()
{
    if(FALSE) {
        Renderer.a()->env->maze2d->super->vt->printMaze(Renderer.a()->env->maze2d->super);
    }
}

static void renderer_loop()
{
    Renderer.a()->mazeSDL->vt->renderMazeSDL(Renderer.a()->mazeSDL, Renderer.a()->renderer);
}
