#include <lcom/lcf.h>
#include <stdlib.h>
#include "bitmap.h"
#include "time.h"
#include "mousedriver.h"
#include "kbc.h"
#include "kbd.h"
#include "i8042.h"
#include "i8254.h"
#include "graphicalmacros.h"
#include "graphics.h"
#include "vetor.h"
#include "statemachine.h"
#include "rtc.h"
#include "game.h"
#include "vbe1.h"
#include "uart.h"
#include "uart_macros.h"
#include "fila.h"

boot_resources *game_load()
{
    uint8_t timer_bit_no;
    uint8_t keyboard_bit_no;
    uint8_t mouse_bit_no;
    uint8_t rtc_bit_no;
    uint8_t uart_bit_no;

    extern int mouse_hook_id;
    boot_resources *load_at_start = (boot_resources *)malloc(sizeof(boot_resources));

    if (timer_subscribe_int(&timer_bit_no) != 0)
    {
        printf("Erro no timer subscribe\n");
        return NULL;
    }
    if (mouse_subscribe_int(&mouse_bit_no) != 0)
    {
        printf("Erro no mouse subscribe\n");
        return NULL;
    }
    if (keyboard_subscribe_int(&keyboard_bit_no) != 0)
    {
        printf("Erro no keyboard subscribe\n");
        return NULL;
    }
    if (rtc_subscribe_int(&rtc_bit_no) != 0)
    {
        printf("Erro no RTC subscribe\n");
        return NULL;
    }
    if (uart_subscribe_int(&uart_bit_no) != 0)
    {
        printf("Erro no RTC subscribe\n");
        return NULL;
    }

    load_at_start->timer_irq_set = BIT(timer_bit_no);
    load_at_start->kbd_irq_set = BIT(keyboard_bit_no);
    load_at_start->mouse_irq_set = BIT(mouse_bit_no);
    load_at_start->uart_irq_set = BIT(uart_bit_no);
    load_at_start->background1 = loadBitmap("home/lcom/labs/proj/res/backgroundfinal.bmp");
    load_at_start->character_p1_move[0] = loadBitmap("home/lcom/labs/proj/res/alucardmove1.bmp");
    load_at_start->character_p1_move[1] = loadBitmap("home/lcom/labs/proj/res/alucardmove2.bmp");
    load_at_start->character_p1_move[2] = loadBitmap("home/lcom/labs/proj/res/alucardmove3.bmp");
    load_at_start->character_p1_move[3] = loadBitmap("home/lcom/labs/proj/res/alucardmove4.bmp");
    load_at_start->character_p1_move[4] = loadBitmap("home/lcom/labs/proj/res/alucardmove5.bmp");
    load_at_start->character_p2_move[0] = loadBitmap("home/lcom/labs/proj/res/alucardmove1_p2.bmp");
    load_at_start->character_p2_move[1] = loadBitmap("home/lcom/labs/proj/res/alucardmove2_p2.bmp");
    load_at_start->character_p2_move[2] = loadBitmap("home/lcom/labs/proj/res/alucardmove3_p2.bmp");
    load_at_start->character_p2_move[3] = loadBitmap("home/lcom/labs/proj/res/alucardmove4_p2.bmp");
    load_at_start->character_p2_move[4] = loadBitmap("home/lcom/labs/proj/res/alucardmove5_p2.bmp");
    load_at_start->mouse_icon = loadBitmap("home/lcom/labs/proj/res/cursor11.bmp");
    load_at_start->axe_taurus1 = loadBitmap("home/lcom/labs/proj/res/enemy1.bmp");
    load_at_start->character_p1_jump[0] = loadBitmap("home/lcom/labs/proj/res/alucardjump1.bmp");
    load_at_start->character_p1_jump[1] = loadBitmap("home/lcom/labs/proj/res/alucardjump2.bmp");
    load_at_start->character_p1_jump[2] = loadBitmap("home/lcom/labs/proj/res/alucardjump3.bmp");
    load_at_start->character_p1_jump[3] = loadBitmap("home/lcom/labs/proj/res/alucardjump4.bmp");
    load_at_start->character_p2_jump[0] = loadBitmap("home/lcom/labs/proj/res/alucardjump1_p2.bmp");
    load_at_start->character_p2_jump[1] = loadBitmap("home/lcom/labs/proj/res/alucardjump2_p2.bmp");
    load_at_start->character_p2_jump[2] = loadBitmap("home/lcom/labs/proj/res/alucardjump3_p2.bmp");
    load_at_start->character_p2_jump[3] = loadBitmap("home/lcom/labs/proj/res/alucardjump4_p2.bmp");
    load_at_start->fantasma_bitmap = loadBitmap("home/lcom/labs/proj/res/fantasma1.bmp");
    load_at_start->character_idle[0] = loadBitmap("home/lcom/labs/proj/res/Alucardidle1.bmp");
    load_at_start->character_idle[1] = loadBitmap("home/lcom/labs/proj/res/Alucardidle2.bmp");
    load_at_start->character_idle[2] = loadBitmap("home/lcom/labs/proj/res/Alucardidle3.bmp");
    load_at_start->character_idle[3] = loadBitmap("home/lcom/labs/proj/res/Alucardidle4.bmp");
    load_at_start->character_idle[4] = loadBitmap("home/lcom/labs/proj/res/Alucardidle5.bmp");
    load_at_start->fire_left = loadBitmap("home/lcom/labs/proj/res/fire_left.bmp");
    load_at_start->fire_right = loadBitmap("home/lcom/labs/proj/res/fire_right.bmp");
    load_at_start->fire_down = loadBitmap("home/lcom/labs/proj/res/fire_down.bmp");
    load_at_start->fire_up = loadBitmap("home/lcom/labs/proj/res/fire_up.bmp");
    load_at_start->fire_left_p2 = loadBitmap("home/lcom/labs/proj/res/fire_left_p2.bmp");
    load_at_start->fire_right_p2 = loadBitmap("home/lcom/labs/proj/res/fire_right_p2.bmp");
    load_at_start->fire_down_p2 = loadBitmap("home/lcom/labs/proj/res/fire_down_p2.bmp");
    load_at_start->fire_up_p2 = loadBitmap("home/lcom/labs/proj/res/fire_up_p2.bmp");
    load_at_start->sword[0] = loadBitmap("home/lcom/labs/proj/res/sword1.bmp");
    load_at_start->sword[1] = loadBitmap("home/lcom/labs/proj/res/sword2.bmp");
    load_at_start->sword[2] = loadBitmap("home/lcom/labs/proj/res/sword3.bmp");
    load_at_start->sword[3] = loadBitmap("home/lcom/labs/proj/res/sword4.bmp");
    load_at_start->sword[4] = loadBitmap("home/lcom/labs/proj/res/sword5.bmp");
    load_at_start->sword_p2[0] = loadBitmap("home/lcom/labs/proj/res/sword1_p2.bmp");
    load_at_start->sword_p2[1] = loadBitmap("home/lcom/labs/proj/res/sword2_p2.bmp");
    load_at_start->sword_p2[2] = loadBitmap("home/lcom/labs/proj/res/sword3_p2.bmp");
    load_at_start->sword_p2[3] = loadBitmap("home/lcom/labs/proj/res/sword4_p2.bmp");
    load_at_start->sword_p2[4] = loadBitmap("home/lcom/labs/proj/res/sword5_p2.bmp");
    load_at_start->main_menu = loadBitmap("home/lcom/labs/proj/res/mainmenu.bmp");
    load_at_start->game_over_menu = loadBitmap("home/lcom/labs/proj/res/gameovermenu.bmp");
    load_at_start->dificulty_menu = loadBitmap("home/lcom/labs/proj/res/dificultymenu.bmp");
    load_at_start->pause_menu = loadBitmap("home/lcom/labs/proj/res/pause.bmp");
    load_at_start->highscore_menu = loadBitmap("home/lcom/labs/proj/res/highscore.bmp");
    load_at_start->sword_ataque = loadBitmap("home/lcom/labs/proj/res/swordataque.bmp");
    load_at_start->numerical[1] = loadBitmap("home/lcom/labs/proj/res/um.bmp");
    load_at_start->numerical[2] = loadBitmap("home/lcom/labs/proj/res/dois.bmp");
    load_at_start->numerical[3] = loadBitmap("home/lcom/labs/proj/res/tres.bmp");
    load_at_start->numerical[4] = loadBitmap("home/lcom/labs/proj/res/quatro.bmp");
    load_at_start->numerical[5] = loadBitmap("home/lcom/labs/proj/res/cinco.bmp");
    load_at_start->numerical[6] = loadBitmap("home/lcom/labs/proj/res/seis.bmp");
    load_at_start->numerical[7] = loadBitmap("home/lcom/labs/proj/res/sete.bmp");
    load_at_start->numerical[8] = loadBitmap("home/lcom/labs/proj/res/oito.bmp");
    load_at_start->numerical[9] = loadBitmap("home/lcom/labs/proj/res/nove.bmp");
    load_at_start->numerical[0] = loadBitmap("home/lcom/labs/proj/res/zero.bmp");
    load_at_start->ragebar[4] = loadBitmap("home/lcom/labs/proj/res/fullragebar.bmp");
    load_at_start->ragebar[0] = loadBitmap("home/lcom/labs/proj/res/ragebar0.bmp");
    load_at_start->ragebar[1] = loadBitmap("home/lcom/labs/proj/res/ragebar25.bmp");
    load_at_start->ragebar[2] = loadBitmap("home/lcom/labs/proj/res/ragebar50.bmp");
    load_at_start->ragebar[3] = loadBitmap("home/lcom/labs/proj/res/ragebar75.bmp");
    load_at_start->infinity = loadBitmap("home/lcom/labs/proj/res/infinity.bmp");
    load_at_start->pressr = loadBitmap("home/lcom/labs/proj/res/pressr.bmp");
    load_at_start->life = loadBitmap("home/lcom/labs/proj/res/vida.bmp");
    load_at_start->Helldog_bitmap = loadBitmap("home/lcom/labs/proj/res/helldog.bmp");
    load_at_start->slash = loadBitmap("home/lcom/labs/proj/res/barra.bmp");
    load_at_start->multiplayer_menu = loadBitmap("home/lcom/labs/proj/res/multiplayer_menu.bmp");
    load_at_start->game_over_menu_multiplayer_win = loadBitmap("home/lcom/labs/proj/res/gameovermenuwin.bmp");
    load_at_start->game_over_menu_multiplayer_lose = loadBitmap("home/lcom/labs/proj/res/gameovermenulose.bmp");
    load_at_start->game_over_menu_multiplayer_draw = loadBitmap("home/lcom/labs/proj/res/gameovermenudraw.bmp");

    load_at_start->dificuldade = 1;
    load_at_start->menu = MAIN_MENU;
    load_at_start->exit = 0;
    load_at_start->background_sprite.x = 0;
    load_at_start->background_sprite.bmp = load_at_start->background1;
    load_at_start->background_sprite.speed = 2;
    load_at_start->background_sprite.width = load_at_start->background1->bitmapInfoHeader.width;
    load_at_start->background_sprite.height = load_at_start->background1->bitmapInfoHeader.height;
    load_at_start->fila_receiver = fila_nova();
    load_at_start->fila_transmitter = fila_nova();
    load_at_start->contador_bytes = 0;

    load_at_start->vec = vetor_novo();
    load_at_start->mouse_stats.x = get_h_res() / 2;
    load_at_start->mouse_stats.y = get_v_res() / 2;
    load_at_start->multiple_bytes = 0;
    load_at_start->conta_frames_character = 1;
    load_at_start->collision_time = 0;
    load_at_start->conta_interrupts = 0;
    load_at_start->conta_interrupts1 = 0;
    load_at_start->conta_balas = 10;
    load_at_start->conta_sword_ataques = 3;
    load_at_start->score_geral = 0;
    load_at_start->score[0] = 0;
    load_at_start->score[1] = 0;
    load_at_start->score[2] = 0;
    load_at_start->score[3] = 0;
    load_at_start->lb_pressed = 0;
    load_at_start->rb_pressed = 0;
    load_at_start->rage_mode = 0;
    load_at_start->segundos_rage_mode = 0;
    load_at_start->full_rage = 0;
    load_at_start->contador_de_vida = 3;
    load_at_start->sobe = 0;
    load_at_start->state = RUN;
    load_at_start->p1.x = 100;
    load_at_start->p1.y = FLOOR_POSITION;
    load_at_start->p1.width = load_at_start->character_p1_move[0]->bitmapInfoHeader.width;
    load_at_start->p1.height = load_at_start->character_p1_move[0]->bitmapInfoHeader.height;
    load_at_start->conta_interrupts_collision = 0;
    load_at_start->conta_interrupts_rage = 0;
    load_at_start->contador_highscore = 0;
    load_at_start->player1_vivo = 1;

    load_at_start->vec_p2 = vetor_novo();
    load_at_start->multiple_bytes2 = 0;
    load_at_start->mouse_stats2.x = get_h_res() / 2;
    load_at_start->mouse_stats2.y = get_v_res() / 2;
    load_at_start->conta_frames_character_p2 = 1;
    load_at_start->collision_time2 = 0;
    load_at_start->conta_interrupts = 0;
    load_at_start->conta_interrupts_p2_1 = 0;
    load_at_start->conta_balas2 = 10;
    load_at_start->conta_sword_ataques2 = 3;
    load_at_start->score_geral2 = 0;
    load_at_start->score2[0] = 0;
    load_at_start->score2[1] = 0;
    load_at_start->score2[2] = 0;
    load_at_start->score2[3] = 0;
    load_at_start->lb_pressed2 = 0;
    load_at_start->rb_pressed2 = 0;
    load_at_start->contador_de_vida2 = 3;
    load_at_start->sobe2 = 0;
    load_at_start->state2 = RUN;
    load_at_start->p2.x = 100;
    load_at_start->p2.y = FLOOR_POSITION;
    load_at_start->p2.width = load_at_start->character_p1_move[0]->bitmapInfoHeader.width;
    load_at_start->p2.height = load_at_start->character_p1_move[0]->bitmapInfoHeader.height;
    load_at_start->conta_interrupts_collision2 = 0;
    load_at_start->high_data2.lugar_1 = 0;
    load_at_start->high_data2.lugar_2 = 0;
    load_at_start->high_data2.lugar_3 = 0;
    load_at_start->high_data2.lugar_4 = 0;
    load_at_start->contador_highscore2 = 0;
    load_at_start->conta_bytes_mouse_to_send = 0;
    load_at_start->player2_vivo = 1;
    load_at_start->rand = 0;

    load_at_start->dificuldade_multiplayer = 3;
    load_at_start->speed_background_multiplayer = 3;

    return load_at_start;
}

