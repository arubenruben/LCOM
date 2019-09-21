#pragma once

/**
 * @brief Subscribes KB interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */


int kb_subscribe_int(uint8_t *(bit_no));

/**
 * @brief Unsubscribes KB interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int keyboard_unsubscribe_int();
