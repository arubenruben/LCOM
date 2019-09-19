#pragma once


/** @defgroup uart uart
 * @{
 *
 *  Functions to control the serial port
 */

#include "fila.h"
struct boot_resources;

/**
 * @brief Clear the fifo receiver
 * 
 * sends a byte to the fifo controller resgiter to clear the fifo receiver
 * uses sys_inb to do so
 * 
 * @return doesnt return anything
 */
void self_clearing_receiver();

/**
 * @brief Clear the fifo transmitter
 * 
 * sends a byte to the fifo controller resgiter to clear the fifo transmitter
 * uses sys_inb to do so
 * 
 * @return doesnt return anything
 */
void self_clearing_transmitter();

/**
 * @brief returns pointer to queue receiver
 * 
 * @param start, struct that contains all the variables, structs to run
 * the game
 * 
 * @return returns pointer to queue receiver
 */
fila *get_transmitter(struct boot_resources *start);

/**
 * @brief returns pointer to queue transmitter
 * 
 * @param start, struct that contains all the variables, structs to run
 * the game
 * 
 * @return returns pointer to queue transmiiter
 */
fila *get_receiver(struct boot_resources *start);

/**
 * @brief configures the seiral port setting 
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int configurate_uart();

/**
 * @brief Process the character received from the receiver buffer registeI*
 * 
 * @param start, struct that contains all the variables, structs to run
 * the game
 * 
 * @return Return 0 upon success and -1  otherwise
 */
int process_char(unsigned char aux, struct boot_resources *start);

/**
 * @brief transmites a queue configured by the user 
 * 
 * @param start, struct that contains all the variables, structs to run
 * the game
 * 
 * @return returns 0 in case of sucess and -1 in case of failure
 */
int transmit_queue(struct boot_resources *start);

/**
 * @brief receives char from the receiver buffer
 * 
 * uses information from the line status reg to know when theres is a 
 * character available to read from the receiver buffer status
 * 
 * @param start, struct that contains all the variables, structs to run
 * the game
 
 * @return doesnt return anything
 */
unsigned char receive_char(struct boot_resources *start);

/**
 * @brief subscirbes interrupts from the uart
 * 
 * uses function setpolicy to set the mode that we want to use the interrups
 * various sys_inb and sys_outb to configure the Interrupt enablbe register and the 
 * fifo control register
 * 
 * @param bit_no address of memory to be initialized with the
 *         bit number to be set in the mask returned upon an interrupt
 * 
 * @return doesnt return anything
 */
int uart_subscribe_int(uint8_t *bit_no);

/**
 * @brief unsubscribes interrupts from the uart
 * 
 * removes the policy set and disables any previous changes made
 * to any register in function uart_unsubscribe, uses sys_inbs and
 * sys_outbs for that purpose
 * 
  * @param start, struct that contains all the variables, structs to run
 * the game
 * 
 * @return doesnt return anything
 */
int uart_unsubscribe_int();
