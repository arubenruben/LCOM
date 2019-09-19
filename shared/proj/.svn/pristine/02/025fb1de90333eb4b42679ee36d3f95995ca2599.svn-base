#include <lcom/lcf.h>
#include <minix/drivers.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include <stdbool.h>
#include <stdint.h>
#include <i8254.h>
#include "i8042.h"
#include "mousedriver.h"

int sys_inb_counter = 0;
int return_kbc_ih = 0;

uint8_t scancode = INITIALIZE0;

void(kbc_ih)()

{
  uint32_t statusregister = INITIALIZE0;
  uint32_t scancode32bit = INITIALIZE0, scancode8bit = INITIALIZE0;

  if (sys_inb(STAT_REG, &statusregister) != 0)
  { //ler valor so stat reg, para saber o estado das entradas se estão cheias ou não
    return_kbc_ih = -1;
    return; /* assuming it returns OK */
  }
  /* loop while 8042 output buffer is empty */
  if (statusregister & OBF)
  { // se estiver cheio o outbuff lemos

    if (sys_inb(OUT_BUF, &scancode32bit) != 0)
    {
      return_kbc_ih = -1; /* assuming it returns OK */
      return;
    }

    scancode8bit = (uint8_t)(scancode32bit & CAST_PARA_8BITS);

    if ((statusregister & (PAR_ERR | TO_ERR)) == 0)
    { //caso não acontecer algum erro
      return_kbc_ih = 1;
      scancode = scancode8bit;
      return;
    }
    else
    {
      return_kbc_ih = -1; // caso acontecer algum erro
      return;
    }
  }
  return;
}

uint8_t return_scancode()
{
  return scancode;
}

int(keyboard_command_issue)(uint8_t registo, uint8_t command)
{

  int tries = 5, i = 0;
  uint32_t stat32bit, lixo;
  uint8_t stat8bit;

  while (i < tries)
  {
    sys_inb(STAT_REG, &stat32bit); // ler o estado atual
    stat8bit = (uint8_t)(stat32bit & CAST_PARA_8BITS);
    //se o INBUF nao estiver cheio, escreve, senao espero

    if (stat8bit & OBF)
    {
      sys_inb(OUT_BUF, &lixo);
    }

    if ((stat8bit & IBF) == INITIALIZE0)
    { // se o inbuff estiver vazio mandamos para lá o command byte
      sys_outb(registo, command);
      return 0;
    }
    i++;
    tickdelay(micros_to_ticks(DELAY_US));
  }
  return -1;
}

int(keyboard_command_receive)(uint8_t *leitura)
{
  int tries = 5, i = 0;

  uint32_t stat32bit, commandbyte32bits = INITIALIZE0;
  uint8_t stat8bit, commandbyte8bits;

  while (i < tries)
  {

    sys_inb(STAT_REG, &stat32bit);

    stat8bit = (uint8_t)(stat32bit & CAST_PARA_8BITS);

    if (stat8bit & OBF)
    {
      sys_inb(OUT_BUF, &commandbyte32bits); /* assuming it returns OK */

      commandbyte8bits = (uint8_t)(commandbyte32bits & CAST_PARA_8BITS);

      if ((stat8bit & (PAR_ERR | TO_ERR)) == 0)
      {
        *leitura = commandbyte8bits;
        return 0;
      }
      else
      {
        printf("Par error\n");
        return -1;
      }
    }
    i++;
    tickdelay(micros_to_ticks(DELAY_US));
  }

  return -1;
}