void game_reboot(boot_resources *start)
{

    //player1
    vetor_apaga(start->vec);
    start->vec = vetor_novo();
    start->mouse_stats.x = get_h_res() / 2;
    start->mouse_stats.y = get_v_res() / 2;
    start->multiple_bytes = 0;
    start->conta_frames_character = 1;
    start->collision_time = 0;
    start->conta_interrupts = 0;
    start->conta_interrupts1 = 0;
    start->conta_balas = 10;
    start->conta_sword_ataques = 3;
    start->score_geral = 0;
    start->score[0] = 0;
    start->score[1] = 0;
    start->score[2] = 0;
    start->score[3] = 0;
    start->lb_pressed = 0;
    start->rb_pressed = 0;
    start->rage_mode = 0;
    start->segundos_rage_mode = 0;
    start->full_rage = 0;
    start->contador_de_vida = 3;
    start->sobe = 0;
    start->state = RUN;
    start->p1.x = 100;
    start->p1.y = FLOOR_POSITION;
    start->p1.width = start->character_p1_move[0]->bitmapInfoHeader.width;
    start->p1.height = start->character_p1_move[0]->bitmapInfoHeader.height;
    start->conta_interrupts_collision = 0;
    start->conta_interrupts_rage = 0;

    if (start->menu != GAME_2PLAYERS)
    {
        start->contador_highscore = 0;
    }
    start->maquina_pronta_para_multiplayer = 0;
    start->player1_vivo = 1;

    vetor_apaga(start->vec_p2);
    start->vec_p2 = vetor_novo();
    start->multiple_bytes2 = 0;
    start->mouse_stats2.x = get_h_res() / 2;
    start->mouse_stats2.y = get_v_res() / 2;
    start->conta_frames_character_p2 = 1;
    start->collision_time2 = 0;
    start->conta_interrupts = 0;
    start->conta_interrupts_p2_1 = 0;
    start->conta_balas2 = 10;
    start->conta_sword_ataques2 = 3;
    start->score_geral2 = 0;
    start->score2[0] = 0;
    start->score2[1] = 0;
    start->score2[2] = 0;
    start->score2[3] = 0;
    start->lb_pressed2 = 0;
    start->rb_pressed2 = 0;
    start->contador_de_vida2 = 3;
    start->sobe2 = 0;
    start->state2 = RUN;
    start->p2.x = 100;
    start->p2.y = FLOOR_POSITION;
    start->p2.width = start->character_p1_move[0]->bitmapInfoHeader.width;
    start->p2.height = start->character_p1_move[0]->bitmapInfoHeader.height;
    start->conta_interrupts_collision2 = 0;
    start->high_data2.lugar_1 = 0;
    start->high_data2.lugar_2 = 0;
    start->high_data2.lugar_3 = 0;
    start->high_data2.lugar_4 = 0;
    if (start->menu != GAME_2PLAYERS)
    {
        start->contador_highscore2 = 0;
    }
    start->maquina2_pronta_para_multiplayer = 0;
    start->conta_bytes_mouse_to_send = 0;
    start->player2_vivo = 1;
    start->rand = 0;

    // GERAL
    fila_apaga(start->fila_receiver);
    fila_apaga(start->fila_transmitter);
    start->fila_receiver = fila_nova();
    start->fila_transmitter = fila_nova();
    self_clearing_receiver();
    self_clearing_transmitter();
    start->maquina_pronta_para_multiplayer = 0;
    start->maquina2_pronta_para_multiplayer = 0;
    start->contador_bytes = 0;

    return;
}

