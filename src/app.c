#include "app.h"

static app* app_a();

static void app_ctor();
static void app_dtor();

static void app_setup();
static int app_loop();

const app_vt App = {
    .a = app_a,

    .ctor = app_ctor,
    .dtor = app_dtor,

    .setup = app_setup,
    .loop = app_loop
};

static app* INSTANCE(app* instance)
{
    static app* singleton;
    if(instance != NULL) {
        singleton = instance;
    }
    return singleton;
}

static app* app_a()
{
    return INSTANCE(NULL);
}

static void app_ctor()
{
    INSTANCE((app*)malloc(sizeof(app)));

    App.a()->vt = (app_vt*)malloc(sizeof(app_vt));
    *App.a()->vt = App;

    Event.ctor(NULL);
    Renderer.ctor(NULL);

    Window.ctor(
        App.a()->vt->setup, Event.a()->vt->setup, Renderer.a()->vt->setup,
        App.a()->vt->loop, Event.a()->vt->loop, Renderer.a()->vt->loop
    );

    App.a()->super = Window.a();

    Event.a()->event = &App.a()->super->event;
    Renderer.a()->renderer = App.a()->super->renderer;

    App.a()->super->vt->run(App.a() , Event.a(), Renderer.a());
}

static void app_dtor()
{
    Window.dtor();

    Event.dtor();
    Renderer.dtor();

    free(App.a()->vt);
    free(App.a());
}

static void app_setup()
{
    if(App.a() == NULL) { return; }

}

static int app_loop()
{
    if(App.a() == NULL) { return FALSE; }
    return TRUE;
}
