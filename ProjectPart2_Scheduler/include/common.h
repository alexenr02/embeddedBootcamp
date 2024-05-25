#ifndef COMMON_H_
#define COMMON_H_

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


#endif /* __BUFFER_H */