void game_end(boot_resources *start)
{
    uint8_t lixo;
    deleteBitmap(start->character_p1_move[0]);
    deleteBitmap(start->character_p1_move[1]);
    deleteBitmap(start->character_p1_move[2]);
    deleteBitmap(start->character_p1_move[3]);
    deleteBitmap(start->character_p1_move[4]);
    deleteBitmap(start->character_p1_jump[0]);
    deleteBitmap(start->character_p1_jump[1]);
    deleteBitmap(start->character_p1_jump[2]);
    deleteBitmap(start->character_p1_jump[3]);
    deleteBitmap(start->character_p2_move[0]);
    deleteBitmap(start->character_p2_move[1]);
    deleteBitmap(start->character_p2_move[2]);
    deleteBitmap(start->character_p2_move[3]);
    deleteBitmap(start->character_p2_move[4]);
    deleteBitmap(start->character_p2_jump[0]);
    deleteBitmap(start->character_p2_jump[1]);
    deleteBitmap(start->character_p2_jump[2]);
    deleteBitmap(start->character_p2_jump[3]);
    deleteBitmap(start->character_idle[0]);
    deleteBitmap(start->character_idle[1]);
    deleteBitmap(start->character_idle[2]);
    deleteBitmap(start->character_idle[3]);
    deleteBitmap(start->character_idle[4]);
    deleteBitmap(start->sword[0]);
    deleteBitmap(start->sword[1]);
    deleteBitmap(start->sword[2]);
    deleteBitmap(start->sword[3]);
    deleteBitmap(start->sword[4]);
    deleteBitmap(start->sword_p2[0]);
    deleteBitmap(start->sword_p2[1]);
    deleteBitmap(start->sword_p2[2]);
    deleteBitmap(start->sword_p2[3]);
    deleteBitmap(start->sword_p2[4]);
    deleteBitmap(start->numerical[1]);
    deleteBitmap(start->numerical[2]);
    deleteBitmap(start->numerical[3]);
    deleteBitmap(start->numerical[4]);
    deleteBitmap(start->numerical[5]);
    deleteBitmap(start->numerical[6]);
    deleteBitmap(start->numerical[7]);
    deleteBitmap(start->numerical[8]);
    deleteBitmap(start->numerical[9]);
    deleteBitmap(start->numerical[0]);
    deleteBitmap(start->ragebar[0]);
    deleteBitmap(start->ragebar[1]);
    deleteBitmap(start->ragebar[2]);
    deleteBitmap(start->ragebar[3]);
    deleteBitmap(start->ragebar[4]);
    deleteBitmap(start->background1);
    deleteBitmap(start->axe_taurus1);
    deleteBitmap(start->menu_gameover);
    deleteBitmap(start->menu_start);
    deleteBitmap(start->mouse_icon);
    deleteBitmap(start->fantasma_bitmap);
    deleteBitmap(start->fire_up);
    deleteBitmap(start->fire_down);
    deleteBitmap(start->fire_left);
    deleteBitmap(start->fire_right);
    deleteBitmap(start->fire_up_p2);
    deleteBitmap(start->fire_down_p2);
    deleteBitmap(start->fire_left_p2);
    deleteBitmap(start->fire_right_p2);
    deleteBitmap(start->main_menu);
    deleteBitmap(start->dificulty_menu);
    deleteBitmap(start->game_over_menu);
    deleteBitmap(start->highscore_menu);
    deleteBitmap(start->pause_menu);
    deleteBitmap(start->sword_ataque);
    deleteBitmap(start->infinity);
    deleteBitmap(start->pressr);
    deleteBitmap(start->life);
    deleteBitmap(start->Helldog_bitmap);
    deleteBitmap(start->slash);
    deleteBitmap(start->game_over_menu_multiplayer_lose);
    deleteBitmap(start->game_over_menu_multiplayer_win);
    deleteBitmap(start->game_over_menu_multiplayer_draw);
    deleteBitmap(start->multiplayer_menu);

    timer_unsubscribe_int();
    keyboard_unsubscribe_int();
    mouse_unsubscribe_int();
    rtc_unsubscribe_int();
    uart_unsubscribe_int();

    vetor_apaga(start->vec);
    vetor_apaga(start->vec_p2);
    fila_apaga(start->fila_transmitter);
    fila_apaga(start->fila_receiver);

    self_clearing_receiver();
    self_clearing_transmitter();

    free(start);

    keyboard_command_receive(&lixo);

    return;
}

