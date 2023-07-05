#include "view/renderer.h"

static renderer* renderer_a();

static void renderer_ctor();
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

static void renderer_ctor()
{
    INSTANCE((renderer*)malloc(sizeof(renderer)));

    Renderer.a()->vt = (renderer_vt*)malloc(sizeof(renderer_vt));
    *Renderer.a()->vt = Renderer;
}

static void renderer_dtor()
{
    free(Renderer.a()->vt);
    free(Renderer.a());
}

static void renderer_setup()
{
    if(Renderer.a() == NULL) { return; }

}

static void renderer_loop()
{
    if(Renderer.a() == NULL) { return; }
}
