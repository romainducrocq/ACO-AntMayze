#ifndef _CONF_H
#define _CONF_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

typedef struct conf {
    int WIDTH;
    int HEIGHT;

    int WIN_W;
    int WIN_H;
} conf;

extern conf CONF;

static inline int argParse(int argc, char** argv)
{
    // https://github.com/gnif/LookingGlass/blob/c0c63fd93bf999b6601a782fec8b56e9133388cc/client/main.c#L1391

    const char cmds[] = "h:W:H:";

    for(;;){
        switch(getopt(argc, argv, cmds)){

            case '?': // help
            case 'h':
            default :
                printf("usage: apps/exec [-h] [-W WIDTH] [-H HEIGHT]\n");
                printf("\n");
                printf("ANT COLONY OPTIMIZATION\n");
                printf("\n");
                printf("optional args:\n");
                printf("  -h         Print help and exit\n");
                printf("  -W WIDTH   Set width\n");
                printf("  -W HEIGHT  Set height\n");

                return FALSE;

            case -1:
                break;

            case 'W':
                CONF.WIDTH = atoi(optarg);
                continue;

            case 'H':
                CONF.HEIGHT = atoi(optarg);
                continue;
        }
        break;
    }

    return TRUE;
}

#endif