void random_enemy(boot_resources *start)
{
    if (start->menu == GAME)
    {
        int rand_result;
        rand_result = (rand() % 3) + 1;

        if (rand_result == 1)
        {
            vetor_insere(start->vec, start, Is_Enemy, Is_Axe_taurus, -1, 1);
        }
        else if (rand_result == 2)
        {
            vetor_insere(start->vec, start, Is_Enemy, Is_Fantasma, -1, 1);
        }
        else if (rand_result == 3)
        {
            vetor_insere(start->vec, start, Is_Enemy, Is_Helldog, -1, 1);
        }
    }
    if (start->menu == GAME_2PLAYERS)
    {
        if (start->rand == 0)
        {
            vetor_insere(start->vec, start, Is_Enemy, Is_Axe_taurus, -1, 1);
            start->rand++;
        }
        else if (start->rand == 1)
        {
            vetor_insere(start->vec, start, Is_Enemy, Is_Fantasma, -1, 1);
            start->rand++;
        }
        else if (start->rand == 2)
        {
            vetor_insere(start->vec, start, Is_Enemy, Is_Helldog, -1, 1);
            start->rand++;
        }
        else if (start->rand == 3)
        {
            vetor_insere(start->vec, start, Is_Enemy, Is_Fantasma, -1, 1);
            start->rand++;
        }
        else if (start->rand == 4)
        {
            vetor_insere(start->vec, start, Is_Enemy, Is_Axe_taurus, -1, 1);
            start->rand++;
        }
        else if (start->rand == 5)
        {
            vetor_insere(start->vec, start, Is_Enemy, Is_Helldog, -1, 1);
            start->rand = 0;
        }
    }
}
void update_variables_p2(boot_resources *start)
{
    receive_char(start);

    if (start->collision_time2 == 1)
    {
        start->conta_interrupts_collision2++;
        if (start->conta_interrupts_collision2 % 180 == 0)
        {
            start->conta_interrupts_collision2 = 0;
            start->collision_time2 = 0;
        }
    }

    if (start->conta_interrupts_p2 % 180 == 0 && start->player2_vivo == 1)
    {
        if (start->conta_balas2 < 10)
        {
            start->conta_balas2++;
        }
        if (start->conta_sword_ataques2 < 3)
        {
            start->conta_sword_ataques2++;
        }
    }

    if (start->state2 == JUMPONCE)
    {

        if (start->sobe2 == 0)
        {
            start->p2.y = start->p2.y - 2 * start->dificuldade_multiplayer;
            if (start->p2.y < (FLOOR_POSITION - start->Helldog_bitmap->bitmapInfoHeader.height - 80))
            {
                start->sobe2 = 1;
            }
        }
        else if (start->sobe2 == 1)
        {
            start->conta_interrupts_p2_1++;

            if (start->conta_interrupts_p2_1 == 4)
            {
                start->conta_interrupts_p2_1 = 0;
                start->sobe2 = 2;
            }
        }
        else if (start->sobe2 == 2)
        {
            start->conta_frames_character_p2 = 8;
            if (start->conta_interrupts_p2 % 1 == 0)
            {
                check_borders_p2(start);
                start->p2.x = start->p2.x + 3;
            }
            start->p2.y = start->p2.y + 2 * start->dificuldade_multiplayer;
            if (start->p2.y >= FLOOR_POSITION)
            {
                start->sobe2 = 0;
                update_character(CHAO, start, 2);
            }
        }
    }
    if (start->conta_interrupts_p2 % 11 - start->dificuldade == 0 && start->state2 != JUMPONCE)
    {
        start->conta_frames_character_p2++;
        if (start->conta_frames_character_p2 == 5)
        {
            start->conta_frames_character_p2 = 0;
        }
        if (start->conta_frames_character_p2 == 7)
        {
            start->conta_frames_character_p2 = 5;
        }
        if (start->conta_frames_character_p2 == 14)
        {
            start->p2.width = start->character_p1_move[0]->bitmapInfoHeader.width;
            start->p2.height = start->character_p1_move[0]->bitmapInfoHeader.height;
            start->conta_frames_character_p2 = 0;
        }
    }
    if (start->conta_interrupts_p2 % 20 == 0)
    {
        update_character(NOTHING, start, 2);
    }
    return;
}

