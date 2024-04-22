#include <stdio.h>
#include <stdint.h>
#include "circularBuffer.h"
#include "userInterface.h"

/*  */

int main( void )
{
    uint32_t            circularBuffer[SIZE_OF_BUFFER] = { 0 }; // Empty circular buffer
    userInputOption_t   optionNumber    = 0;                    // User-input option number
    uint8_t             readIndex       = 0;                    // Index of the read pointer
    uint8_t             writeIndex      = 0;                    // Index of the write pointer
    uint8_t             bufferLength    = 0;                    // Number of values in circular buffer
    uint8_t             loopStatus      = 0;                    // Loop Condition variable

    while ( loopStatus != EXIT_LOOP ) {
        displayMainMenu();
        getNumber(&optionNumber);   // Get option number from user  

        switch ( optionNumber ) {
            case OPTION_WRITE:
            // check if buffer is full
                if ( bufferLength == SIZE_OF_BUFFER ) {
                    printf( "\n   Buffer is full! \n\n   " );
                    getchar();
                }

                printf("\n   Please input an integer to store in the array\n\n    ");
                getNumber(&circularBuffer[writeIndex]);
                bufferLength++;
                writeIndex++;

                // If at last index in buffer, set writeIndex back to 0
                if ( writeIndex == SIZE_OF_BUFFER ) {
                    writeIndex = 0;
                }
                break;

            case OPTION_READ:
                if ( bufferLength == 0 ) {
                    printf( "\n    Buffer is empty!\n\n   " );
                    getchar();
                }

                printf("\n     The output value is %d\n\n    ", circularBuffer[readIndex]);
                getchar();

                bufferLength--;     //   Decrease buffer size after reading
                readIndex++;        //   Increase readIndex position to prepare for next read

                // if at last index in buffer, set readIndex back to 0
                if ( readIndex == SIZE_OF_BUFFER ) {
                    readIndex = 0;
                }
                break;
            case OPTION_DISPLAY_BUFFER:
                printf("\n================= CIRCULAR BUFFER ==================\n\n");
                printf("                  ");
                for( uint8_t bufferSize = 0; bufferSize < SIZE_OF_BUFFER; bufferSize++) {
                    printf("%d ", circularBuffer[bufferSize]);
                }
                printf("\n====================================================\n\n");
                continue;
                break;
            case OPTION_EXIT:
                printf("\n    Thanks for using the circular buffer!\n\n");
                loopStatus = EXIT_LOOP;
                break;
                
            case OPTION_INVALID:    
            default:
                printf("\n    Invalid option number!\n\n    ");
                getchar();
                break;
        }
    }
    return 0;
}