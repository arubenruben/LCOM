#pragma once

/** @defgroup kbc kbc
 * @{
 *
 *  Functions to send or receive commands from the output buffer and input buffer, main uses
 * are to send and receive status information from the keyboard and mouse
 */


/**
 * @brief function that controls the commnunication bettween the program and the mouse
 * 
 * Uses function keyboard_comand_issue and receive
 * 
 *  @param leitura, pointer to where we want the information
 *  @param command byte we want to send
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int(mouse_messaging)(uint8_t *leitura, uint8_t comand);

/**
 * @brief sends command bytes to the outbuff and the inbuff
 * 
 *  @param registo to where we want to send the command byte
 *  @param command byte we want to send
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int(keyboard_command_issue)(uint8_t registo, uint8_t command);


/**
 * @brief receives bytes from the outbuff
 * 
 *  @param leitura , pointer to variable where the information read from the outbuff is gonna be stored
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int(keyboard_command_receive)(uint8_t *leitura);



/** 
 * @brief interrupt handler for the keyboard
 * 
 * process interrupts from the keyboard
 * 
*/
void(kbc_ih)();

/**
 * @brief sends information to configure the keyboard using a command byte
 * 
 * Uses functions keyboard_comand_receive and issue
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int(keyboard_messaging)(uint8_t *leitura, uint8_t comand);


/**
 * @brief returns the scancode sent from the keyboard
 *
 * @return Return the scancode
 */

uint8_t return_scancode();

/**
 * @brief Inserts information about the mouse into a struct packet
 *
 * @param time Length of time interval while interrupts are subscribed
 * 
 * @return 0 on sucess or -1 in case of failure 
 */

int(data_processing)(struct packet *leitura);
