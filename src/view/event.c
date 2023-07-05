#include "view/event.h"

static event* event_a();

static void event_ctor();
static void event_dtor();

static void event_setup();
static void event_loop();

const event_vt Event = {
    .a = event_a,

    .ctor = event_ctor,
    .dtor = event_dtor,

    .setup = event_setup,
    .loop = event_loop
};

static event* INSTANCE(event* instance)
{
    static event* singleton;
    if(instance != NULL) {
        singleton = instance;
    }
    return singleton;
}

static event* event_a()
{
    return INSTANCE(NULL);
}

static void event_ctor()
{
    INSTANCE((event*)malloc(sizeof(event)));

    Event.a()->vt = (event_vt*)malloc(sizeof(event_vt));
    *Event.a()->vt = Event;
}

static void event_dtor()
{
    free(Event.a()->vt);
    free(Event.a());
}

static void event_setup()
{
    if(Event.a() == NULL) { return; }

}

static void event_loop()
{
    if(Event.a() == NULL) { return; }
}
