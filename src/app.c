#include "app.h"

static app* app_ctor();
static void app_dtor(app*);

static void app_setup(app*);
static int app_loop(app*);

const app_vt App = {
    .ctor = app_ctor,
    .dtor = app_dtor,

    .setup = app_setup,
    .loop = app_loop
};

static app* app_ctor()
{
    app* this = (app*)malloc(sizeof(app));

    this->vt = (app_vt*)malloc(sizeof(app_vt));
    *this->vt = App;

    return this;
}

static void app_dtor(app* this)
{
    free(this->vt);
    free(this);
}

static void app_setup(app* this)
{
    if(this == NULL) { return; }

}

static int app_loop(app* this)
{
    if(this == NULL) { return FALSE; }
    return TRUE;
}
