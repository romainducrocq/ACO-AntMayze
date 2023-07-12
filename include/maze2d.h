#ifndef _MAZE_H
#define _MAZE_H

#include <stdio.h>
#include <stdlib.h>

#include "conf.h"

#include "maze.h"

typedef struct cell2d{
    cell* cell;
    int walls[4][4];
} cell2d;

typedef struct maze2d {
    maze* super;
    struct maze2d_vt* vt;

} maze2d;

typedef struct maze2d_vt {
    maze2d* (*ctor)();
    void (*dtor)(maze2d*);

} maze2d_vt;

extern const maze2d_vt Maze2d;

#endif
