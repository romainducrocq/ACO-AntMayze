#ifndef _VIEW_RENDERER_H
#define _VIEW_RENDERER_H

#include "conf.h"

typedef struct renderer {
    struct renderer_vt* vt;

} renderer;

typedef struct renderer_vt {
    renderer* (*ctor)();
    void (*dtor)(renderer*);

    void (*setup)(renderer*);
    void (*loop)(renderer*);

} renderer_vt;

extern const renderer_vt Renderer;

#endif