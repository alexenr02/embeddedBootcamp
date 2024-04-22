#include <stdio.h>
#include "main.h"


int main( void )
{
    int firstDigit, secondDigit, thirdDigit = 0;
    int correctPassword = 834;
    int introducedPassword= 0;
    int state = STATE_IDLE;
    int run = ON;
    
    while( run == ON )
    {
        switch( state )
        {
            case STATE_IDLE:
                printf("\nWelcome, please enter password: ");
                state = STATE_FIRST_DIGIT;
            break;
            case STATE_FIRST_DIGIT:
                scanf("%d", &firstDigit);
                if ( firstDigit == 8 ) {
                    state = STATE_SECOND_DIGIT;
                } else {
                    state = STATE_ERROR;
                }
            break;
            case STATE_SECOND_DIGIT:
                scanf("%d", &secondDigit );
                if ( secondDigit == 3 ) {
                    state = STATE_THIRD_DIGIT;
                } else {
                    state = STATE_ERROR;
                }
            break;
            case STATE_THIRD_DIGIT:
                scanf("%d", &thirdDigit);
                if ( thirdDigit == 4 ) {
                    state = STATE_OPEN_DOOR;
                } else {
                    state = STATE_ERROR;
                }
            break;
            case STATE_OPEN_DOOR:
                printf("Welcome, door opened. ");
                state = STATE_IDLE;
                run = OFF;
            break;
            case STATE_ERROR:
                printf("\nWrong Password, try again. ");
                state = STATE_IDLE;
            break;
            default:
            break;
        }
    }
}