#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_



/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the keyboard and mouse
 */

#define BIT(n) (0x01 << (n))
#define IRQ_LINE_KEYBOARD 1
#define IRQ_LINE_MOUSE 12
//  KEYBOARD-RELATED KBV COMMANDS FOR PC-AT/PS2 MACROS
#define READ_COMMAND_BYTE 0x20        // RETURNS COMMAND BYTE
#define WRITE_COMMAND_BYTE 0X60       // TAKES A : COMMAND BYTE
#define CHECK_KBC 0xAA                // RETURNS 0x55, IF OK ; RETURNS 0xFC, IF ERROR
#define CHECK_KEYBOARD_INTERFACE 0xAB // RETURNS 0, IF OK
#define DISABLE_KB_INTERFACE 0xAD     //  DESATIVAR KB
#define ENABLE_KBD_INTERFACE 0xAE    //  ATIVAR KB
#define DISABLE_MOUSE 0xA7
#define ENABLE_MOUSE 0xA8
#define CHECK_MOUSE_INTERFACE 0xA9
#define WRITE_BYTE_TO_MOUSE 0xD4
//  COMMAND BYTE KBC MACROS
#define DISABLE_KEYBOARD_INTERFACE BIT(4)
#define ENABLE_INTERRUPT_MOUSE BIT(1)
#define ENABLE_INTERRUPT_KEYBOARD BIT(0)
//  STATUS REGISTER MACROS  , & LOGICO E DEPOIS COMPARAR COM A
#define AUX BIT(5)
#define INH BIT(4)
#define A2 BIT(3)
#define SYS BIT(2)
#define IBF BIT(1)
#define OBF BIT(0)
#define DATA_BYTE 0
#define COMMAND_BYTE 1
#define INPUT_BUFFER_FULL 1
#define OUTPUT_BUFFER_FULL 1
#define PAR_ERR BIT(7)
#define TO_ERR BIT(6)
#define OUT_BUF_FULL 0x01
#define DELAY_US 20000
//macro para o esc para terminar o scan
#define ESC_BREAK 0x81
//  registers
#define OUT_BUF 0x60
#define IN_BUF_0x60 0x60
#define STAT_REG 0x64
#define IN_BUF_0x64 0x64
// SE O SCAN WORD FOREM DOIS BYTES
#define TWO_BYTES 0xE0
#define MSB BIT(7)
#define CAST_PARA_8BITS 0XFF
#define COMMANDBYTE_ENABLE_KEYBOARD 0x01
#define E_ARG 1
#define NAO_E_ARG 0
//MACROS PARA PROCESSAR BYTE 1 DO +ACKET
#define L_B BIT(0)
#define R_B BIT(1)
#define M_B BIT(2)
#define X_SIGN BIT(4)
#define Y_SIGN BIT(5)
#define X_OVFL BIT(6)
#define Y_OVFL BIT(7)
#define SINALNEGATIVO BIT(15)
//PS/2 MOUSE COMMANDS 
#define RESET 0xfe
#define RESEND 0xfe
#define SET_DEFAULT 0xf6
#define DISABLE_DATA_REPORTING 0xf5
#define ENABLE_DATA_REPORTING 0xf4
#define SET_SAMPLE_RATE 0xf3
#define SET_REMOTE_MODE 0xf0
#define READ_DATA 0xeb
#define SET_STREAM_MODE 0xea
#define STATUS_REQUEST 0xe9
#define SET_SCALING_2_1 0xe7
#define SET_SCALING_1_1 0xe6
#define ACK 0xfa
#define NACK 0xfe
#define ERROR 0xfc

#define Complemento_2 0xff00 

#endif
