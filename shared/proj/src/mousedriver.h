#pragma once

/** @defgroup mousedriver mousedriver
 * @{
 *
 *  Functions to susbcribes and unsubscribe interrupts from the keyboard and to process
 * scancodes sent from the keyboard
 */

#include "bitmap.h"

struct boot_resources;

typedef struct {    
    int x, y;
    int leftButtonDown;
    int middleButtonDown;
    int rightButtonDown;
    int leftButtonReleased;
    int rightButtonReleased;
    int middleButtonReleased;

} Mouse;  //struct that contains all the details from the mouse packet

/**
 * @brief subscribes interrupts from the mouse
 * 
 * @param bit_no address of memory to be initialized with the
 *         bit number to be set in the mask returned upon an interrupt
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int(mouse_subscribe_int)(uint8_t *bit_no);

/**
 * @brief unsubscribe interrupts from the mouse
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int(mouse_unsubscribe_int)();

/**
 * @brief mouse interrupts handler
 *
 * every time an interrupts from the mouse happens we need to read the byte it
 * sends before sending it to be processed
 * 
 */
void (mouse_ih)();

/**
 * @brief returns the mouse_byte
 *
 * @return Return the mouse_byte
 */
uint8_t return_mousebyte();


/**
 * @brief processes the mouse bytes received from player1
 * 
 * @param  start, struct that contains all the varaibles, structs necessary to run the game
 *
 * @return doesnt return anything
 */
void mouse_processing(struct boot_resources *start);

/**
 * @brief processes the mouse bytes received from player2
 * 
 * @param  start, struct that contains all the varaibles, structs necessary to run the game
 *
 * @return doesnt return anything
 */
void mouse_processing_p2(struct boot_resources *start);