void update_variables(boot_resources *start)
{
    if (start->menu == MAIN_MENU || start->menu == DIFICULTY_MENU)
    {
        if (start->conta_interrupts % 30 == 0)
        {
            start->conta_frames_character++;
            start->conta_frames_character_p2++;
            if (start->conta_frames_character_p2 == 6)
            {
                start->conta_frames_character_p2 = 1;
            }
            if (start->conta_frames_character == 6)
            {
                start->conta_frames_character = 1;
            }
            update_menu(NOTHING1, start);
        }
        draw_background_menu(start);
    }
    else if (start->menu == GAME_OVER_MENU || start->menu == PAUSE_MENU)
    {
        draw_background_menu(start);
    }
    else if (start->menu == HIGHSCORE_MENU)
    {
        draw_background_menu(start);
    }
    else if (start->menu == GAME_OVER_MENU_2PLAYERS)
    {
        draw_background_menu(start);
    }

    if (start->menu == MULTIPLAYER_MENU)
    {
        if (start->conta_interrupts % 30 == 0)
        {
            start->conta_frames_character++;
            start->conta_frames_character_p2++;
            if (start->conta_frames_character_p2 == 6)
            {
                start->conta_frames_character_p2 = 1;
            }
            if (start->conta_frames_character == 6)
            {
                start->conta_frames_character = 1;
            }
            update_menu(NOTHING1, start);
        }

        if (start->maquina2_pronta_para_multiplayer == 1)
        {
            update_menu(PRONTO2MAQUINAS, start);
        }

        draw_background_menu(start);
    }

    else if (start->menu == GAME || start->menu == GAME_2PLAYERS)
    {
        if (start->collision_time == 1)
        {
            start->conta_interrupts_collision++;
            if (start->conta_interrupts_collision % 180 == 0)
            {
                start->conta_interrupts_collision = 0;
                start->collision_time = 0;
            }
        }
        if (start->rage_mode == 1 && start->menu == GAME)
        {
            start->conta_interrupts_rage++;
            if (start->lb_pressed == 1)
            {
                vetor_insere(start->vec, start, Is_Projectil, -2, -1, 1);
            }
            if (start->conta_interrupts_rage % 60 == 0)
            {
                start->segundos_rage_mode++;
            }
            if (start->segundos_rage_mode == 10)
            {
                start->conta_balas = 10;
                start->conta_sword_ataques = 3;
                start->segundos_rage_mode = 0;
                start->rage_mode = 0;
                start->full_rage = 0;
                start->score_geral = 0;
            }
        }
        if (start->menu == GAME)
        {
            if (start->conta_interrupts % ((6 - start->dificuldade) * 30) == 0 && start->rage_mode == 0)
            {
                random_enemy(start);
            }
            else if (start->rage_mode == 1 && start->conta_interrupts % 5 == 0)
            {
                random_enemy(start);
            }
        }
        if (start->menu == GAME_2PLAYERS)
        {
            if (start->conta_interrupts % ((5 - start->dificuldade_multiplayer) * 30) == 0 && start->rage_mode == 0)
            {
                random_enemy(start);
            }
        }

        if (start->conta_interrupts % 180 == 0 && start->player1_vivo == 1)
        {
            if (start->conta_balas < 10)
            {
                start->conta_balas++;
            }
            if (start->conta_sword_ataques < 3)
            {
                start->conta_sword_ataques++;
            }
        }

        if (start->state == JUMPONCE)
        {
            if (start->conta_interrupts % 1 == 0)
            {
                if (start->menu == GAME)
                {
                    if (start->sobe == 0)
                    {
                        if (start->dificuldade == 1)
                        {

                            start->p1.y = start->p1.y - 3 * start->dificuldade;
                        }
                        else
                        {

                            start->p1.y = start->p1.y - 2 * start->dificuldade;
                        }
                        if (start->p1.y < (FLOOR_POSITION - start->Helldog_bitmap->bitmapInfoHeader.height - 80))
                        {
                            start->sobe = 1;
                        }
                    }
                    else if (start->sobe == 1)
                    {
                        start->conta_interrupts1++;
                        if (start->dificuldade == 1)
                        {
                            if (start->conta_interrupts1 == 4)
                            {
                                start->conta_interrupts1 = 0;
                                start->sobe = 2;
                            }
                        }
                        else
                        {
                            if (start->conta_interrupts1 == 5)
                            {
                                start->conta_interrupts1 = 0;
                                start->sobe = 2;
                            }
                        }
                    }
                    else if (start->sobe == 2)
                    {
                        start->conta_frames_character = 8;
                        if (start->conta_interrupts % 1 == 0)
                        {
                            if (start->dificuldade > 1)
                            {
                                start->p1.x = start->p1.x + 3;
                            }
                            else
                            {
                           
                                start->p1.x = start->p1.x + 1;
                            }
                            check_borders_p1(start);
                        }
                        start->p1.y = start->p1.y + 2 * start->dificuldade;
                        if (start->p1.y >= FLOOR_POSITION)
                        {
                            start->sobe = 0;
                            update_character(CHAO, start, 1);
                        }
                    }
                }
                else if (start->menu == GAME_2PLAYERS)
                {

                    if (start->sobe == 0)
                    {
                        start->p1.y = start->p1.y - 2 * start->dificuldade_multiplayer;
                        if (start->p1.y < (FLOOR_POSITION - start->Helldog_bitmap->bitmapInfoHeader.height - 80))
                        {
                            start->sobe = 1;
                        }
                    }
                    else if (start->sobe == 1)
                    {
                        start->conta_interrupts1++;

                        if (start->conta_interrupts1 == 4)
                        {
                            start->conta_interrupts1 = 0;
                            start->sobe = 2;
                        }
                    }
                    else if (start->sobe == 2)
                    {
                        start->conta_frames_character = 8;
                        if (start->conta_interrupts % 1 == 0)
                        {
                            start->p1.x = start->p1.x + 1;
                        }
                        start->p1.y = start->p1.y + 2 * start->dificuldade_multiplayer;
                        if (start->p1.y >= FLOOR_POSITION)
                        {
                            start->sobe = 0;
                            update_character(CHAO, start, 1);
                        }
                    }
                }
            }
        }
        if (start->conta_interrupts % 11 - start->dificuldade == 0 && start->state != JUMPONCE)
        {
            start->conta_frames_character++;
            if (start->conta_frames_character == 5)
            {
                start->conta_frames_character = 0;
            }
            if (start->conta_frames_character == 7)
            {
                start->conta_frames_character = 5;
            }
            if (start->conta_frames_character == 14)
            {
                start->p1.width = start->character_p1_move[0]->bitmapInfoHeader.width;
                start->p1.height = start->character_p1_move[0]->bitmapInfoHeader.height;
                start->conta_frames_character = 0;
            }
        }
        draw_frame(start);

        if (start->conta_interrupts % 20 == 0)
        {
            update_character(NOTHING, start, 1);
        }
    }
    return;
}

