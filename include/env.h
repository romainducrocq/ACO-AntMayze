#ifndef _ENV_H
#define _ENV_H

#include <stdlib.h>

#include "conf.h"

#include "maze2d.h" 

typedef struct env {
    struct env_vt* vt;

    maze2d* maze2d;
} env;

typedef struct env_vt {
    env* (*ctor)();
    void (*dtor)(env*);
} env_vt;

extern const env_vt Env;

#endif