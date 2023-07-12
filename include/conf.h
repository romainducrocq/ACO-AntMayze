#ifndef _CONF_H
#define _CONF_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1

typedef struct conf {
    int MAZE_COLS;
    int MAZE_ROWS;

    int WINDOW_WIDTH;
    int WINDOW_HEIGHT;
} conf;

extern conf CONF;

static inline int argParse(int argc, char** argv)
{
    // https://github.com/gnif/LookingGlass/blob/c0c63fd93bf999b6601a782fec8b56e9133388cc/client/main.c#L1391

    const char cmds[] = "h:c:r:";

    for(;;){
        switch(getopt(argc, argv, cmds)){

            case '?': // help
            case 'h':
            default :
                printf("usage: apps/exec [-h] [-c COL] [-r ROW]\n");
                printf("\n");
                printf("ANT COLONY OPTIMIZATION\n");
                printf("\n");
                printf("optional args:\n");
                printf("  -h      Print help and exit\n");
                printf("  -c COL  Set cols\n");
                printf("  -r ROW  Set rows\n");

                return FALSE;

            case -1:
                break;

            case 'c':
                CONF.MAZE_COLS = atoi(optarg);
                continue;

            case 'r':
                CONF.MAZE_ROWS = atoi(optarg);
                continue;
        }
        break;
    }

    return TRUE;
}

#endif