#include "view/event.h"

static event* event_ctor();
static void event_dtor(event*);

static void event_setup(event*);
static void event_loop(event*);

const event_vt Event = {
    .ctor = event_ctor,
    .dtor = event_dtor,

    .setup = event_setup,
    .loop = event_loop
};

static event* event_ctor()
{
    event* this = (event*)malloc(sizeof(event));

    this->vt = (event_vt*)malloc(sizeof(event_vt));
    *this->vt = Event;

    return this;
}

static void event_dtor(event* this)
{
    free(this->vt);
    free(this);
}

static void event_setup(event* this)
{
    if(this == NULL) { return; }

}

static void event_loop(event* this)
{
    if(this == NULL) { return; }
}
