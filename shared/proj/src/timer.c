#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <minix/drivers.h>
#include <minix/syslib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "i8254.h"

static int hook_id; // hook id used in the set policy function

int(util_get_LSB)(uint16_t val, uint8_t *lsb);
int(util_get_LSB)(uint16_t val, uint8_t *lsb)
{

  if (lsb == NULL)
    return 1;
  *lsb = 0x00;
  *lsb = (uint8_t)(*lsb) | val;
  return 0;
}
int(util_get_MSB)(uint16_t val, uint8_t *msb);
int(util_get_MSB)(uint16_t val, uint8_t *msb)
{

  if (msb == NULL)
    return 1;
  *msb = 0x00;
  val = val >> 8;
  *msb = (uint8_t)(*msb) | val;
  return 0;
}

uint8_t(timerselector)(uint8_t timer)
{

  if (timer == 0)
    timer = TIMER_0; //selects timer 0
  else if (timer == 1)
    timer = TIMER_1; //selects timer 1
  else if (timer == 2)
    timer = TIMER_2; //selects timer 2
  return timer;
}

int(timer_subscribe_int)(uint8_t *bit_no)
{

  if (bit_no == NULL)
  {
    return 1;
  }
  hook_id = 0;
  *bit_no = hook_id;
  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != OK)
  {
    return 1;
  }

  return 0;
}

int(timer_unsubscribe_int)()
{

  if (sys_irqdisable(&hook_id) != OK)
  {
    return 1;
  }
  if (sys_irqrmpolicy(&hook_id) != OK)
  {
    return 1;
  }
  return 0;
}

int(timer_set_frequency)(uint8_t(timer), uint32_t(freq))
{

  if ((timer < 0 || timer > 2) || (freq <= 0))
  {
    return -1;
  }

  uint8_t st, stout = INITIALIZE0, timerref = INITIALIZE0;
  uint8_t msb, lsb = INITIALIZE0;
  uint16_t outbbyte = INITIALIZE0;

  outbbyte = (uint32_t)(TIMER_FREQ / freq); // freq que vamos efetivamente mandar para o contador

  if (timer_get_conf(timer, &st) != 0)
  { //tiro a config atual, para a preservar
    return 1;
  }
  timerref = timerselector(timer);

  stout = st;
  stout = stout & FOURLSB_STATUSBYTE; //preserva a integridade do st, o byte retorno,o e preserva os 4 bits menos significativos.

  stout = stout | TIMER_LSB_MSB; //o modo preferido, no guiao para dar set ao timer e LSB Followed by MSB

  //preparar a control word para incidir sobre o timer pretendido
  //caso timerref == TIMER_0 não precisamos de fazer nada pois os  bits correspondente ja estão a 00
  if (timerref == TIMER_1)
    stout = stout | TIMER_SEL1; // bits 6 e 5 passam a 01 invés de 00

  else if (timerref == TIMER_2)
    stout = stout | TIMER_SEL2; //bits 6 e 5 passam a 10 inves de 00

  //mandar a control word
  if (sys_outb(TIMER_CTRL, stout) != 0)
  { //caso aconteca algum erro ao mandar a control word
    return 1;
  }
  if (util_get_LSB(outbbyte, &lsb) != 0)
  { //tirar os LSBs para dar upload para o register de 8 bits followed by MSB
    return 1;
  }

  if (sys_outb(timerref, lsb) != 0)
  { //mandar os Lsb da freq para o timer
    return 1;
  }

  if (util_get_MSB(outbbyte, &msb) != 0)
  { //tira o MSB para mandar os restantes 8 bits para o timer com a frequecia certa
    return 1;
  }

  if (sys_outb(timerref, msb) != 0)
  { //mandar os Msb da freq para o timer
    return 1;
  }

  return 0;
}
