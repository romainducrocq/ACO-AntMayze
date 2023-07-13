#include "maze.h"

static maze* maze_ctor();
static void maze_dtor(maze*);

static cell* maze_getNextCell(maze*);
static void maze_removeWalls(cell* a, cell* b);
static void maze_makeMaze(maze*);

static int maze_getIndex(maze*, int x, int y);
static void maze_printMaze(maze*);

const maze_vt Maze = {
    .ctor = maze_ctor,
    .dtor = maze_dtor,

    ._getNextCell = maze_getNextCell,
    ._removeWalls = maze_removeWalls,
    ._makeMaze = maze_makeMaze,

    .getIndex = maze_getIndex,
    .printMaze = maze_printMaze,
};

static maze* maze_ctor()
{
    maze* this = (maze*)malloc(sizeof(maze));

    this->vt = (maze_vt*)malloc(sizeof(maze_vt));
    *this->vt = Maze;

    this->cols = CONF.MAZE_COLS;
    this->rows = CONF.MAZE_ROWS;

    this->cells = (cell*)malloc((this->cols * this->rows) * sizeof(cell));
    this->_stack = (cell**)malloc((this->cols * this->rows) * sizeof(cell*));

    this->vt->_makeMaze(this);

    return this;
}

static void maze_dtor(maze* this)
{
    free(this->cells);
    free(this->_stack);
    free(this->vt);
    free(this);
}

static cell* maze_getNextCell(maze* this)
{
    int n = 0;
    cell* neighborCells[4] = {
       &this->cells[this->vt->getIndex(this, this->_currentCell->x, this->_currentCell->y-1)],
       &this->cells[this->vt->getIndex(this, this->_currentCell->x-1, this->_currentCell->y)],
       &this->cells[this->vt->getIndex(this, this->_currentCell->x, this->_currentCell->y+1)],
       &this->cells[this->vt->getIndex(this, this->_currentCell->x+1, this->_currentCell->y)],
    };

    if(this->_currentCell->y > 0 && neighborCells[0]->isVisited == FALSE){
        neighborCells[n++] = neighborCells[0];
    }
    if(this->_currentCell->x > 0 && neighborCells[1]->isVisited == FALSE){
        neighborCells[n++] = neighborCells[1];
    }
    if(this->_currentCell->y < this->rows - 1 && neighborCells[2]->isVisited == FALSE){
        neighborCells[n++] = neighborCells[2];
    }
    if(this->_currentCell->x < this->cols - 1 && neighborCells[3]->isVisited == FALSE){
        neighborCells[n++] = neighborCells[3];
    }

    if(n > 0) {
        return neighborCells[rand() % n];
    }

    return NULL;
}

static void maze_removeWalls(cell* a, cell* b)
{
    if(abs(a->x - b->x) == 1){
        a->walls[2 + a->x - b->x] = FALSE;
        b->walls[2 - a->x + b->x] = FALSE;
    } else {
        a->walls[1 - a->y + b->y] = FALSE;
        b->walls[1 + a->y - b->y] = FALSE;
    }
}

static void maze_makeMaze(maze* this)
{
    int x, y;
    for(y = 0; y < this->rows; y++){
        for(x = 0; x < this->cols; x++){
            int i = this->vt->getIndex(this, x, y);
            this->cells[i].x = x;
            this->cells[i].y = y;
            int n;
            for(n = 0; n < 4; n++) {
                this->cells[i].walls[n] = TRUE;
            }
            this->cells[i].isVisited = FALSE;
        }
    }

    this->_stackSize = 0;
    this->_currentCell = &this->cells[rand() % (this->cols * this->rows)];

    while(TRUE){
        this->_currentCell->isVisited = TRUE;
        cell* nextCell = this->vt->_getNextCell(this);
        if(nextCell != NULL) {
            nextCell->isVisited = TRUE;
            this->_stack[++this->_stackSize] = this->_currentCell;
            this->vt->_removeWalls(this->_currentCell, nextCell);
            this->_currentCell = nextCell;
        } else if(this->_stackSize > 0) {
            this->_currentCell = this->_stack[this->_stackSize--];
        } else {
            break;
        }
    }
}

static int maze_getIndex(maze* this, int x, int y)
{
    return x + y * this->cols;
}

static void maze_printMaze(maze* this)
{
    int x, y;
    for (x = 0; x < this->cols; x++) {
        printf(" _");
    }
    printf("\n");
    for (y = 0; y < this->rows; y++) {
        for (x = 0; x < this->cols; x++) {
            if (this->cells[this->vt->getIndex(this, x, y)].walls[2] == FALSE &&
                this->cells[this->vt->getIndex(this, x, y)].walls[3] == FALSE) {
                printf("  ");
            } else if (this->cells[this->vt->getIndex(this, x, y)].walls[2] == FALSE) {
                printf("| ");
            } else if (this->cells[this->vt->getIndex(this, x, y)].walls[3] == FALSE) {
                printf(" _");
            } else {
                printf("|_");
            }
        }
        printf("|\n");
    }
}