void all_interrupts(boot_resources *start)
{

    int ipc_status, r;
    message msg;
    unsigned char *pointer;
    unsigned char *pointer1;
    unsigned char *scancode;
    //unsigned char *breakcode;
    unsigned char *mouse_byte;
    unsigned char *mouse_byte1;
    unsigned char *mouse_byte2;
    uint8_t mouse_byte_aux;

    while (start->exit == 0)
    { /* You may want to use a different condition */
        /* Get a request message. */
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
        {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status))
        { /* received notification */
            switch (_ENDPOINT_P(msg.m_source))
            {
            case HARDWARE: /* hardware interrupt notification */

                if (msg.m_notify.interrupts & start->timer_irq_set)
                {
                    start->conta_interrupts++;
                    start->conta_interrupts_p2++;
                    if (start->menu == GAME_2PLAYERS)
                    {
                        update_variables_p2(start);
                    }
                    update_variables(start);
                }

                if ((msg.m_notify.interrupts & start->kbd_irq_set))
                {
                    kbc_ih();
                    start->scancode = return_scancode();
                    kbd_processing(start);

                    pointer = (unsigned char *)malloc(sizeof(unsigned char));
                    *pointer = 'k';
                    scancode = (unsigned char *)malloc(sizeof(unsigned char));
                    *scancode = (unsigned char)start->scancode;
                    fila_push(start->fila_transmitter, pointer);
                    fila_push(start->fila_transmitter, scancode);
                    transmit_queue(start);
                }

                if ((msg.m_notify.interrupts & start->mouse_irq_set))
                {
                    mouse_ih();
                    mouse_processing(start);

                    if (start->menu == GAME_2PLAYERS)
                    {

                        mouse_byte_aux = return_mousebyte();
                        if (start->conta_bytes_mouse_to_send == 0)
                        {
                            mouse_byte = (unsigned char *)malloc(sizeof(unsigned char));
                            pointer1 = (unsigned char *)malloc(sizeof(unsigned char));
                            *pointer1 = 'm';
                            mouse_byte = (unsigned char *)malloc(sizeof(unsigned char));
                            *mouse_byte = (unsigned char)mouse_byte_aux;
                            start->conta_bytes_mouse_to_send++;
                        }
                        else if (start->conta_bytes_mouse_to_send == 1)
                        {
                            mouse_byte1 = (unsigned char *)malloc(sizeof(unsigned char));
                            *mouse_byte1 = (unsigned char)mouse_byte_aux;
                            start->conta_bytes_mouse_to_send++;
                        }
                        else if (start->conta_bytes_mouse_to_send == 2)
                        {
                            mouse_byte2 = (unsigned char *)malloc(sizeof(unsigned char));
                            *mouse_byte2 = (unsigned char)mouse_byte_aux;
                            fila_push(start->fila_transmitter, pointer1);
                            fila_push(start->fila_transmitter, mouse_byte);
                            fila_push(start->fila_transmitter, mouse_byte1);
                            fila_push(start->fila_transmitter, mouse_byte2);
                            transmit_queue(start);
                            start->conta_bytes_mouse_to_send = 0;
                        }
                    }
                }

                break;
            default:
                break;
            }
        }
        else
        {
            //fica vazio
        }
    }

    free(pointer);
    free(pointer1);
    free(scancode);
    free(mouse_byte);
    free(mouse_byte1);
    free(mouse_byte2);

    return;
}
