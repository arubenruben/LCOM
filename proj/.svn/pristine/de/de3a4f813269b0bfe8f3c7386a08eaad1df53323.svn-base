#include <lcom/lcf.h>
#include <liblm.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include "i8042.h"
#include "i8254.h"
#include "kbc.h"
#include "kbd.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include "graphicalmacros.h"
#include "vbe1.h"
#include "bitmap.h"
#include "mousedriver.h"
#include "game.h"
#include "statemachine.h"
#include "rtc.h"
#include "graphics.h"
#include "uart.h"
#include "uart_macros.h"

int contador = 0;

void update_menu(event_game evt, boot_resources *start)
{
    unsigned char *pointer;
    switch (start->menu)
    {
    case MAIN_MENU:

        if (evt == NOTHING1)
        {
            start->menu = MAIN_MENU;
        }

        else if (evt == PLAY_PRESSED)
        {
            start->menu = GAME;
            game_reboot(start);
        }

        else if (evt == DIFICULTY_PRESSED)
        {
            start->menu = DIFICULTY_MENU;
        }

        else if (evt == EXIT_PRESSED)
            start->exit = 1;

        else if (evt == HIGHSCORE_PRESSED)
        {
            start->menu = HIGHSCORE_MENU;
        }

        else if (evt == MULTIPLAYER_PRESSED)
        {
            //envia 'r´ para a outra maquina
            start->maquina_pronta_para_multiplayer = 1;
            pointer = (unsigned char *)malloc(sizeof(unsigned char));
            if (pointer == NULL)
            {
                printf("Erro malloc linha 77, State Machine\n");
                return;
            }
            *pointer = 'r';
            fila_push(start->fila_transmitter, pointer);
            transmit_queue(start);
            start->menu = MULTIPLAYER_MENU;
        }
        break;

    case HIGHSCORE_MENU:
        if (evt == MAIN_MENU_PRESSED)
        {
            start->menu = MAIN_MENU;
        }

    case DIFICULTY_MENU:
        if (evt == EASY_PRESSED)
        {
            start->dificuldade = 1;
            start->background_sprite.speed = 2 * start->dificuldade;
            start->menu = MAIN_MENU;
        }

        else if (evt == MEDIUM_PRESSED)
        {
            start->dificuldade = 3;
            start->background_sprite.speed = 3;
            start->menu = MAIN_MENU;
        }

        else if (evt == HARD_PRESSED)
        {
            start->dificuldade = 5;
            start->background_sprite.speed = 5;
            start->menu = MAIN_MENU;
        }

        else if (evt == MAIN_MENU_PRESSED)
        {
            start->menu = MAIN_MENU;
        }
        break;

    case MULTIPLAYER_MENU:

        if (evt == NOTHING1)
        {
            receive_char(start);
        }

        if (evt == MAIN_MENU_PRESSED)
        {
            start->maquina_pronta_para_multiplayer = 0;
            pointer = (unsigned char *)malloc(sizeof(unsigned char));
            if (pointer == NULL)
            {
                printf("Erro malloc linha 77, State Machine\n");
                return;
            }
            *pointer = 'u';
            fila_push(start->fila_transmitter, pointer);
            transmit_queue(start);
            start->menu = MAIN_MENU;
        }

        if (evt == PRONTO2MAQUINAS)
        {
            game_reboot(start);
            start->menu = GAME_2PLAYERS;
            start->mouse_stats2.x = get_h_res() / 2;
            start->mouse_stats.x = get_h_res() / 2;
            start->mouse_stats2.y = get_v_res() / 2;
            start->mouse_stats.y = get_v_res() / 2;
        }
        break;

    case PAUSE_MENU:
        if (evt == CONTINUE_PRESSED)
        {
            start->menu = GAME;
        }

        else if (evt == EXIT_PRESSED)
        {
            start->exit = 1;
        }

        else if (evt == RESTART_PRESSED)
        {
            start->menu = GAME;
            scores_update(start);
            game_reboot(start);
        }

        else if (evt == MAIN_MENU_PRESSED)
        {
            start->p1.x = start->character_p1_move[0]->bitmapInfoHeader.width;
            start->p1.y = FLOOR_POSITION;
            start->menu = MAIN_MENU;
            scores_update(start);
            game_reboot(start);
        }
        break;

    case GAME:
        if (evt == ESC_PRESSED)
        {
            start->menu = PAUSE_MENU;
        }

        else if (evt == COLISION)
        {
            start->menu = GAME_OVER_MENU;
            scores_update(start);
        }
        break;

    case GAME_2PLAYERS:

        if (evt == BOTHDEAD)
        {   
            game_reboot(start);
            start->menu = GAME_OVER_MENU_2PLAYERS;
        }
        break;

    case GAME_OVER_MENU_2PLAYERS:
        if (evt == MAIN_MENU_PRESSED)
        {
            start->p1.x = start->character_p1_move[0]->bitmapInfoHeader.width;
            start->p1.y = FLOOR_POSITION;
            start->menu = MAIN_MENU;
            game_reboot(start);
        }

        else if (evt == EXIT_PRESSED)
        {
            start->exit = 1;
        }
        break;

    case GAME_OVER_MENU:
        if (evt == RESTART_PRESSED)
        {
            start->menu = GAME;
            game_reboot(start);
        }

        else if (evt == MAIN_MENU_PRESSED)
        {
            start->p1.x = start->character_p1_move[0]->bitmapInfoHeader.width;
            start->p1.y = FLOOR_POSITION;
            start->menu = MAIN_MENU;
            game_reboot(start);
        }

        else if (evt == EXIT_PRESSED)
        {
            start->exit = 1;
        }
        break;
    }
}

