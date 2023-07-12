#include "maze2d.h"

static maze2d* maze2d_ctor();
static void maze2d_dtor(maze2d*);

static void maze2d_makeMaze2d(maze2d*);

const maze2d_vt Maze2d = {
    .ctor = maze2d_ctor,
    .dtor = maze2d_dtor,

    ._makeMaze2d = maze2d_makeMaze2d
};

static maze2d* maze2d_ctor()
{
    maze2d* this = (maze2d*)malloc(sizeof(maze2d));

    this->vt = (maze2d_vt*)malloc(sizeof(maze2d_vt));
    *this->vt = Maze2d;

    this->super = Maze.ctor();
    this->super->vt->_printMaze(this->super);

    this->cell2dWidth = CONF.WINDOW_WIDTH / (float)CONF.MAZE_COLS;
    this->cell2dHeight = CONF.WINDOW_HEIGHT / (float)CONF.MAZE_ROWS;

    this->cell2ds = (cell2d*)malloc((this->super->cols * this->super->rows) * sizeof(cell2d));

    this->vt->_makeMaze2d(this);

    return this;
}

static void maze2d_dtor(maze2d* this)
{
    Maze.dtor(this->super);
    free(this->cell2ds);
    free(this->vt);
    free(this);
}

static void maze2d_makeMaze2d(maze2d* this)
{
    int x, y;
    for(y = 0; y < this->super->rows; y++){
        for(x = 0; x < this->super->cols; x++){
            int i = this->super->vt->_getIndex(this->super, x, y);
            this->cell2ds[i].cell = &this->super->cells[i];
            
            this->cell2ds[i].wall2ds[0][0] = x * this->cell2dWidth;
            this->cell2ds[i].wall2ds[0][1] = y * this->cell2dHeight;
            this->cell2ds[i].wall2ds[0][2] = (x+1) * this->cell2dWidth;
            this->cell2ds[i].wall2ds[0][3] = y * this->cell2dHeight;

            this->cell2ds[i].wall2ds[1][0] = (x+1) * this->cell2dWidth;
            this->cell2ds[i].wall2ds[1][1] = y * this->cell2dHeight;
            this->cell2ds[i].wall2ds[1][2] = (x+1) * this->cell2dWidth;
            this->cell2ds[i].wall2ds[1][3] = (y+1) * this->cell2dHeight;

            this->cell2ds[i].wall2ds[2][0] = x * this->cell2dWidth;  
            this->cell2ds[i].wall2ds[2][1] = (y+1) * this->cell2dHeight;
            this->cell2ds[i].wall2ds[2][2] = (x+1) * this->cell2dWidth;
            this->cell2ds[i].wall2ds[2][3] = (y+1) * this->cell2dHeight;

            this->cell2ds[i].wall2ds[3][0] = x * this->cell2dWidth;
            this->cell2ds[i].wall2ds[3][1] = y * this->cell2dHeight;
            this->cell2ds[i].wall2ds[3][2] = x * this->cell2dWidth;
            this->cell2ds[i].wall2ds[3][3] = (y+1) * this->cell2dHeight;
        }
    }
}
