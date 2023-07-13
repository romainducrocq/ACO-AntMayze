#include <stdlib.h>
#include <time.h>

#include "conf.h"

#include "app.h"


conf CONF = {
    .MAZE_COLS = 20,
    .MAZE_ROWS = 20,

    .WINDOW_WIDTH = 1280,
    .WINDOW_HEIGHT = 720
};

int main(int argc, char** argv) {
    srand(time(NULL));

    if(argParse(argc, argv))
    {

        {
            App.ctor();
            App.dtor();
        }

        return 0;
    }

    return 1;
}
