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

    const char cmds[] = "h:W:H:C:R:";

    for(;;){
        switch(getopt(argc, argv, cmds)){

            case '?': // help
            case 'h':
            default :
                printf("usage: apps/exec [-h] [-W WID] [-H HEI] [-C COL] [-R ROW]\n");
                printf("\n");
                printf("ANT COLONY OPTIMIZATION\n");
                printf("\n");
                printf("optional args:\n");
                printf("  -h      Print help and exit\n");
                printf("  -W HEI  Set width\n");
                printf("  -H WID  Set height\n");
                printf("  -C COL  Set cols\n");
                printf("  -R ROW  Set rows\n");

                return FALSE;

            case -1:
                break;

            case 'W':
                CONF.WINDOW_WIDTH = atoi(optarg);
                continue;

            case 'H':
                CONF.WINDOW_HEIGHT = atoi(optarg);
                continue;

            case 'C':
                CONF.MAZE_COLS = atoi(optarg);
                continue;

            case 'R':
                CONF.MAZE_ROWS = atoi(optarg);
                continue;
        }
        break;
    }

    return TRUE;
}

#endif