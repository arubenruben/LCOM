#include <lcom/lcf.h>
#include <minix/drivers.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include <stdbool.h>
#include <stdint.h>
#include "i8254.h"
#include "i8042.h"
#include "kbc.h"
#include "vetor.h"
#include "uart.h"
#include "statemachine.h"
#include "game.h"
#include "vbe1.h"

static int hook_id = 0x01; // hook id for the keyboard

int(keyboard_subscribe_int)(uint8_t *bit_no)
{

  if (bit_no == NULL)
  {
    return -1;
  }
  *bit_no = hook_id;
  if (sys_irqsetpolicy(IRQ_LINE_KEYBOARD, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != OK)
  {
    return -1;
  }
  return 0;
}

int(keyboard_unsubscribe_int)()
{

  if (sys_irqdisable(&hook_id) != OK)
  {
    return -1;
  }
  if (sys_irqrmpolicy(&hook_id) != OK)
  {
    return -1;
  }
  return 0;
  //check
}

void check_borders_p1(boot_resources *start)
{
  if (start->p1.x > (get_h_res() - start->p1.width))
  {
    start->p1.x = get_h_res() - start->p1.width;
  }
  else if (start->p1.x < 0)
  {
    start->p1.x = 0;
  }
  if (start->p1.y < 0)
  {
    start->p1.y = 0;
  }
  else if (start->p1.y > get_v_res() - start->p1.height)
  {
    start->p1.y = get_v_res() - start->p1.height;
  }
  return;
}

void check_borders_p2(boot_resources *start)
{
  if (start->p2.x > (get_h_res() - start->p2.width))
  {
    start->p2.x = get_h_res() - start->p2.width;
  }
  else if (start->p2.x < 0)
  {
    start->p2.x = 0;
  }
  if (start->p2.y < 0)
  {
    start->p2.y = 0;
  }
  else if (start->p2.y > get_v_res() - start->p2.height)
  {
    start->p2.y = get_v_res() - start->p2.height;
  }
  return;
}

void kbd_processing_p2(boot_resources *start)
{
  if (start->menu == GAME || start->menu == GAME_2PLAYERS)
  {
    if (start->multiple_bytes2 == 1)
    {
      start->multiple_bytes2 = 0;
      start->scancode2 = 0x00;
    }
    else if (start->scancode2 == 0xE0)
    {
      start->multiple_bytes2 = 1;
    }

    if (start->scancode2 == W_KEY_MAKECODE)
    {
      update_character(UP, start, 2);
    }
    if (start->scancode2 == A_KEY_MAKECODE)
    {
      update_character(LEFT, start, 2);
    }
    if (start->scancode2 == D_KEY_MAKECODE)
    {
      update_character(RIGHT, start, 2);
    }
    if (start->scancode2 == S_KEY_MAKECODE)
    {
      update_character(DOWN, start, 2);
    }
    if (start->scancode2 == SPACE_KEY_MAKECODE)
    {
      update_character(JUMP, start, 2);
    }
    check_borders_p2(start);
  }
  return;
}

void kbd_processing(boot_resources *start)
{
  if (start->menu == GAME || start->menu == GAME_2PLAYERS)
  {
    if (start->multiple_bytes == 1)
    {
      start->multiple_bytes = 0;
      start->scancode = 0x00;
    }
    if (start->scancode == 0xE0)
    {
      start->multiple_bytes = 1;
    }

    if (start->scancode == W_KEY_MAKECODE)
    {
      update_character(UP, start, 1);
    }
    if (start->scancode == A_KEY_MAKECODE)
    {
      update_character(LEFT, start, 1);
    }
    if (start->scancode == D_KEY_MAKECODE)
    {
      update_character(RIGHT, start, 1);
    }
    if (start->scancode == S_KEY_MAKECODE)
    {
      update_character(DOWN, start, 1);
    }
    if (start->scancode == SPACE_KEY_MAKECODE)
    {
      update_character(JUMP, start, 1);
    }
    if (start->menu == GAME)
    {
      if (start->scancode == ESC_BREAK)
      {
        update_menu(ESC_PRESSED, start);
      }
      if (start->scancode == R_KEY_MAKECODE && start->full_rage == 1)
      {
        start->full_rage = 0;
        start->rage_mode = 1;
      }
    }
    check_borders_p1(start);
  }
  return;
}
