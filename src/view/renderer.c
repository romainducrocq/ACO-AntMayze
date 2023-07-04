#include "view/renderer.h"

static renderer* renderer_ctor();
static void renderer_dtor(renderer*);

static void renderer_setup(renderer*);
static void renderer_loop(renderer*);

const renderer_vt Renderer = {
    .ctor = renderer_ctor,
    .dtor = renderer_dtor,

    .setup = renderer_setup,
    .loop = renderer_loop
};

static renderer* renderer_ctor()
{
    renderer* this = (renderer*)malloc(sizeof(renderer));

    this->vt = (renderer_vt*)malloc(sizeof(renderer_vt));
    *this->vt = Renderer;

    return this;
}

static void renderer_dtor(renderer* this)
{
    free(this->vt);
    free(this);
}

static void renderer_setup(renderer* this)
{
    if(this == NULL) { return; }

}

static void renderer_loop(renderer* this)
{
    if(this == NULL) { return; }
}
