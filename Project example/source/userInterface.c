/**
 * \file user_interface.c
 * 
 * Functions call necessary for the user interface text displaying. 
 * This will handle all the interactions between the software and the user, including
 * the entering of the values and text displaying.
 * 
*/

/********************************************************************************
 * Header Files
 *******************************************************************************/

#include <stdio.h>
#include "userInterface.h"
#include "circularBuffer.h"

/********************************************************************************
 * Variable Declarations
 *******************************************************************************/



/********************************************************************************
 * Private Function Prototypes
 *******************************************************************************/

/********************************************************************************
 * Public Function
 *******************************************************************************/
void displayMainMenu(void) {
    printf("\n================= CIRCULAR BUFFER ==================\n\n");
    printf("     Please choose from the following options:\n\n");
    printf("          1     Input Value\n");
    printf("          2     Output Value\n");
    printf("          3     Display Buffer\n");
    printf("          4     Exit Program\n");
    printf("\n=====================================================\n\n");
    
} 

int  getNumber(userInputOption_t* pNumber) {
    // An array of char to store the string
    char userInput[MAX_LENGTH_OF_STRING]    =   { 0 };
    
    // Get User Input 
    fgets(userInput, MAX_LENGTH_OF_STRING, stdin);
    
    // Parse the user input for an integer and store it in the pNumber parameter
    if ( sscanf(userInput, "%d", pNumber) != 1 ) {
        return FAILURE;
    }
    return SUCCESS;
}

/********************************************************************************
 * Internal Functions
 *******************************************************************************/