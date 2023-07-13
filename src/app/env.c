#include "app/env.h"

static env* env_ctor();
static void env_dtor(env*);

const env_vt Env = {
    .ctor = env_ctor,
    .dtor = env_dtor
};

static env* env_ctor()
{
    env* this = (env*)malloc(sizeof(env));

    this->vt = (env_vt*)malloc(sizeof(env_vt));
    *this->vt = Env;

    this->maze2d = Maze2d.ctor();

    return this;
}

static void env_dtor(env* this)
{
    Maze2d.dtor(this->maze2d);
    free(this->vt);
    free(this);
}