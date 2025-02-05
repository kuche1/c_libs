
#ifndef _ERR_H_
#define _ERR_H_

#include <stdio.h>

#define PANICIF(err) \
    { \
        if(err) \
        { \
            fprintf(stderr, "ERROR: %s\n", err); \
            exit(EXIT_FAILURE); \
        } \
    }

/*
#define CRITICAL(info) \
    { \
        fprintf(stderr, "CRITICAL ERROR: %s\n", info); \
        exit(EXIT_FAILURE); \
    }
*/

#endif
