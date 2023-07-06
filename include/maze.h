#ifndef _MAZE_H
#define _MAZE_H

#include <stdio.h>
#include <stdlib.h>

#include "conf.h"

#include "maze_generator.h"

typedef struct maze {
    mazeGenerator* super;
    struct maze_vt* vt;

} maze;

typedef struct maze_vt {
    maze* (*ctor)();
    void (*dtor)(maze*);

} maze_vt;

extern const maze_vt Maze;

#endif
