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
            App.ctor();
            Event.ctor();
            Renderer.ctor();

            Window.ctor(
                App.a()->vt->setup, Event.a()->vt->setup, Renderer.a()->vt->setup,
                App.a()->vt->loop, Event.a()->vt->loop, Renderer.a()->vt->loop
            );

            Window.a()->vt->run(App.a() , Event.a(), Renderer.a());

            Window.dtor();

            App.dtor();
            Event.dtor();
            Renderer.dtor();
        }

        return 0;
    }

    return 1;
}
