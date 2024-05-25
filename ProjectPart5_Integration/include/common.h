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

#if 0
#define ENABLE_DEBUG_MESSAGES
#endif


#ifdef  ENABLE_DEBUG_MESSAGES
#define PRINT_PARAMS(value,...)             printf( #value "\n",## __VA_ARGS__);
#define PRINT(value)                        printf( #value "\n");
#define DEBUG(value)                        value
#else
#define PRINT_PARAMS(value,...) 
#define PRINT(value)
#define DEBUG(value)
#endif

#endif /* __BUFFER_H */