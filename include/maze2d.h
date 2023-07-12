#ifndef _MAZE2D_H
#define _MAZE2D_H

#include <stdlib.h>

#include "conf.h"

#include "maze.h"

typedef struct cell2d{
    cell* cell;
    int wall2ds[4][4];
} cell2d;

typedef struct maze2d {
    maze* super;
    struct maze2d_vt* vt;

    int cell2dWidth;
    int cell2dHeight;
    cell2d* cell2ds;
} maze2d;

typedef struct maze2d_vt {
    maze2d* (*ctor)();
    void (*dtor)(maze2d*);

    void (*_makeMaze2d)(maze2d*);
} maze2d_vt;

extern const maze2d_vt Maze2d;

#endif
