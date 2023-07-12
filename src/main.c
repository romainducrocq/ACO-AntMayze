#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "conf.h"

#include "app.h"

#include "maze2d.h"

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
            maze2d* m = Maze2d.ctor();
            Maze2d.dtor(m);
        }

        {
            App.ctor();
            App.dtor();
        }

        return 0;
    }

    return 1;
}
