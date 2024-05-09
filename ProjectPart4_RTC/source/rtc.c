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

/********************************************************************************
 * Private Function Prototypes
 *******************************************************************************/

/********************************************************************************
 * Public Function
 *******************************************************************************/

void Rtcc_clockInit(Rtcc_Clock *rtcc) {
    rtcc->tm_sec = 0;
    rtcc->tm_min = 0;
    rtcc->tm_hour = 0;
    rtcc->tm_day = 1;
    rtcc->tm_mon = 1;
    rtcc->tm_year = 1900;
    rtcc->tm_wday = 0;
    rtcc->al_min = 0;
    rtcc->al_hour = 0;
    rtcc->mt_days[13u] = {31,28,31,30,31,30,31,30,31,30,31,31};
    rtcc->ctrl.Register = 0xFF;
    rtcc->ctrl.bits.clk_en = 0;
    rtcc->ctrl.bits.al_set = 0;
    rtcc->ctrl.bits.al_active = 0;
    rtcc->ctrl.bits.none = 0;
}


uint8_t Rtcc_setTime(Rtcc_Clock *rtcc, uint8_t hour, uint8_t minutes, uint8_t seconds) {
    if(hour > 24 || hour < 0 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59 ) {
        printf("\n\n Incorrect time format\n\n");
        return FALSE;
    }

    rtcc->tm_hour = hour;
    rtcc->tm_min = minutes;
    rtcc->tm_sec = seconds;
    return TRUE;
}


uint8_t Rtcc_setDate(Rtcc_Clock *rtcc, uint8_t day, uint8_t month, uint16_t year) {
    if(day > 31 || day < 0 || month < 1 || month > 12 || year < 1900 || year > 2100 ) {
        printf("\n\n Incorrect Date format\n\n");
        return FALSE;
    }

    uint16_t dayOfWeek = year;

    if ( (dayOfWeek - 2000) < 0 ) {
        dayOfWeek = dayOfWeek - 2000;
    } else {
        dayOfWeek = dayOfWeek - 1900;
    }
    
    dayOfWeek = dayOfWeek / 4;
    dayOfWeek = dayOfWeek + day;

    rtcc->tm_day = day;
    rtcc->tm_mon = month;
    rtcc->tm_year = year;

    switch (rtcc->tm_mon) {
        case 1:
            dayOfWeek = dayOfWeek + 1;
            break;
        case 2:
            dayOfWeek = dayOfWeek + 4;
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
    uint8_t reminder = dayOfWeek % 7;
    switch (reminder) {
            case 0: 
                rtcc->tm_wday = 5;  //Saturday
                break;
            case 1:
                rtcc->tm_wday = 6;  //Sunday
                break;
            case 2:
                rtcc->tm_wday = 0;  //Monday
                break;
            case 3:
                rtcc->tm_wday = 1;  //Tuesday
                break;
            case 4:
                rtcc->tm_wday = 2;  //Wednesday
                break;
            case 5: 
                rtcc->tm_wday = 3;  //Thursday
                break;
            case 6:
                rtcc->tm_wday = 4;  //Friday
        }
    return TRUE;
}

uint8_t Rtcc_setAlarm(Rtcc_Clock *rtcc, uint8_t hour, uint8_t minutes) {

}

void Rtcc_getTime(Rtcc_Clock *rtcc, uint8_t *hour, uint8_t *minutes, uint8_t *seconds) {

}

void Rtcc_getDate(Rtcc_Clock *rtcc, uint8_t* day, uint8_t* month, uint16_t* year, uint8_t* weekDay) {

}

uint8_t Rtcc_getAlarm(Rtcc_Clock *rtcc, uint8_t* hour, uint8_t* minutes ) {

}

void Rtcc_clearAlarm( Rtcc_Clock *rtcc ) {

}

uint8_t Rtcc_getAlarmFlag( Rtcc_Clock *rtcc ) {

}

void Rtcc_periodicTask( Rtcc_Clock *rtcc ) {

}

/********************************************************************************
 * Private Function Definitions
 *******************************************************************************/