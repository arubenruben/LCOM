#include <lcom/lcf.h>
#include <minix/drivers.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include <stdbool.h>
#include <stdint.h>
#include "i8254.h"
#include "i8042.h"
#include "kbc.h"
#include <lcom/lab4.h>
#include "mousedriver.h"

int mouse_hook_id = 12; // hookid utilizado para a funçao irq_setpolicy()
uint8_t mousebyte;

int(mouse_subscribe_int)(uint8_t *bit_no)
{

  if (bit_no == NULL)
  { //erro caso a apontador bit no não seja valido
    return -1;
  }

  *bit_no = (uint8_t)mouse_hook_id; // bit no recebe o hook id que nos configuramos para mandarmos para o kernel

  if (sys_irqsetpolicy(IRQ_LINE_MOUSE, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id) != OK)
  { //da set a policy
    printf("ERRO , sys_irqsetpolicy falhou\n");
    return -1;
  }

  return 0;
  //che
}

int(mouse_unsubscribe_int)()
{

  if (sys_irqdisable(&mouse_hook_id) != OK)
  { //disable primeiro, para depois tirar a policy set
    printf("ERRO , sys_irqdisable falhou\n");
    return -1;
  }
  if (sys_irqrmpolicy(&mouse_hook_id) != OK)
  { //disbable nos interrupts
    printf("ERRO , sys_irqrmpolicy falhou\n");
    return -1;
  }
  return 0;
  //check
}

void(mouse_ih)()
{

  uint32_t statusregister = INITIALIZE0;
  uint32_t mousebyte32bit = INITIALIZE0, mousebyte8bits = INITIALIZE0;
  if (sys_inb(STAT_REG, &statusregister) != 0)
  {         //ler valor so stat reg, para saber o estado das entradas se estão cheias ou não
    return; /* assuming it returns OK */
  }
  /* loop while 8042 output buffer is empty */
  if (statusregister & OBF)
  { // se estiver cheio o outbuff lemos

    if (sys_inb(OUT_BUF, &mousebyte32bit) != 0)
    { /* assuming it returns OK */
      return;
    }

    mousebyte8bits = (uint8_t)(mousebyte32bit & CAST_PARA_8BITS);

    if ((statusregister & (PAR_ERR | TO_ERR)) == 0)
    { //caso não acontecer algum erro
      if ((statusregister & AUX) != 0)
        mousebyte = mousebyte8bits;
      return;
    }
    else
    {
      return;
    }
  }
  return;
}


