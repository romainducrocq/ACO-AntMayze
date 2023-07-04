#ifndef _APP_H
#define _APP_H

#include "conf.h"

typedef struct app {
    struct app_vt* vt;

} app;

typedef struct app_vt {
    app* (*ctor)();
    void (*dtor)(app*);

    void (*setup)(app*);
    int (*loop)(app*);

} app_vt;

extern const app_vt App;

#endif