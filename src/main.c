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

            window* w = Window.ctor(
                a->vt->setup, e->vt->setup, r->vt->setup,
                a->vt->loop, e->vt->loop, r->vt->loop
            );

            w->vt->run(w, a , e, r);

            Window.dtor(w);

            App.dtor(a);
            Event.dtor(e);
            Renderer.dtor(r);
        }

        return 0;
    }

    return 1;
}
