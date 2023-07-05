#ifndef _APP_H
#define _APP_H

#include "conf.h"

typedef struct app {
    struct app_vt* vt;

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