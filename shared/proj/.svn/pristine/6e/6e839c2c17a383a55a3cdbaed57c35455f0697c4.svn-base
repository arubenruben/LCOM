#pragma once



/** @defgroup rtc rtc
 * @{
 *
 *  Functions to control the rtc
 */

/**
 * @brief reads the year, the month, the day, the hour, the minute and the second from the rtc
 *
 * @param t seconds, pointers to the variable thats gonna store the seconds
 *  @param t minutes, pointers to the variable thats gonna store the minutes
 *  @param t hour, pointers to the variable thats gonna store the hour
 *  @param t day_month, pointers to the variable thats gonna store the day_month
 *  @param t month, pointers to the variable thats gonna store the month
 *  @param t year, pointers to the variable thats gonna store the year
 * 
 * @return day of the wekk , monday, tuesday, wednesday, thrusday, friday, saturday, sunday
 */
char * (rtc_read_time)(uint8_t *seconds, uint8_t *minutes, uint8_t *hour, uint8_t *day_month,uint8_t *month, uint8_t *year);

/**
 * @brief subscribes interrupts from the real time clock
 * 
 * @param bit_no address of memory to be initialized with the
 *         bit number to be set in the mask returned upon an interrupt
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (rtc_subscribe_int)(uint8_t *bit_no);

/**
 * @brief unsubscribe interrupts from the real time clock
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int(rtc_unsubscribe_int)();

