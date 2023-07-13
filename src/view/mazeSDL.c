#include "view/mazeSDL.h"

static mazeSDL* mazeSDL_ctor(env*);
static void mazeSDL_dtor(mazeSDL*);

static void mazeSDL_makeMazeSDL(mazeSDL*);

static void mazeSDL_renderMazeSDL(mazeSDL*, SDL_Renderer*);

const mazeSDL_vt MazeSDL = {
    .ctor = mazeSDL_ctor,
    .dtor = mazeSDL_dtor,

    ._makeMazeSDL = mazeSDL_makeMazeSDL,

    .renderMazeSDL = mazeSDL_renderMazeSDL
};

static mazeSDL* mazeSDL_ctor(env* _env)
{
    mazeSDL* this = (mazeSDL*)malloc(sizeof(mazeSDL));

    this->vt = (mazeSDL_vt*)malloc(sizeof(mazeSDL_vt));
    *this->vt = MazeSDL;

    this->env = _env;

    this->bgSDL.x = 0;
    this->bgSDL.y = 0;
    this->bgSDL.w = this->env->maze2d->super->cols * this->env->maze2d->cell2dWidth;
    this->bgSDL.h = this->env->maze2d->super->rows * this->env->maze2d->cell2dHeight;

    this->wallSDLsLength = (this->env->maze2d->super->cols-1) *
                            (this->env->maze2d->super->rows-1);

    this->wallSDLs = (SDL_Rect*)malloc(this->wallSDLsLength * sizeof(SDL_Rect));

    this->vt->_makeMazeSDL(this);

    return this;
}

static void mazeSDL_dtor(mazeSDL* this)
{
    free(this->wallSDLs);
    free(this->vt);
    free(this);
}

static void mazeSDL_makeMazeSDL(mazeSDL* this)
{
    int x, y;
    int n = 0;
    for(y = 0; y < this->env->maze2d->super->rows; y++){
        for(x = 0; x < this->env->maze2d->super->cols; x++){
            int i = this->env->maze2d->super->vt->getIndex(this->env->maze2d->super, x, y);

            if(this->env->maze2d->cell2ds[i].cell->walls[1] == TRUE && 
               x < this->env->maze2d->super->cols - 1) {
                this->wallSDLs[n].x = this->env->maze2d->cell2ds[i].wall2ds[1][0] - 1;
                this->wallSDLs[n].y = this->env->maze2d->cell2ds[i].wall2ds[1][1];
                this->wallSDLs[n].w = 2;
                this->wallSDLs[n++].h = this->env->maze2d->cell2dHeight;
            }
            if(this->env->maze2d->cell2ds[i].cell->walls[2] == TRUE &&
               y < this->env->maze2d->super->rows - 1) {
                this->wallSDLs[n].x = this->env->maze2d->cell2ds[i].wall2ds[2][0];
                this->wallSDLs[n].y = this->env->maze2d->cell2ds[i].wall2ds[2][1] - 1;
                this->wallSDLs[n].w = this->env->maze2d->cell2dWidth;
                this->wallSDLs[n++].h = 2;
            }
        }
    }
}

static void mazeSDL_renderMazeSDL(mazeSDL* this, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255 );
    SDL_RenderFillRect(renderer, &this->bgSDL);

    SDL_SetRenderDrawColor(renderer, 255, 0, 100, 255 );
    int i;
    for(i = 0; i < this->wallSDLsLength; i++) {
        SDL_RenderFillRect(renderer, &this->wallSDLs[i]);
    }
}
