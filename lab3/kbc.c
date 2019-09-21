#include <lcom/lcf.h>
#include <minix/drivers.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include <stdbool.h>
#include <stdint.h>
#include <i8254.h>
#include "i8042.h"
#include "kbc.h"
#include "kbd.h"

int sys_inb_counter = 0;
int return_kbc_ih = 0;

uint8_t scancode = INITIALIZE0;

#ifdef LAB3
int sys_inb_cnt(port_t port, uint32_t *byte);
#else
#  define sys_inb_cnt(p, q) sys_inb_cnt(p, q)
#endif

int(sys_inb_cnt)(port_t port, uint32_t *byte) {
  if (sys_inb(port, byte) != 0)
    return 1;
  sys_inb_counter++;
  return 0;
}

void(kbc_ih)() {
  uint32_t statusregister = INITIALIZE0;
  uint32_t scancode32bit = INITIALIZE0, scancode8bit = INITIALIZE0;

  if (sys_inb_cnt(STAT_REG, &statusregister) != 0) { //ler valor so stat reg, para saber o estado das entradas se estão cheias ou não
    return_kbc_ih = -1;
    return; /* assuming it returns OK */
  }
  /* loop while 8042 output buffer is empty */
  if (statusregister & OBF) { // se estiver cheio o outbuff lemos

    if (sys_inb_cnt(OUT_BUF, &scancode32bit) != 0) {
      return_kbc_ih = -1; /* assuming it returns OK */
      return;
    }

    scancode8bit = (uint8_t)(scancode32bit & CAST_PARA_8BITS);

    if ((statusregister & (PAR_ERR | TO_ERR)) == 0) { //caso não acontecer algum erro
      return_kbc_ih = 1;
      scancode = scancode8bit;
      return;
    }
    else {
      return_kbc_ih = -1; // caso acontecer algum erro
      return;
    }
  }
  return;
}
uint8_t(keyboard_command_issue)(uint8_t registo, uint8_t command, uint8_t e_argumento) {

  int tries = 5, i = 0;
  uint32_t stat32bit;
  uint8_t stat8bit, leitura;
  uint32_t commandaux = command;

  if (e_argumento == E_ARG && registo == IN_BUF_0x60) {

    while (i < tries) {
      sys_inb_cnt(STAT_REG, &stat32bit); // ler o estado atual
      stat8bit = (uint8_t)(stat32bit & CAST_PARA_8BITS);
      //se o INBUF nao estiver cheio, escreve, senao espera

      if ((stat8bit & IBF) == INITIALIZE0) { // se o inbuff estiver vazio mandamos para lá o command byte
        sys_outb(IN_BUF_0x60, command);
        return 0;
      }

      i++;
      tickdelay(micros_to_ticks(DELAY_US));
    }
    return -1;
  }

  else if (command == DISABLE_KB_INTERFACE || command == ENABLE_KBD_INTERFACE) {
    sys_outb(IN_BUF_0x64, commandaux);
    return 0;
  }
  else if ((command == WRITE_COMMAND_BYTE || command == READ_COMMAND_BYTE) && e_argumento == NAO_E_ARG && registo == IN_BUF_0x64) {

    while (i < tries) {
      sys_inb_cnt(STAT_REG, &stat32bit); // ler o estado atual
      stat8bit = (uint8_t)(stat32bit & CAST_PARA_8BITS);

      if ((stat8bit & IBF) == INITIALIZE0) { // se o inbuff estiver vazio mandamos para lá o command byte
        sys_outb(IN_BUF_0x64, command);
        return 0;
      }
      i++;
      tickdelay(micros_to_ticks(DELAY_US));
    }
    return -1;
  }

  else if (command == CHECK_KBC || command == CHECK_KEYBOARD_INTERFACE) {
    sys_outb(IN_BUF_0x64, command);
    keyboard_command_receive(&leitura);
    if (leitura == 0x55)
      return 0;
    else if (leitura == 0xFC)
      return -1;
  }

  return -1;
}

int(keyboard_command_receive)(uint8_t *leitura) {
  int tries = 5, i = 0;

  uint32_t stat32bit, commandbyte32bits = INITIALIZE0;
  uint8_t stat8bit, commandbyte8bits;

  while (i < tries) {
    sys_inb_cnt(STAT_REG, &stat32bit);
    stat8bit = (uint8_t)(stat32bit & CAST_PARA_8BITS);

    if (stat8bit & OBF) {

      sys_inb_cnt(OUT_BUF, &commandbyte32bits); /* assuming it returns OK */

      commandbyte8bits = (uint8_t)(commandbyte32bits & CAST_PARA_8BITS);

      if ((stat8bit & (PAR_ERR | TO_ERR | AUX)) == 0) {

        *leitura = commandbyte8bits;
        return 0;
      }
      else
        continue;
    }
    i++;
    tickdelay(micros_to_ticks(DELAY_US));
  }

  return -1;
}
//argumentos-outbuf, inbuf-commandd bytes, stat_reg

int(keyboard_messaging)(uint8_t *leitura, uint8_t command) {
  uint32_t leituraaux;

  if (command == READ_COMMAND_BYTE) {
    if ((keyboard_command_issue(IN_BUF_0x64, READ_COMMAND_BYTE, NAO_E_ARG) != 0))
      return -1;
  }

  else if (command == WRITE_COMMAND_BYTE) {
    if ((keyboard_command_receive(leitura) != 0))
      return -1;

    *leitura = (*leitura) | COMMANDBYTE_ENABLE_KEYBOARD;

    leituraaux = *leitura;

    if (keyboard_command_issue(IN_BUF_0x64, WRITE_COMMAND_BYTE, NAO_E_ARG) != 0)
      return -1;
    if (keyboard_command_issue(IN_BUF_0x60, leituraaux, E_ARG) != 0)
      return -1;
  }
  else if (command == CHECK_KBC || command == CHECK_KEYBOARD_INTERFACE || command == DISABLE_KB_INTERFACE || command == ENABLE_KBD_INTERFACE)
    if (keyboard_command_issue(IN_BUF_0x64, command, NAO_E_ARG) != 0)
      return -1;

  return 0;
}
