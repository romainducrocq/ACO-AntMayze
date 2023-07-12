#ifndef _APP_H
#define _APP_H

#include <stdlib.h>

#include "conf.h"

#include "util/window.h"
#include "env.h"
#include "view/event.h"
#include "view/renderer.h"

typedef struct app {
    window* super;
    struct app_vt* vt;

    env* env;
} app;

typedef struct app_vt {
    app* (*a)();

    void (*ctor)();
    void (*dtor)();

    void (*setup)();
    int (*loop)();

} app_vt;

extern const app_vt App;

#endif