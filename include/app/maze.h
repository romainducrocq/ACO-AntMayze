#ifndef _APP_MAZE_H
#define _APP_MAZE_H

#include <stdio.h>
#include <stdlib.h>

#include "conf.h"

typedef struct cell {
    int x;
    int y;
    int walls[4];
    int isVisited;
} cell;

typedef struct maze {
    struct maze_vt* vt;

    cell* _currentCell;
    int _stackSize;
    cell** _stack;

    int cols;
    int rows;
    cell* cells;
} maze;

typedef struct maze_vt {
    maze* (*ctor)();
    void (*dtor)(maze*);

    cell* (*_getNextCell)(maze*);
    void (*_removeWalls)(cell* a, cell* b);
    void (*_makeMaze)(maze*);

    int (*getIndex)(maze*, int x, int y);
    void (*printMaze)(maze*);
} maze_vt;

extern const maze_vt Maze;

#endif
