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
}

static void app_dtor()
{
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
