#ifndef COMMON_H_
#define COMMON_H_
#include <time.h>
/********************************************************************************
 * Constant Definitions
 *******************************************************************************/

/* Arbitrary number of temporary strings */
#define MAX_LENGTH_OF_STRING    81

#define SUCCESS                 0
#define FAILURE                 -1
#define EXIT_LOOP               1

#define TRUE 1
#define FALSE 0

typedef enum {
    NOT_EMPTY,
    EMPTY

}systemErrors_t;

static long milliseconds (void) {
    return clock() / ( CLOCKS_PER_SEC / 1000 );
}

#endif /* __BUFFER_H */