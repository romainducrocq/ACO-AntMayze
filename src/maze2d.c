#include "maze2d.h"

static maze2d* maze2d_ctor();
static void maze2d_dtor(maze2d*);

const maze2d_vt Maze2d = {
    .ctor = maze2d_ctor,
    .dtor = maze2d_dtor
};

static maze2d* maze2d_ctor()
{
    maze2d* this = (maze2d*)malloc(sizeof(maze2d));

    this->vt = (maze2d_vt*)malloc(sizeof(maze2d_vt));
    *this->vt = Maze2d;

    this->super = Maze.ctor();
    this->super->vt->_printMaze(this->super);

    return this;
}

static void maze2d_dtor(maze2d* this)
{
    Maze.dtor(this->super);
    free(this->vt);
    free(this);
}
