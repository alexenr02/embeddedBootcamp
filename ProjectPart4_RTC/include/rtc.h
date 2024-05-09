#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>

/********************************************************************************
 * Constant Definitions
 *******************************************************************************/

/********************************************************************************
 * Data Prototypes
 *******************************************************************************/

/* Control union structure to handle certain number of flags each of them represented by a single bit */
typedef union _Rtcc_Ctrl {
    uint8_t Register;   /* 8 bit variable */
    struct _bits {
        uint8_t clk_en: 1;  /*!< clock enable flag  */
        uint8_t al_set: 1;  /*!< alarm set flag  */
        uint8_t al_active: 1; /*!< alarm active flag  */
        uint8_t none : 4;
    } bits;
} Rtcc_Ctrl;

/* Control structure to pass parameter on each interface */
typedef struct _Rtcc_Clock {
    uint8_t     tm_sec;         /*!< seconds, range 0 to 59 */
    uint8_t     tm_min;         /*!< minutes, range 0 to 59 */
    uint8_t     tm_hour;        /*!< hours, range 0 to 23 */
    uint8_t     tm_day;         /*!< day of the month, range 1 to 31 */
    uint8_t     tm_mon;         /*!< month, range 1 to 12 */
    uint8_t     tm_year;        /*!< years, range 1900 to 2100 */
    uint8_t     tm_wday;        /*!< day of the week, range 0 to 6 */
    uint8_t     al_min;         /*!< alarm minutes, range 0 to 59 */
    uint8_t     al_hour;        /*!< alarm hours, range 0 to 23 */
    uint8_t     mt_days[13u];   /*!< max days on each month */
    Rtcc_Ctrl   ctrl;           /*!< clock control bits */
} Rtcc_Clock;



/********************************************************************************
 * External Functions Prototypes
 *******************************************************************************/
/**
 * Function 
 * 
 * \param  
 * 
 * \return none
 */
void Rtcc_clockInit(Rtcc_Clock *rtcc);

/**
 * Function 
 * 
 * \param  
 * 
 * \return none
 */
uint8_t Rtcc_setTime(Rtcc_Clock *rtcc, uint8_t hour, uint8_t minutes, uint8_t seconds);

/**
 * Function 
 * 
 * \param  
 * 
 * \return none
 */
uint8_t Rtcc_setDate(Rtcc_Clock *rtcc, uint8_t day, uint8_t month, uint16_t year);

/**
 * Function 
 * 
 * \param  
 * 
 * \return none
 */
uint8_t Rtcc_setAlarm(Rtcc_Clock *rtcc, uint8_t hour, uint8_t minutes);

/**
 * Function 
 * 
 * \param  
 * 
 * \return none
 */
void Rtcc_getTime(Rtcc_Clock *rtcc, uint8_t *hour, uint8_t *minutes, uint8_t *seconds);

/**
 * Function 
 * 
 * \param  
 * 
 * \return none
 */
void Rtcc_getDate(Rtcc_Clock *rtcc, uint8_t* day, uint8_t* month, uint16_t* year, uint8_t* weekDay);

/**
 * Function 
 * 
 * \param  
 * 
 * \return none
 */
uint8_t Rtcc_getAlarm(Rtcc_Clock *rtcc, uint8_t* hour, uint8_t* minutes );

/**
 * Function 
 * 
 * \param  
 * 
 * \return none
 */
void Rtcc_clearAlarm( Rtcc_Clock *rtcc );

/**
 * Function 
 * 
 * \param  
 * 
 * \return none
 */
uint8_t Rtcc_getAlarmFlag( Rtcc_Clock *rtcc );

/**
 * Function 
 * 
 * \param  
 * 
 * \return none
 */
void Rtcc_periodicTask( Rtcc_Clock *rtcc );

#endif /* __RTC_H */