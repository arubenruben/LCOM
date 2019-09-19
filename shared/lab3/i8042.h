#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#define BIT(n) (0x01 << (n))

#define IRQ_LINE_KEYBOARD 1

//  KEYBOARD-RELATED KBV COMMANDS FOR PC-AT/PS2 MACROS

#define READ_COMMAND_BYTE 0x20        // RETURNS COMMAND BYTE
#define WRITE_COMMAND_BYTE 0X60       // TAKES A : COMMAND BYTE
#define CHECK_KBC 0xAA                // RETURNS 0x55, IF OK ; RETURNS 0xFC, IF ERROR
#define CHECK_KEYBOARD_INTERFACE 0xAB // RETURNS 0, IF OK
#define DISABLE_KB_INTERFACE 0xAD     //  DESATIVAR KB
#define ENABLE_KBD_INTERFACE 0xAE     //  ATIVAR KB

//  COMMAND BYTE KBC MACROS

#define DISABLE_MOUSE BIT(5);
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

#endif