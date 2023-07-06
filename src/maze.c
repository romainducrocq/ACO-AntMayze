#include "maze.h"

static maze* maze_ctor();
static void maze_dtor(maze*);

const maze_vt Maze = {
        .ctor = maze_ctor,
        .dtor = maze_dtor
};

static maze* maze_ctor()
{
    maze* this = (maze*)malloc(sizeof(maze));

    this->vt = (maze_vt*)malloc(sizeof(maze_vt));
    *this->vt = Maze;

    this->super = MazeGenerator.ctor();
    this->super->vt->_printMaze(this->super);

    return this;
}

static void maze_dtor(maze* this)
{
    MazeGenerator.dtor(this->super);
    free(this->vt);
    free(this);
}
