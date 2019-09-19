#pragma once



/** @defgroup kbd kbd
 * @{
 *
 *  Functions to susbcribes and unsubscribe interrupts from the keyboard and to process
 * scancodes sent from the keyboard
 */


struct boot_resources;

/**
 * @brief subscribes interrupts from the keyboard
 * 
 * @param bit_no address of memory to be initialized with the
 *         bit number to be set in the mask returned upon an interrupt
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int keyboard_subscribe_int(uint8_t *(bit_no));

/**
 * @brief unsubscribe interrupts from the keyboard
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int keyboard_unsubscribe_int();

/**
 * @brief checks the borders from player1s character
 * 
 * @param  start, struct that contains all the varaibles, structs necessary to run the game
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
void check_borders_p1(struct boot_resources *start);

/**
 * @brief checks the borders from player2s character
 * 
 * @param  start, struct that contains all the varaibles, structs necessary to run the game
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
void check_borders_p2(struct boot_resources *start);


/**
 * @brief processes the scancodes from the keyboard for player1
 * 
 * @param  start, struct that contains all the varaibles, structs necessary to run the game
 *
 * @return doesnt return anything
 */
void kbd_processing(struct boot_resources *start);

/**
 * @brief processes the scancodes from the keyboard for player2
 * 
 * @param  start, struct that contains all the varaibles, structs necessary to run the game
 *
 * @return doesnt return anything
 */
void kbd_processing_p2(struct boot_resources *start);
