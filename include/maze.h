#ifndef _MAZE_H
#define _MAZE_H

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
    maze* (*ctor)(int w, int h);
    void (*dtor)(maze*);

    int (*_getIndex)(maze*, int x, int y);
    cell* (*_getNextCell)(maze*);
    void (*_removeWalls)(cell* a, cell* b);
    void (*_makeMaze)(maze*);
    void (*_printMaze)(maze*);
} maze_vt;

extern const maze_vt Maze;

#endif
