#include <stdlib.h>
#include <time.h>

#include "conf.h"

#include "app.h"

// #include "maze2d.h"

conf CONF = {
    .MAZE_COLS = 20,
    .MAZE_ROWS = 20,

    .WINDOW_WIDTH = 1280,
    .WINDOW_HEIGHT = 720
};

int main(int argc, char** argv) {
    srand(time(NULL));

    if(argParse(argc, argv))
    {
        /*
        {
            maze2d* m = Maze2d.ctor();
            Maze2d.dtor(m);
        }
        return 0;
        */

        {
            App.ctor();
            App.dtor();
        }

        return 0;
    }

    return 1;
}
