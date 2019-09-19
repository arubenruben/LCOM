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

int mouse_hook_id = 12;   //hook id for the mouse
static uint8_t mousebyte; // byte from the mouse packet

int(mouse_subscribe_int)(uint8_t *bit_no)
{
    if (bit_no == NULL)
    {
        return -1;
    }
    *bit_no = (uint8_t)mouse_hook_id;

    if (sys_irqsetpolicy(IRQ_LINE_MOUSE, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id) != OK)
    {
        printf("ERRO , sys_irqsetpolicy falhou\n");
        return -1;
    }
    return 0;
}

int(mouse_unsubscribe_int)()
{
    if (sys_irqdisable(&mouse_hook_id) != OK)
    {
        printf("ERRO , sys_irqdisable falhou\n");
        return -1;
    }
    if (sys_irqrmpolicy(&mouse_hook_id) != OK)
    {
        printf("ERRO , sys_irqrmpolicy falhou\n");
        return -1;
    }
    return 0;
}

void(mouse_ih)()
{
    uint32_t statusregister = INITIALIZE0;
    uint32_t mousebyte32bit = INITIALIZE0, mousebyte8bits = INITIALIZE0;
    if (sys_inb(STAT_REG, &statusregister) != 0)
    {
        return;
    }
    /* loop while 8042 output buffer is empty */
    if (statusregister & OBF)
    {

        if (sys_inb(OUT_BUF, &mousebyte32bit) != 0)
        { /* assuming it returns OK */
            return;
        }
        mousebyte8bits = (uint8_t)(mousebyte32bit & CAST_PARA_8BITS);

        if ((statusregister & (PAR_ERR | TO_ERR)) == 0)
        {
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

uint8_t return_mousebyte()
{
    return mousebyte;
}

void mouse_processing_p2(boot_resources *start)
{
    start->mouse_stats2.x += start->mouse_packet2.delta_x;
    start->mouse_stats2.y -= start->mouse_packet2.delta_y;

    if (start->mouse_stats2.x >= get_h_res())
    {
        start->mouse_stats2.x = get_h_res() - 10;
    }

    else if (start->mouse_stats2.x <= 0)
    {
        start->mouse_stats2.x = 0;
    }

    if (start->mouse_stats2.y >= get_v_res())
    {
        start->mouse_stats2.y = get_v_res() - 10;
    }

    else if (start->mouse_stats2.y <= 0)
    {
        start->mouse_stats2.y = 0;
    }
    if (start->menu == GAME_2PLAYERS)
    {
        if (start->mouse_packet2.lb == TRUE && start->mouse_packet2.rb == FALSE)
        {
            if (start->conta_balas2 > 0 && start->lb_pressed2 == 0)
            {
                vetor_insere(start->vec_p2, start, Is_Projectil, -2, -1, 2);
                start->lb_pressed2 = 1;
                start->conta_balas2--;
            }
        }

        else if (start->mouse_packet2.lb == FALSE)
        {
            start->lb_pressed2 = 0;
        }

        if (start->mouse_packet2.lb == FALSE && start->mouse_packet2.rb == TRUE && start->p2.y == FLOOR_POSITION)
        {
            if (start->conta_sword_ataques2 > 0 && start->rb_pressed2 == 0)
            {
                start->rb_pressed2 = 1;
                start->p2.width = start->sword[0]->bitmapInfoHeader.width;
                start->p2.height = start->sword[0]->bitmapInfoHeader.height;
                start->conta_frames_character_p2 = 9;
                start->conta_sword_ataques2--;
            }
        }

        else if (start->mouse_packet2.rb == FALSE)
        {
            start->rb_pressed2 = 0;
        }
    }

    return;
}

void mouse_processing(boot_resources *start)
{
    start->mouse_byte = return_mousebyte();
    if (start->contador_bytes == 0)
    {
        if ((start->mouse_byte & BIT(3)) != 0)
        {
            start->mouse_packet.bytes[0] = start->mouse_byte;
            start->contador_bytes++;
        }

        else
            return;
    }

    else if (start->contador_bytes == 1)
    {
        start->mouse_packet.bytes[1] = start->mouse_byte;
        start->contador_bytes++;
    }

    else if (start->contador_bytes == 2)
    {
        start->mouse_packet.bytes[2] = start->mouse_byte;
        data_processing(&(start->mouse_packet));
        start->mouse_stats.x += start->mouse_packet.delta_x;
        start->mouse_stats.y -= start->mouse_packet.delta_y;
        start->contador_bytes = 0;

        if (start->mouse_stats.x >= get_h_res())
        {
            start->mouse_stats.x = get_h_res() - 10;
        }

        else if (start->mouse_stats.x <= 0)
        {
            start->mouse_stats.x = 0;
        }

        if (start->mouse_stats.y >= get_v_res())
        {
            start->mouse_stats.y = get_v_res() - 10;
        }

        else if (start->mouse_stats.y <= 0)
        {
            start->mouse_stats.y = 0;
        }

        if (start->menu == MAIN_MENU)
        {
            if (start->mouse_stats.x > 524 && start->mouse_stats.x < 654 && start->mouse_stats.y < 258 && start->mouse_stats.y > 201 && start->mouse_packet.lb == TRUE)
            {
                update_menu(PLAY_PRESSED, start);
            }
            if (start->mouse_stats.x > 524 && start->mouse_stats.x < 654 && start->mouse_stats.y < 315 && start->mouse_stats.y > 260 && start->mouse_packet.lb == TRUE)
            {
                update_menu(MULTIPLAYER_PRESSED, start);
            }
            if (start->mouse_stats.x > 524 && start->mouse_stats.x < 654 && start->mouse_stats.y < 371 && start->mouse_stats.y > 317 && start->mouse_packet.lb == TRUE)
            {
                update_menu(DIFICULTY_PRESSED, start);
            }
            if (start->mouse_stats.x > 524 && start->mouse_stats.x < 654 && start->mouse_stats.y < 428 && start->mouse_stats.y > 374 && start->mouse_packet.lb == TRUE)
            {
                update_menu(HIGHSCORE_PRESSED, start);
            }
            if (start->mouse_stats.x > 524 && start->mouse_stats.x < 654 && start->mouse_stats.y < 486 && start->mouse_stats.y > 432 && start->mouse_packet.lb == TRUE)
            {
                update_menu(EXIT_PRESSED, start);
            }
        }

        else if (start->menu == DIFICULTY_MENU)
        {
            if (start->mouse_stats.x > 504 && start->mouse_stats.x < 639 && start->mouse_stats.y < 278 && start->mouse_stats.y > 224 && start->mouse_packet.lb == TRUE)
            {
                update_menu(HARD_PRESSED, start);
            }
            if (start->mouse_stats.x > 504 && start->mouse_stats.x < 639 && start->mouse_stats.y < 339 && start->mouse_stats.y > 287 && start->mouse_packet.lb == TRUE)
            {
                update_menu(MEDIUM_PRESSED, start);
            }
            if (start->mouse_stats.x > 504 && start->mouse_stats.x < 639 && start->mouse_stats.y < 402 && start->mouse_stats.y > 347 && start->mouse_packet.lb == TRUE)
            {
                update_menu(EASY_PRESSED, start);
            }
            if (start->mouse_stats.x > 504 && start->mouse_stats.x < 639 && start->mouse_stats.y < 465 && start->mouse_stats.y > 410 && start->mouse_packet.lb == TRUE)
            {
                update_menu(MAIN_MENU_PRESSED, start);
            }
        }

        else if (start->menu == HIGHSCORE_MENU)
        {
            if (start->mouse_stats.x > 642 && start->mouse_stats.x < 761 && start->mouse_stats.y < 462 && start->mouse_stats.y > 411 && start->mouse_packet.lb == TRUE)
            {
                update_menu(MAIN_MENU_PRESSED, start);
            }
        }

        else if (start->menu == PAUSE_MENU)
        {
            if (start->mouse_stats.x > 333 && start->mouse_stats.x < 464 && start->mouse_stats.y < 278 && start->mouse_stats.y > 224 && start->mouse_packet.lb == TRUE)
            {
                update_menu(CONTINUE_PRESSED, start);
            }
            if (start->mouse_stats.x > 333 && start->mouse_stats.x < 464 && start->mouse_stats.y < 339 && start->mouse_stats.y > 287 && start->mouse_packet.lb == TRUE)
            {
                update_menu(RESTART_PRESSED, start);
            }
            if (start->mouse_stats.x > 333 && start->mouse_stats.x < 464 && start->mouse_stats.y < 402 && start->mouse_stats.y > 347 && start->mouse_packet.lb == TRUE)
            {
                update_menu(MAIN_MENU_PRESSED, start);
            }
            if (start->mouse_stats.x > 333 && start->mouse_stats.x < 464 && start->mouse_stats.y < 465 && start->mouse_stats.y > 410 && start->mouse_packet.lb == TRUE)
            {
                update_menu(EXIT_PRESSED, start);
            }
        }

        else if (start->menu == GAME_OVER_MENU)
        {
            if (start->mouse_stats.x > 336 && start->mouse_stats.x < 468 && start->mouse_stats.y < 317 && start->mouse_stats.y > 263 && start->mouse_packet.lb == TRUE)
            {
                update_menu(RESTART_PRESSED, start);
            }
            if (start->mouse_stats.x > 336 && start->mouse_stats.x < 468 && start->mouse_stats.y < 379 && start->mouse_stats.y > 324 && start->mouse_packet.lb == TRUE)
            {
                update_menu(MAIN_MENU_PRESSED, start);
            }
            if (start->mouse_stats.x > 336 && start->mouse_stats.x < 468 && start->mouse_stats.y < 440 && start->mouse_stats.y > 387 && start->mouse_packet.lb == TRUE)
            {
                update_menu(EXIT_PRESSED, start);
            }
        }

        else if (start->menu == MULTIPLAYER_MENU)
        {
            if (start->mouse_stats.x > 503 && start->mouse_stats.x < 633 && start->mouse_stats.y < 464 && start->mouse_stats.y > 407 && start->mouse_packet.lb == TRUE)
            {
                update_menu(MAIN_MENU_PRESSED, start);
            }
        }

        else if (start->menu == GAME_OVER_MENU_2PLAYERS)
        {
            if (start->mouse_stats.x > 336 && start->mouse_stats.x < 468 && start->mouse_stats.y < 408 && start->mouse_stats.y > 356 && start->mouse_packet.lb == TRUE)
            {
                update_menu(MAIN_MENU_PRESSED, start);
            }
            else if (start->mouse_stats.x > 336 && start->mouse_stats.x < 468 && start->mouse_stats.y < 477 && start->mouse_stats.y > 419 && start->mouse_packet.lb == TRUE)
            {
                update_menu(EXIT_PRESSED, start);
            }
        }

        else if (start->menu == GAME)
        {
            if (start->rage_mode == 0)
            {
                if (start->mouse_packet.lb == TRUE && start->mouse_packet.rb == FALSE)
                {
                    if (start->conta_balas > 0 && start->lb_pressed == 0)
                    {
                        vetor_insere(start->vec, start, Is_Projectil, -2, -1, 1);
                        start->lb_pressed = 1;
                        start->conta_balas--;
                    }
                }

                else if (start->mouse_packet.lb == FALSE)
                {
                    start->lb_pressed = 0;
                }

                if (start->mouse_packet.lb == FALSE && start->mouse_packet.rb == TRUE && start->p1.y == FLOOR_POSITION)
                {
                    if (start->conta_sword_ataques > 0 && start->rb_pressed == 0)
                    {
                        start->rb_pressed = 1;
                        start->p1.width = start->sword[0]->bitmapInfoHeader.width;
                        start->p1.height = start->sword[0]->bitmapInfoHeader.height;
                        start->conta_frames_character = 9;
                        start->conta_sword_ataques--;
                    }
                }

                else if (start->mouse_packet.rb == FALSE)
                {
                    start->rb_pressed = 0;
                }
            }

            else if (start->rage_mode == 1)
            {
                if (start->mouse_packet.lb == TRUE && start->mouse_packet.rb == FALSE)
                {
                    start->lb_pressed = 1;
                    vetor_insere(start->vec, start, Is_Projectil, -2, -1, 1);
                }

                else if (start->mouse_packet.lb == FALSE && start->mouse_packet.rb == FALSE)
                {
                    start->lb_pressed = 0;
                }

                if (start->mouse_packet.lb == FALSE && start->mouse_packet.rb == TRUE && start->p1.y == FLOOR_POSITION)
                {
                    start->p1.width = start->sword[2]->bitmapInfoHeader.width;
                    start->p1.height = start->sword[2]->bitmapInfoHeader.height;
                    start->conta_frames_character = 9;
                    start->conta_sword_ataques--;
                }
            }
        }
        else if (start->menu == GAME_2PLAYERS)
        {

            if (start->mouse_packet.lb == TRUE && start->mouse_packet.rb == FALSE)
            {
                if (start->conta_balas > 0 && start->lb_pressed == 0)
                {
                    vetor_insere(start->vec, start, Is_Projectil, -2, -1, 1);
                    start->lb_pressed = 1;
                    start->conta_balas--;
                }
            }

            else if (start->mouse_packet.lb == FALSE)
            {
                start->lb_pressed = 0;
            }

            if (start->mouse_packet.lb == FALSE && start->mouse_packet.rb == TRUE && start->p1.y == FLOOR_POSITION)
            {
                if (start->conta_sword_ataques > 0 && start->rb_pressed == 0)
                {
                    start->rb_pressed = 1;
                    start->p1.width = start->sword[0]->bitmapInfoHeader.width;
                    start->p1.height = start->sword[0]->bitmapInfoHeader.height;
                    start->conta_frames_character = 9;
                    start->conta_sword_ataques--;
                }
            }

            else if (start->mouse_packet.rb == FALSE)
            {
                start->rb_pressed = 0;
            }
        }
    }
    return;
}
