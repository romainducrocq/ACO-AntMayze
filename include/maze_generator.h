#ifndef _MAZE_GENERATOR_H
#define _MAZE_GENERATOR_H

#include <stdio.h>
#include <stdlib.h>

#include "conf.h"

typedef struct cell {
    int x;
    int y;
    int walls[4];
    int isVisited;
} cell;

typedef struct mazeGenerator {
    struct mazeGenerator_vt* vt;

    cell* _currentCell;
    int _stackSize;
    cell** _stack;

    int cols;
    int rows;
    cell* cells;
} mazeGenerator;

typedef struct mazeGenerator_vt {
    mazeGenerator* (*ctor)();
    void (*dtor)(mazeGenerator*);

    int (*_getIndex)(mazeGenerator*, int x, int y);
    cell* (*_getNextCell)(mazeGenerator*);
    void (*_removeWalls)(cell* a, cell* b);
    void (*_makeMaze)(mazeGenerator*);
    void (*_printMaze)(mazeGenerator*);
} mazeGenerator_vt;

extern const mazeGenerator_vt MazeGenerator;

#endif
