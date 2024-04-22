#ifndef MAIN_H_
#define MAIN_H_


#define ON 1
#define OFF 0 

enum states {
    STATE_IDLE,
    STATE_FIRST_DIGIT,
    STATE_SECOND_DIGIT,
    STATE_THIRD_DIGIT,
    STATE_OPEN_DOOR,
    STATE_ERROR,
    STATE_COUNT
};

#endif