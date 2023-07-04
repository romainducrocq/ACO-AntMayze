#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "conf.h"

#include "app.h"
#include "view/event.h"
#include "view/renderer.h"
#include "util/window.h"

#include "maze.h"

conf CONF = {
    .WIDTH = 20,
    .HEIGHT = 20,

    .WIN_W = 1920,
    .WIN_H = 1080
};

int main(int argc, char** argv) {
    srand(time(NULL));

    if(argParse(argc, argv))
    {
        {
            maze* m = Maze.ctor();
            m->vt->_printMaze(m);
            Maze.dtor(m);
        }

        {
            app* a = App.ctor();
            event* e = Event.ctor();
            renderer* r = Renderer.ctor();

            Window.ctor(
                a->vt->setup, e->vt->setup, r->vt->setup,
                a->vt->loop, e->vt->loop, r->vt->loop
            );

            Window.a()->vt->run(a , e, r);

            Window.dtor();

            App.dtor(a);
            Event.dtor(e);
            Renderer.dtor(r);
        }

        return 0;
    }

    return 1;
}
