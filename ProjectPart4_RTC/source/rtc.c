/**
 * \file buffer.c
 * 
 * Functions call necessary for the circular buffer. The circular buffer will
 * store a specific amount of values and it is operated by a FIFO logic.
 * 
*/

/********************************************************************************
 * Header Files
 *******************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "scheduler.h"
#include "rtc.h"
#include "common.h"

/********************************************************************************
 * Variable Declarations
 *******************************************************************************/

uint8_t months[13] = {31,28,31,30,31,30,31,30,31,30,31,31};

/********************************************************************************
 * Private Function Prototypes
 *******************************************************************************/

/********************************************************************************
 * Public Function
 *******************************************************************************/

void Rtcc_clockInit(Rtcc_Clock_t *rtcc) {
    rtcc->tm_sec = 0;
    rtcc->tm_min = 0;
    rtcc->tm_hour = 0;
    rtcc->tm_day = 1;
    rtcc->tm_mon = 1;
    rtcc->tm_year = 1900;
    rtcc->tm_wday = 0;
    rtcc->al_min = 0;
    rtcc->al_hour = 0;
    rtcc->mt_days[13] = months[13];
    rtcc->ctrl.Register = 0xFF;
    rtcc->ctrl.bits.clk_en = 0;
    rtcc->ctrl.bits.al_set = 0;
    rtcc->ctrl.bits.al_active = 0;
    rtcc->ctrl.bits.none = 0;
}


uint8_t Rtcc_setTime(Rtcc_Clock_t *rtcc, uint8_t hour, uint8_t minutes, uint8_t seconds) {
    if(hour > 24 || hour < 0 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59 ) {
        printf("\n\n Incorrect time format\n\n");
        return FALSE;
    }

    rtcc->tm_hour = hour;
    rtcc->tm_min = minutes;
    rtcc->tm_sec = seconds;
    return TRUE;
}


uint8_t Rtcc_setDate(Rtcc_Clock_t *rtcc, uint8_t day, uint8_t month, uint16_t year) {
    if(day > 31 || day < 0 || month < 1 || month > 12 || year < 1900 || year > 2100 ) {
        printf("\n\n Incorrect Date format\n\n");
        return FALSE;
    }
    bool_t leap = FALSE;
    if ( year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
        leap = TRUE;
    }
    printf("Date: %d/%d/%d\n\n", day,month,year);
    uint16_t dayOfWeek = year;
    uint8_t lastTwoDigits = year;
    if ( (dayOfWeek - 2000) < 0 ) {
        dayOfWeek = dayOfWeek - 1900;
        lastTwoDigits = dayOfWeek;
    } else {
        dayOfWeek = dayOfWeek - 2000;
        lastTwoDigits = dayOfWeek;
    }
   
    dayOfWeek = dayOfWeek / 4;
    dayOfWeek = dayOfWeek + day;

    rtcc->tm_day = day;
    rtcc->tm_mon = month;
    rtcc->tm_year = year;

    switch (rtcc->tm_mon) {
        case 1:
        if ( leap == FALSE ) {
            dayOfWeek = dayOfWeek + 1;
        }
            break;
        case 2:
        if ( leap == FALSE) {
            dayOfWeek = dayOfWeek + 4;
        } else {
            dayOfWeek = dayOfWeek + 3;
        }
            break;
        case 3:
            dayOfWeek = dayOfWeek + 4;
            break;
        case 4:
            dayOfWeek = dayOfWeek + 0;
            break;
        case 5:
            dayOfWeek = dayOfWeek + 2; 
            break;
        case 6:
            dayOfWeek = dayOfWeek + 5;
            break; 
        case 7:
            dayOfWeek = dayOfWeek + 0;
            break;
        case 8:
            dayOfWeek = dayOfWeek + 3; 
            break;
        case 9:
            dayOfWeek = dayOfWeek + 6;
            break;
        case 10:
            dayOfWeek = dayOfWeek + 1;
            break; 
        case 11:
            dayOfWeek = dayOfWeek + 4;
            break;
        case 12:
            dayOfWeek = dayOfWeek + 6;
            break;
        default:
            break;
            
    }
    //rtcc->tm_wday = dayOfWeek / 7;
    if ( (year - 2000) < 0 ) {
        dayOfWeek = dayOfWeek;
    } else {
        dayOfWeek = dayOfWeek + 6;
    }

    dayOfWeek = dayOfWeek + lastTwoDigits;
    dayOfWeek = dayOfWeek % 7;
    if (dayOfWeek == 0) {
        rtcc->tm_wday = 6;
    } else {
        rtcc->tm_wday = dayOfWeek;
    }
    return TRUE;
}

uint8_t Rtcc_setAlarm(Rtcc_Clock_t *rtcc, uint8_t hour, uint8_t minutes) {
    if(hour > 23 || hour < 0 || minutes < 0 || minutes > 59 ) {
        printf("\n\n Incorrect Alarm format\n\n");
        return FALSE;
    }
    rtcc->al_hour = hour;
    rtcc->al_min = minutes;
    rtcc->ctrl.bits.al_set = TRUE;
    return TRUE;
}

void Rtcc_getTime(Rtcc_Clock_t *rtcc, uint8_t *hour, uint8_t *minutes, uint8_t *seconds) {
    *hour = rtcc->tm_hour;
    *minutes = rtcc->tm_min;
    *seconds = rtcc->tm_sec;
}

void Rtcc_getDate(Rtcc_Clock_t *rtcc, uint8_t* day, uint8_t* month, uint16_t* year, uint8_t* weekDay) {
    *day = rtcc->tm_day;
    *month = rtcc->tm_mon;
    *year = rtcc->tm_year;
    *weekDay = rtcc->tm_wday;
}

uint8_t Rtcc_getAlarm(Rtcc_Clock_t *rtcc, uint8_t* hour, uint8_t* minutes ) {
        *hour = rtcc->al_hour;
        *minutes = rtcc->al_min;
        return rtcc->ctrl.bits.al_set;
}

void Rtcc_clearAlarm( Rtcc_Clock_t *rtcc ) {
    if ( rtcc->ctrl.bits.al_active == TRUE && rtcc->al_hour == rtcc->tm_hour && rtcc->al_min == rtcc->tm_min) {
        rtcc->ctrl.bits.al_active = FALSE;
        rtcc->ctrl.bits.al_active = FALSE;
    }
}

uint8_t Rtcc_getAlarmFlag( Rtcc_Clock_t *rtcc ) {
    return rtcc->ctrl.bits.al_active;
}

void Rtcc_periodicTask( Rtcc_Clock_t *rtcc ) {
    
    
    while (1) {
    }
}

/********************************************************************************
 * Private Function Definitions
 *******************************************************************************/