#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

/********************************************************************************
 * Constant Definitions
 *******************************************************************************/

/********************************************************************************
 * Data Prototypes
 *******************************************************************************/

typedef enum {
    OPTION_WRITE = 1,
    OPTION_READ,
    OPTION_DISPLAY_BUFFER,
    OPTION_EXIT,
    OPTION_INVALID,
    OPTION_END
} userInputOption_t;

/********************************************************************************
 * External Functions Prototypes
 *******************************************************************************/

/**
 * Displays the main menu options to the user
 * 
 * \param none
 * 
 * \return none
*/
void displayMainMenu(void);

/**
 * Get a number entered by the user
 * 
 * \param pNumber pointer to the number where will be stored 
 * 
 * \return value of the number entered by the user
 * 
 */
int  getNumber(userInputOption_t* pNumber);


#endif /* __USERINTERFACE_H */