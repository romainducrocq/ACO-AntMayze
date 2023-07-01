#include <SDL.h>
#include <SDL_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "conf.h"
#include "maze.h"

int main(int argc, char** argv) {
    srand(time(NULL));

    if(argParse(argc, argv))
    {
        {
            maze* m = Maze.ctor(CONF()->WIDTH, CONF()->HEIGHT);
            m->vt->_printMaze(m);
            Maze.dtor(m);
        }

        return 0;
    }

    return 1;
}