void update_character(event_character evt, boot_resources *start, int player)
{
    if (player == 1)
    {
        switch (start->state)
        {
        case RUN:
            if (evt == UP)
            {
                start->p1.y = start->p1.y - 150;
                start->conta_frames_character = 5;
                start->p1.width = start->character_p1_jump[0]->bitmapInfoHeader.width;
                start->p1.height = start->character_p1_jump[0]->bitmapInfoHeader.height;
                start->state = FLY1;
            }

            else if (evt == RIGHT)
            {
                start->p1.x = start->p1.x + 10;
            }

            else if (evt == LEFT)
            {
                start->p1.x = start->p1.x - 10;
            }

            else if (evt == NOTHING)
            {
                start->state = RUN;
            }

            else if (evt == JUMP)
            {
                start->conta_frames_character = 7;
                start->state = JUMPONCE;
            }
            break;

        case FLY1:
            if (evt == UP)
            {
                if (start->p1.y <= 120)
                {
                    start->p1.y = 120;
                }
                start->p1.y = start->p1.y - 15;
            }

            else if (evt == DOWN)
            {
                start->p1.y = start->p1.y + 20;
                if (start->p1.y > FLOOR_POSITION - 100)
                {
                    start->p1.y = FLOOR_POSITION;
                    start->conta_frames_character = 0;
                    start->state = RUN;
                }
            }

            else if (evt == RIGHT)
            {
                start->p1.x = start->p1.x + 10;
            }

            else if (evt == LEFT)
            {
                start->p1.x = start->p1.x - 10;
            }

            else if (evt == NOTHING)
            {
                if (start->p1.y < FLOOR_POSITION)
                {
                    start->p1.y = start->p1.y + 5;
                    start->state = FLY1;
                }
                if (start->p1.y > FLOOR_POSITION - 100)
                {
                    start->p1.y = FLOOR_POSITION;
                    start->conta_frames_character = 0;
                    start->state = RUN;
                }
            }
            break;

        case JUMPONCE:
            if (evt == CHAO)
            {
                start->p1.y = FLOOR_POSITION;
                start->conta_frames_character = 0;
                start->state = RUN;
            }
            if (evt == UP)
            {
                start->state = FLY1;
                start->p1.y = start->p1.y - 60;
                start->conta_frames_character = 5;
            }
            break;
        default:
            break;
        }
    }

    else if (player == 2)
    {
        switch (start->state2)
        {
        case RUN:
            if (evt == UP)
            {
                start->p2.y = start->p2.y - 150;
                start->conta_frames_character_p2 = 5;
                start->p2.width = start->character_p2_jump[0]->bitmapInfoHeader.width;
                start->p2.height = start->character_p2_jump[0]->bitmapInfoHeader.height;
                start->state2 = FLY1;
            }

            else if (evt == RIGHT)
            {
                start->p2.x = start->p2.x + 10;
            }

            else if (evt == LEFT)
            {
                start->p2.x = start->p2.x - 10;
            }

            else if (evt == NOTHING)
            {
                start->state2 = RUN;
            }

            else if (evt == JUMP)
            {
                start->conta_frames_character_p2 = 7;
                start->state2 = JUMPONCE;
            }
            break;

        case FLY1:
            if (evt == UP)
            {
                if (start->p2.y <= 120)
                {
                    start->p2.y = 120;
                }
                start->p2.y = start->p2.y - 15;
            }

            else if (evt == DOWN)
            {
                start->p2.y = start->p2.y + 20;
                if (start->p2.y > FLOOR_POSITION - 100)
                {
                    start->p2.y = FLOOR_POSITION;
                    start->conta_frames_character_p2 = 0;
                    start->state2 = RUN;
                }
            }

            else if (evt == RIGHT)
            {
                start->p2.x = start->p2.x + 10;
            }

            else if (evt == LEFT)
            {
                start->p2.x = start->p2.x - 10;
            }

            else if (evt == NOTHING)
            {
                if (start->p2.y < FLOOR_POSITION)
                {
                    start->p2.y = start->p2.y + 5;
                    start->state2 = FLY1;
                }
                if (start->p2.y > FLOOR_POSITION - 100)
                {
                    start->p2.y = FLOOR_POSITION;
                    start->conta_frames_character_p2 = 0;
                    start->state2 = RUN;
                }
            }
            break;

        case JUMPONCE:
            if (evt == CHAO)
            {
                start->p2.y = FLOOR_POSITION;
                start->conta_frames_character_p2 = 0;
                start->state2 = RUN;
            }
            if (evt == UP)
            {
                start->state2 = FLY1;
                start->p2.y = start->p2.y - 60;
                start->conta_frames_character_p2 = 5;
            }
            break;
        default:
            break;
        }
    }
    return;
}
