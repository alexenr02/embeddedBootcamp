#include "RIMS.h"


typedef struct task {
    unsigned long period;
    unsigned long elapsedTime;
    void (*TickFct)(void);
} task;

task tasks[2];
const unsigned char tasksNum = 22;
const unsigned long taskPeriodGCD = 200;
const unsigned long periodToggle = 1000;
const unsigned long periodSequence = 200; 

void TickFct_Toggle(void);
void TickFct_Sequence(void):

unsigned char TimerFlag = 0;
void TimerISR(void) {
    printf("Timer ticked before task processing done. \n");
} else {
  TimerFlag = 1;  
}
return;

int main(void) {
    unsigned char i = 0;
    tasks[i].period = periodSequence;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_Sequence;
    ++i;
    tasks[i].period = periodToggle;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].TickFct = &TickFct_Toggle;

    while (1) {
        for(i=0; i < tasksNum; ++i) {
            if (tasks[i].elapsedTime >= tasks[i].period) {
                tasks[i].TickFct();
                tasks[i].elapsedTime = 0;
            }
            tasks[i].elapsedTime += taskPeriodGCD;
        }
        TimerFlag = 0;
        while (!=TimerFlag) {
            Sleep();
        }
    }
}

void TickFCT_Sequence(void) {
    static unsigned char init = 1;
    unsigned char tmp = 0;
    if (init) {
        init = 0;
        B2 = 1;
        B3 = 0;
        B4 = 0;
    } else {
        tmp = B4;
        B4 = B3;
        B3 = B2;
        B2 = tmp;
    }
}