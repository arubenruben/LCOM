#include <lcom/lcf.h>
#include <minix/drivers.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <i8254.h>
#include "kbd.h"
#include "i8042.h"
#include "kbc.h"

static int hook_id = 0x01; // hookid utilizado para a funçao irq_setpolicy()

int(kb_subscribe_int)(uint8_t *bit_no) {

  if (bit_no == NULL) { //erro caso a apontador bit no não seja valido
    return -1;
  }

  *bit_no = hook_id; // bit no recebe o hook id que nos configuramos para mandarmos para o kernel

  if (sys_irqsetpolicy(IRQ_LINE_KEYBOARD, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != OK) { //da set a policy
    return -1;
  }

  return 0;
  //check
}

int(keyboard_unsubscribe_int)() {

  if (sys_irqdisable(&hook_id) != OK) { //disable primeiro, para depois tirar a policy set
    return -1;
  }
  if (sys_irqrmpolicy(&hook_id) != OK) { //disbable nos interrupts
    return -1;
  }
  return 0;
  //check
}