int(keyboard_messaging)(uint8_t *leitura, uint8_t command) {
  uint32_t leituraaux;

  if (command == READ_COMMAND_BYTE) {
    if ((keyboard_command_issue(IN_BUF_0x64, READ_COMMAND_BYTE) != 0))
      return -1;
  }

  else if (command == WRITE_COMMAND_BYTE) {
    if ((keyboard_command_receive(leitura) != 0))
      return -1;

    *leitura = (*leitura) | COMMANDBYTE_ENABLE_KEYBOARD;

    leituraaux = *leitura;

    if (keyboard_command_issue(IN_BUF_0x64, WRITE_COMMAND_BYTE) != 0)
      return -1;
    if (keyboard_command_issue(IN_BUF_0x60, leituraaux) != 0)
      return -1;
  }
  else if (command == CHECK_KBC || command == CHECK_KEYBOARD_INTERFACE || command == DISABLE_KB_INTERFACE || command == ENABLE_KBD_INTERFACE)
    if (keyboard_command_issue(IN_BUF_0x64, command) != 0)
      return -1;

  return 0;
}

int(mouse_messaging)(uint8_t *leitura, uint8_t command)
{

  uint8_t acknowledgment_byte = NACK;
  //uint32_t acknowledgment_byte32bits;
  while (acknowledgment_byte == NACK)
  {

    if (keyboard_command_issue(IN_BUF_0x64, DISABLE_MOUSE) != 0)
      return -1;

    if ((keyboard_command_issue(IN_BUF_0x64, WRITE_BYTE_TO_MOUSE)) != 0)
    {
      printf("falhou o keyboard comand issue ao mandar o command na função mouse_issue\n");
      return -1;
    }
    if ((keyboard_command_issue(IN_BUF_0x60, command)) != 0)
    {
      printf("falhou issue do command \n");
      return -1;
    }

    if ((keyboard_command_receive(&acknowledgment_byte)) != 0)
    {
      printf("falhou o receive da leitura\n");
      return -1;
    }
  }
  if (acknowledgment_byte == ACK)
  {
    *leitura = acknowledgment_byte;
    return 0;
  }
  else if (acknowledgment_byte == ERROR)
  {
    printf("second consecutive invalid byte\n");
    return -1;
  }
  return -1;
}

int(data_processing)(struct packet *leitura)
{

  int sinalx, sinaly;
  uint16_t mousebyte16bits;

  if ((leitura->bytes[0] & L_B) != 0)
    leitura->lb = TRUE;
  else
    leitura->lb = FALSE;

  if ((leitura->bytes[0] & M_B) != 0)
    leitura->mb = TRUE;
  else
    leitura->mb = FALSE;

  if ((leitura->bytes[0] & R_B) != 0)
    leitura->rb = TRUE;
  else
    leitura->rb = FALSE;

  if ((leitura->bytes[0] & Y_OVFL) != 0)
    leitura->y_ov = TRUE;
  else
    leitura->y_ov = FALSE;

  if ((leitura->bytes[0] & X_OVFL) != 0)
    leitura->x_ov = TRUE;
  else
    leitura->x_ov = FALSE;

  if ((leitura->bytes[0] & X_SIGN) != 0)
  {
    sinalx = 1;
  }
  else
    sinalx = 0;

  if ((leitura->bytes[0] & Y_SIGN) != 0)
  {
    sinaly = 1;
  }
  else
    sinaly = 0;

  if (sinalx == 1)
  {
    mousebyte16bits = 0;
    mousebyte16bits = (mousebyte16bits | leitura->bytes[1]);
    mousebyte16bits = mousebyte16bits | Complemento_2;
    leitura->delta_x = mousebyte16bits;
  }
  else
  {
    mousebyte16bits = 0;
    mousebyte16bits = (mousebyte16bits | leitura->bytes[1]);

    leitura->delta_x = mousebyte16bits;
  }

  if (sinaly == 1)
  {
    mousebyte16bits = 0;
    mousebyte16bits = (mousebyte16bits | leitura->bytes[2]);
    mousebyte16bits = mousebyte16bits | Complemento_2;
    leitura->delta_y = mousebyte16bits;
  }
  else
  {
    mousebyte16bits = 0;
    mousebyte16bits = (mousebyte16bits | leitura->bytes[2]);
    leitura->delta_y = mousebyte16bits;
  }

  return 0;
}
