#include "maze_generator.h"

static mazeGenerator* mazeGenerator_ctor();
static void mazeGenerator_dtor(mazeGenerator*);

static int mazeGenerator_getIndex(mazeGenerator*, int x, int y);
static cell* mazeGenerator_getNextCell(mazeGenerator*);
static void mazeGenerator_removeWalls(cell* a, cell* b);
static void mazeGenerator_makeMaze(mazeGenerator*);
static void mazeGenerator_printMaze(mazeGenerator*);

const mazeGenerator_vt MazeGenerator = {
    .ctor = mazeGenerator_ctor,
    .dtor = mazeGenerator_dtor,

    ._getIndex = mazeGenerator_getIndex,
    ._getNextCell = mazeGenerator_getNextCell,
    ._removeWalls = mazeGenerator_removeWalls,
    ._makeMaze = mazeGenerator_makeMaze,
    ._printMaze = mazeGenerator_printMaze
};

static mazeGenerator* mazeGenerator_ctor()
{
    mazeGenerator* this = (mazeGenerator*)malloc(sizeof(mazeGenerator));

    this->vt = (mazeGenerator_vt*)malloc(sizeof(mazeGenerator_vt));
    *this->vt = MazeGenerator;

    this->cols = CONF.WIDTH;
    this->rows = CONF.HEIGHT;

    this->cells = (cell*)malloc((this->cols * this->rows) * sizeof(cell));
    this->_stack = (cell**)malloc((this->cols * this->rows) * sizeof(cell*));

    this->vt->_makeMaze(this);

    return this;
}

static void mazeGenerator_dtor(mazeGenerator* this)
{
    free(this->cells);
    free(this->_stack);
    free(this->vt);
    free(this);
}

static int mazeGenerator_getIndex(mazeGenerator* this, int x, int y)
{
    return x + y * this->cols;
}

static cell* mazeGenerator_getNextCell(mazeGenerator* this)
{
    int n = 0;
    cell* neighborCells[4] = {
       &this->cells[this->vt->_getIndex(this, this->_currentCell->x, this->_currentCell->y-1)],
       &this->cells[this->vt->_getIndex(this, this->_currentCell->x-1, this->_currentCell->y)],
       &this->cells[this->vt->_getIndex(this, this->_currentCell->x, this->_currentCell->y+1)],
       &this->cells[this->vt->_getIndex(this, this->_currentCell->x+1, this->_currentCell->y)],
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

static void mazeGenerator_removeWalls(cell* a, cell* b)
{
    if(abs(a->x - b->x) == 1){
        a->walls[2 + a->x - b->x] = FALSE;
        b->walls[2 - a->x + b->x] = FALSE;
    } else {
        a->walls[1 - a->y + b->y] = FALSE;
        b->walls[1 + a->y - b->y] = FALSE;
    }
}

static void mazeGenerator_makeMaze(mazeGenerator* this)
{
    int x, y;
    for(y = 0; y < this->rows; y++){
        for(x = 0; x < this->cols; x++){
            int i = this->vt->_getIndex(this, x, y);
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

static void mazeGenerator_printMaze(mazeGenerator* this)
{
    int x, y;
    for (x = 0; x < this->cols; x++) {
        printf(" _");
    }
    printf("\n");
    for (y = 0; y < this->rows; y++) {
        for (x = 0; x < this->cols; x++) {
            if (this->cells[this->vt->_getIndex(this, x, y)].walls[2] == FALSE &&
                this->cells[this->vt->_getIndex(this, x, y)].walls[3] == FALSE) {
                printf("  ");
            } else if (this->cells[this->vt->_getIndex(this, x, y)].walls[2] == FALSE) {
                printf("| ");
            } else if (this->cells[this->vt->_getIndex(this, x, y)].walls[3] == FALSE) {
                printf(" _");
            } else {
                printf("|_");
            }
        }
        printf("|\n");
    }
}