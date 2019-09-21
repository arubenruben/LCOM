#include <lcom/lcf.h>
#include <liblm.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include "rtc.h"
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
#include "game.h"
#include "mousedriver.h"
#include "vetor.h"
#include "statemachine.h"

void flip_display()
{
    memcpy(get_video_mem(), get_double_buffer(), (get_vram_size()));
    memset(get_double_buffer(), 0, (get_vram_size()));
    return;
}
void draw_mouse(boot_resources *start)
{
    drawBitmap(start->mouse_icon, start->mouse_stats.x, start->mouse_stats.y, ALIGN_LEFT, get_double_buffer());
    return;
}

void draw_character(boot_resources *start, int character)
{
    if (character == 1 && start->player1_vivo == 1)
    {
        switch (start->conta_frames_character)
        {
        case 0:
            start->p1.bmp = start->character_p1_move[0];
            start->p1.width = start->character_p1_move[0]->bitmapInfoHeader.width;
            start->p1.height = start->character_p1_move[0]->bitmapInfoHeader.height;
            drawBitmap(start->character_p1_move[0], start->p1.x, start->p1.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 1:
            start->p1.bmp = start->character_p1_move[1];
            start->p1.width = start->character_p1_move[1]->bitmapInfoHeader.width;
            start->p1.height = start->character_p1_move[1]->bitmapInfoHeader.height;
            drawBitmap(start->character_p1_move[1], start->p1.x, start->p1.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 2:
            start->p1.bmp = start->character_p1_move[2];
            start->p1.width = start->character_p1_move[2]->bitmapInfoHeader.width;
            start->p1.height = start->character_p1_move[2]->bitmapInfoHeader.height;
            drawBitmap(start->character_p1_move[2], start->p1.x, start->p1.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 3:
            start->p1.bmp = start->character_p1_move[3];
            start->p1.width = start->character_p1_move[3]->bitmapInfoHeader.width;
            start->p1.height = start->character_p1_move[3]->bitmapInfoHeader.height;
            drawBitmap(start->character_p1_move[3], start->p1.x, start->p1.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 4:
            start->p1.bmp = start->character_p1_move[4];
            start->p1.width = start->character_p1_move[4]->bitmapInfoHeader.width;
            start->p1.height = start->character_p1_move[4]->bitmapInfoHeader.height;
            drawBitmap(start->character_p1_move[4], start->p1.x, start->p1.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 5:
            start->p1.bmp = start->character_p1_jump[0];
            start->p1.width = start->character_p1_jump[0]->bitmapInfoHeader.width;
            start->p1.height = start->character_p1_jump[0]->bitmapInfoHeader.height;
            drawBitmap(start->character_p1_jump[0], start->p1.x, start->p1.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 6:
            start->p1.bmp = start->character_p1_jump[1];
            start->p1.width = start->character_p1_jump[1]->bitmapInfoHeader.width;
            start->p1.height = start->character_p1_jump[1]->bitmapInfoHeader.height;
            drawBitmap(start->character_p1_jump[1], start->p1.x, start->p1.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 7:
            start->p1.bmp = start->character_p1_jump[2];
            start->p1.width = start->character_p1_jump[2]->bitmapInfoHeader.width;
            start->p1.height = start->character_p1_jump[2]->bitmapInfoHeader.height;
            drawBitmap(start->character_p1_jump[2], start->p1.x, start->p1.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 8:
            start->p1.bmp = start->character_p1_jump[3];
            start->p1.width = start->character_p1_jump[3]->bitmapInfoHeader.width;
            start->p1.height = start->character_p1_jump[3]->bitmapInfoHeader.height;
            drawBitmap(start->character_p1_jump[3], start->p1.x, start->p1.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 9:
            start->p1.bmp = start->sword[0];
            start->p1.width = start->sword[0]->bitmapInfoHeader.width;
            start->p1.height = start->sword[0]->bitmapInfoHeader.height;
            drawBitmap(start->sword[0], start->p1.x, start->p1.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 10:
            start->p1.bmp = start->sword[1];
            start->p1.width = start->sword[1]->bitmapInfoHeader.width - 20;
            start->p1.height = start->sword[1]->bitmapInfoHeader.height;
            start->p1.x = start->p1.x + 1;
            drawBitmap(start->sword[1], start->p1.x, start->p1.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 11:
            start->p1.bmp = start->sword[2];
            start->p1.width = start->sword[2]->bitmapInfoHeader.width;
            start->p1.height = start->sword[2]->bitmapInfoHeader.height;
            drawBitmap(start->sword[2], start->p1.x, start->p1.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 12:
            start->p1.bmp = start->sword[3];
            start->p1.width = start->sword[3]->bitmapInfoHeader.width;
            start->p1.height = start->sword[3]->bitmapInfoHeader.height;
            drawBitmap(start->sword[3], start->p1.x, start->p1.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 13:
            start->p1.bmp = start->sword[4];
            start->p1.width = start->sword[4]->bitmapInfoHeader.width;
            start->p1.height = start->sword[4]->bitmapInfoHeader.height;
            drawBitmap(start->sword[4], start->p1.x, start->p1.y, ALIGN_LEFT, get_double_buffer());
            break;
        }
    }
    else if (character == 2 && start->player2_vivo == 1)
    {
        switch (start->conta_frames_character_p2)
        {
        case 0:
            start->p2.bmp = start->character_p2_move[0];
            start->p2.width = start->character_p2_move[0]->bitmapInfoHeader.width;
            start->p2.height = start->character_p2_move[0]->bitmapInfoHeader.height;
            drawBitmap(start->character_p2_move[0], start->p2.x, start->p2.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 1:
            start->p2.bmp = start->character_p2_move[1];
            start->p2.width = start->character_p2_move[1]->bitmapInfoHeader.width;
            start->p2.height = start->character_p2_move[1]->bitmapInfoHeader.height;
            drawBitmap(start->character_p2_move[1], start->p2.x, start->p2.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 2:
            start->p2.bmp = start->character_p2_move[2];
            start->p2.width = start->character_p2_move[2]->bitmapInfoHeader.width;
            start->p2.height = start->character_p2_move[2]->bitmapInfoHeader.height;
            drawBitmap(start->character_p2_move[2], start->p2.x, start->p2.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 3:
            start->p2.bmp = start->character_p2_move[3];
            start->p2.width = start->character_p2_move[3]->bitmapInfoHeader.width;
            start->p2.height = start->character_p2_move[3]->bitmapInfoHeader.height;
            drawBitmap(start->character_p2_move[3], start->p2.x, start->p2.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 4:
            start->p2.bmp = start->character_p2_move[4];
            start->p2.width = start->character_p2_move[4]->bitmapInfoHeader.width;
            start->p2.height = start->character_p2_move[4]->bitmapInfoHeader.height;
            drawBitmap(start->character_p2_move[4], start->p2.x, start->p2.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 5:
            start->p2.bmp = start->character_p2_jump[0];
            start->p2.width = start->character_p2_jump[0]->bitmapInfoHeader.width;
            start->p2.height = start->character_p2_jump[0]->bitmapInfoHeader.height;
            drawBitmap(start->character_p2_jump[0], start->p2.x, start->p2.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 6:
            start->p2.bmp = start->character_p2_jump[1];
            start->p2.width = start->character_p2_jump[1]->bitmapInfoHeader.width;
            start->p2.height = start->character_p2_jump[1]->bitmapInfoHeader.height;
            drawBitmap(start->character_p2_jump[1], start->p2.x, start->p2.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 7:
            start->p2.bmp = start->character_p2_jump[2];
            start->p2.width = start->character_p2_jump[2]->bitmapInfoHeader.width;
            start->p2.height = start->character_p2_jump[2]->bitmapInfoHeader.height;
            drawBitmap(start->character_p2_jump[2], start->p2.x, start->p2.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 8:
            start->p2.bmp = start->character_p2_jump[3];
            start->p2.width = start->character_p2_jump[3]->bitmapInfoHeader.width;
            start->p2.height = start->character_p2_jump[3]->bitmapInfoHeader.height;
            drawBitmap(start->character_p2_jump[3], start->p2.x, start->p2.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 9:
            start->p2.bmp = start->sword_p2[0];
            start->p2.width = start->sword_p2[0]->bitmapInfoHeader.width;
            start->p2.height = start->sword_p2[0]->bitmapInfoHeader.height;
            drawBitmap(start->sword_p2[0], start->p2.x, start->p2.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 10:
            start->p2.bmp = start->sword_p2[1];
            start->p2.width = start->sword_p2[1]->bitmapInfoHeader.width - 20;
            start->p2.height = start->sword_p2[1]->bitmapInfoHeader.height;
            start->p2.x = start->p2.x + 1;
            drawBitmap(start->sword_p2[1], start->p2.x, start->p2.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 11:
            start->p2.bmp = start->sword_p2[2];
            start->p2.width = start->sword_p2[2]->bitmapInfoHeader.width;
            start->p2.height = start->sword_p2[2]->bitmapInfoHeader.height;
            drawBitmap(start->sword_p2[2], start->p2.x, start->p2.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 12:
            start->p2.bmp = start->sword_p2[3];
            start->p2.width = start->sword_p2[3]->bitmapInfoHeader.width;
            start->p2.height = start->sword_p2[3]->bitmapInfoHeader.height;
            drawBitmap(start->sword_p2[3], start->p2.x, start->p2.y, ALIGN_LEFT, get_double_buffer());
            break;
        case 13:
            start->p2.bmp = start->sword_p2[4];
            start->p2.width = start->sword_p2[4]->bitmapInfoHeader.width;
            start->p2.height = start->sword_p2[4]->bitmapInfoHeader.height;
            drawBitmap(start->sword_p2[4], start->p2.x, start->p2.y, ALIGN_LEFT, get_double_buffer());
            break;
        }
    }

    return;
}
void print_number(int condition, boot_resources *start, int x, int y)
{
    switch (condition)
    {
    case 0:
        drawBitmap(start->numerical[0], x, y, ALIGN_LEFT, get_double_buffer());
        break;
    case 1:
        drawBitmap(start->numerical[1], x, y, ALIGN_LEFT, get_double_buffer());
        break;
    case 2:
        drawBitmap(start->numerical[2], x, y, ALIGN_LEFT, get_double_buffer());
        break;
    case 3:
        drawBitmap(start->numerical[3], x, y, ALIGN_LEFT, get_double_buffer());
        break;
    case 4:
        drawBitmap(start->numerical[4], x, y, ALIGN_LEFT, get_double_buffer());
        break;
    case 5:
        drawBitmap(start->numerical[5], x, y, ALIGN_LEFT, get_double_buffer());
        break;
    case 6:
        drawBitmap(start->numerical[6], x, y, ALIGN_LEFT, get_double_buffer());
        break;
    case 7:
        drawBitmap(start->numerical[7], x, y, ALIGN_LEFT, get_double_buffer());
        break;
    case 8:
        drawBitmap(start->numerical[8], x, y, ALIGN_LEFT, get_double_buffer());
        break;
    case 9:
        drawBitmap(start->numerical[9], x, y, ALIGN_LEFT, get_double_buffer());
        break;
    }
    return;
}

void scores_update(boot_resources *start)
{
    start->highscore_total = start->contador_highscore;

    if (start->contador_highscore > start->high_data.lugar_1)
    {
        start->high_data.lugar_4 = start->high_data.lugar_3;
        start->high_data.lugar_3 = start->high_data.lugar_2;
        start->high_data.lugar_2 = start->high_data.lugar_1;
        start->high_data.read[3] = start->high_data.read[2];
        start->high_data.read[2] = start->high_data.read[1];
        start->high_data.read[1] = start->high_data.read[0];
        start->high_data.lugar_1 = start->contador_highscore;
        rtc_read_time(&start->high_data.read[0].seconds, &start->high_data.read[0].minutes, &start->high_data.read[0].hour, &start->high_data.read[0].day_month, &start->high_data.read[0].month, &start->high_data.read[0].year);
    }
    else if (start->contador_highscore > start->high_data.lugar_2)
    {
        start->high_data.lugar_4 = start->high_data.lugar_3;
        start->high_data.lugar_3 = start->high_data.lugar_2;
        start->high_data.read[3] = start->high_data.read[2];
        start->high_data.read[2] = start->high_data.read[1];
        rtc_read_time(&start->high_data.read[1].seconds, &start->high_data.read[1].minutes, &start->high_data.read[1].hour, &start->high_data.read[1].day_month, &start->high_data.read[1].month, &start->high_data.read[1].year);
        start->high_data.lugar_2 = start->contador_highscore;
    }
    else if (start->contador_highscore > start->high_data.lugar_3)
    {
        start->high_data.lugar_4 = start->high_data.lugar_3;
        start->high_data.read[3] = start->high_data.read[2];
        rtc_read_time(&start->high_data.read[2].seconds, &start->high_data.read[2].minutes, &start->high_data.read[2].hour, &start->high_data.read[2].day_month, &start->high_data.read[2].month, &start->high_data.read[2].year);
        start->high_data.lugar_3 = start->contador_highscore;
    }
    else if (start->contador_highscore > start->high_data.lugar_4)
    {
        rtc_read_time(&start->high_data.read[3].seconds, &start->high_data.read[3].minutes, &start->high_data.read[3].hour, &start->high_data.read[3].day_month, &start->high_data.read[3].month, &start->high_data.read[3].year);
        start->high_data.lugar_4 = start->contador_highscore;
    }
    return;
}

void draw_contador_de_ataques(boot_resources *start)
{
    drawBitmap(start->fire_right, 20, 50, ALIGN_LEFT, get_double_buffer());

    if (start->rage_mode == 0)
    {
        if (start->conta_balas == 10)
        {
            drawBitmap(start->numerical[1], 55, 50, ALIGN_LEFT, get_double_buffer());
            drawBitmap(start->numerical[0], 80, 50, ALIGN_LEFT, get_double_buffer());
        }
        else if (start->conta_balas < 10)
        {
            drawBitmap(start->numerical[0], 55, 50, ALIGN_LEFT, get_double_buffer());
            print_number(start->conta_balas, start, 80, 50);
        }
        drawBitmap(start->sword_ataque, 150, 50, ALIGN_LEFT, get_double_buffer());
        drawBitmap(start->numerical[0], 225, 50, ALIGN_LEFT, get_double_buffer());
        print_number(start->conta_sword_ataques, start, 250, 50);
    }
    else if (start->rage_mode == 1)
    {
        drawBitmap(start->fire_right, 20, 50, ALIGN_LEFT, get_double_buffer());
        drawBitmap(start->sword_ataque, 150, 50, ALIGN_LEFT, get_double_buffer());
        drawBitmap(start->infinity, 80, 50, ALIGN_LEFT, get_double_buffer());
        drawBitmap(start->infinity, 225, 50, ALIGN_LEFT, get_double_buffer());
    }
    drawBitmap(start->life, 320, 50, ALIGN_LEFT, get_double_buffer());
    print_number(start->contador_de_vida, start, 350, 50);
    print_number(start->score[0], start, 700, 50);
    print_number(start->score[1], start, 675, 50);
    print_number(start->score[2], start, 650, 50);
    print_number(start->score[3], start, 625, 50);

    if (start->menu == GAME_2PLAYERS)
    {
        print_number(start->score2[0], start, 700, 524);
        print_number(start->score2[1], start, 675, 524);
        print_number(start->score2[2], start, 650, 524);
        print_number(start->score2[3], start, 625, 524);
    }
    return;
}

int check_collision_pixel_per_pixel(boot_resources *start, int p1_x1, int p1_x2, int p1_y1, int p1_y2, int enemy_x1, int enemy_x2, int enemy_y1, int enemy_y2, Bitmap *enemy_bitmap)
{
    int left;
    int right;
    int top;
    int bottom;
    int character_left_rectangle_point_x;
    int enemy_left_rectangle_point_x;
    int character_left_rectangle_point_y;
    int enemy_left_rectangle_point_y;
    unsigned char *character_start_pos;
    unsigned char *enemy_start_pos;
    if (p1_x1 > enemy_x1)
    {
        left = p1_x1;
    }
    else
    {
        left = enemy_x1;
    }
    if (p1_y1 > enemy_y1)
    {
        top = p1_y1;
    }
    else
    {
        top = enemy_y1;
    }
    if (p1_x2 > enemy_x2)
    {
        right = enemy_x2;
    }
    else
    {
        right = p1_x2;
    }
    if (p1_y2 > enemy_y2)
    {
        bottom = enemy_y2;
    }
    else
    {
        bottom = p1_y2;
    }

    character_left_rectangle_point_x = left - start->p1.x;
    character_left_rectangle_point_y = p1_y2 - bottom;
    enemy_left_rectangle_point_x = left - enemy_x1;
    enemy_left_rectangle_point_y = enemy_y2 - bottom;
    for (int i = 0; i < (bottom - top); i++)
    {
        character_start_pos = start->p1.bmp->bitmapData + character_left_rectangle_point_x * 2 + start->p1.bmp->bitmapInfoHeader.width * character_left_rectangle_point_y * 2 + (start->p1.width * i * 2);
        enemy_start_pos = enemy_bitmap->bitmapData + enemy_left_rectangle_point_x * 2 + enemy_bitmap->bitmapInfoHeader.width * enemy_left_rectangle_point_y * 2 + (enemy_bitmap->bitmapInfoHeader.width * i * 2);
        for (int j = 0; j < (right - left) * 2; j = j + 2)
        {
            if (character_start_pos[j] != PINK1 && character_start_pos[j + 1] != PINK2 && enemy_start_pos[j] != PINK1 && enemy_start_pos[j + 1] != PINK2)
            {
                if (start->collision_time == 0 && start->player1_vivo == 1)
                {
                    start->collision_time = 1;
                    start->contador_de_vida--;
                }
                if (start->contador_de_vida == 0)
                {
                    return -1;
                }
            }
        }
    }

    return 0;
}
int check_collision_pixel_per_pixel_p2(boot_resources *start, int p2_x1, int p2_x2, int p2_y1, int p2_y2, int enemy_x1, int enemy_x2, int enemy_y1, int enemy_y2, Bitmap *enemy_bitmap)
{
    int left;
    int right;
    int top;
    int bottom;
    int character_left_rectangle_point_x;
    int enemy_left_rectangle_point_x;
    int character_left_rectangle_point_y;
    int enemy_left_rectangle_point_y;
    unsigned char *character_start_pos;
    unsigned char *enemy_start_pos;
    if (p2_x1 > enemy_x1)
    {
        left = p2_x1;
    }
    else
    {
        left = enemy_x1;
    }
    if (p2_y1 > enemy_y1)
    {
        top = p2_y1;
    }
    else
    {
        top = enemy_y1;
    }
    if (p2_x2 > enemy_x2)
    {
        right = enemy_x2;
    }
    else
    {
        right = p2_x2;
    }
    if (p2_y2 > enemy_y2)
    {
        bottom = enemy_y2;
    }
    else
    {
        bottom = p2_y2;
    }
    character_left_rectangle_point_x = left - start->p2.x;
    character_left_rectangle_point_y = p2_y2 - bottom;
    enemy_left_rectangle_point_x = left - enemy_x1;
    enemy_left_rectangle_point_y = enemy_y2 - bottom;
    for (int i = 0; i < (bottom - top); i++)
    {
        character_start_pos = start->p2.bmp->bitmapData + character_left_rectangle_point_x * 2 + start->p2.bmp->bitmapInfoHeader.width * character_left_rectangle_point_y * 2 + (start->p1.width * i * 2);
        enemy_start_pos = enemy_bitmap->bitmapData + enemy_left_rectangle_point_x * 2 + enemy_bitmap->bitmapInfoHeader.width * enemy_left_rectangle_point_y * 2 + (enemy_bitmap->bitmapInfoHeader.width * i * 2);
        for (int j = 0; j < (right - left) * 2; j = j + 2)
        {
            if (character_start_pos[j] != PINK1 && character_start_pos[j + 1] != PINK2 && enemy_start_pos[j] != PINK1 && enemy_start_pos[j + 1] != PINK2)
            {
                if (start->collision_time2 == 0 && start->player2_vivo == 1)
                {
                    start->collision_time2 = 1;
                    start->contador_de_vida2--;
                }
                if (start->contador_de_vida2 == 0)
                {
                    return -1;
                }
            }
        }
    }

    return 0;
}

int check_collision_fireball_enemy(boot_resources *start, int enemy_x1, int enemy_x2, int enemy_y1, int enemy_y2)
{
    fireball *bullet;
    v_elements *retorno;

    for (int i = 0; i < start->vec->tamanho; i++)
    {
        retorno = vetor_elemento(start->vec, i);
        if (retorno == NULL)
        {
            printf("Erro vetor\n");
            return -1;
        }
        if (start->vec->n_balas == 0)
        {
            break;
        }
        if (retorno->type == Is_Projectil)
        {
            bullet = start->vec->element[i].union_type_elementos.proj->obj;
            if ((bullet->x + (bullet->width / 2)) > enemy_x1 && (bullet->x + (bullet->width / 2)) < enemy_x2 && (bullet->y + (bullet->height / 2)) < enemy_y2 && (bullet->y + (bullet->height / 2)) > enemy_y1)
            {
                vetor_remove(start->vec, i);
                return -1;
            }
        }
    }
    return 0;
}
int check_collision_fireball_p2_enemy(boot_resources *start, int enemy_x1, int enemy_x2, int enemy_y1, int enemy_y2)
{
    fireball *bullet;
    v_elements *retorno;

    for (int i = 0; i < start->vec_p2->tamanho; i++)
    {
        retorno = vetor_elemento(start->vec_p2, i);
        if (retorno == NULL)
        {
            printf("Erro vetor\n");
            return 10;
        }
        if (start->vec_p2->n_balas == 0)
        {
            break;
        }
        if (retorno->type == Is_Projectil)
        {
            bullet = start->vec_p2->element[i].union_type_elementos.proj->obj;
            if ((bullet->x + (bullet->width / 2)) > enemy_x1 && (bullet->x + (bullet->width / 2)) < enemy_x2 && (bullet->y + (bullet->height / 2)) < enemy_y2 && (bullet->y + (bullet->height / 2)) > enemy_y1)
            {
                vetor_remove(start->vec_p2, i);
                return -1;
            }
        }
    }
    return 0;
}

int check_collision_p2(boot_resources *start, int pos, int type)
{
    int p2_x1 = start->p2.x;
    int p2_x2 = start->p2.x + start->p2.width;
    int p2_y2 = start->p2.y + start->p2.height;
    int p2_y1 = start->p2.y;
    int fantasma_x1;
    int fantasma_x2;
    int fantasma_y1;
    int fantasma_y2;
    int taurus_x1;
    int taurus_y1;
    int taurus_x2;
    int taurus_y2;
    int helldog_x1;
    int helldog_y1;
    int helldog_x2;
    int helldog_y2;
    Fantasma *aux_Fantasma;
    Axe_taurus *aux_taurus;
    Helldog *aux_helldog;

    switch (type)
    {
    case Is_Fantasma:
        aux_Fantasma = start->vec->element[pos].union_type_elementos.obj->union_enemies.e2;
        if (aux_Fantasma == NULL)
        {
            printf("Erro no vetor\n");
            return -1;
        }
        fantasma_x1 = aux_Fantasma->x;
        fantasma_x2 = aux_Fantasma->x + aux_Fantasma->width;
        fantasma_y1 = aux_Fantasma->y;
        fantasma_y2 = aux_Fantasma->y + aux_Fantasma->height;
        if ((p2_x1 > fantasma_x1 && p2_x1 < fantasma_x2) || (p2_x2 > fantasma_x1 && p2_x2 < fantasma_x2) || (p2_x1 > fantasma_x1 && p2_x2 < fantasma_x2))
        {
            if ((p2_y1 < fantasma_y2 && p2_y2 > fantasma_y2) || (p2_y2 > fantasma_y1 && p2_y1 < fantasma_y1) || (p2_y1 > fantasma_y1 && p2_y2 < fantasma_y2))
            {
                if (start->conta_frames_character_p2 > 8 && start->conta_frames_character_p2 < 13)
                    return -1;
                else
                {
                    if (check_collision_pixel_per_pixel_p2(start, p2_x1, p2_x2, p2_y1, p2_y2, fantasma_x1, fantasma_x2, fantasma_y1, fantasma_y2, start->fantasma_bitmap) == -1)
                    {
                        return 2;
                    }
                }
            }
        }
        if (check_collision_fireball_p2_enemy(start, fantasma_x1, fantasma_x2, fantasma_y1, fantasma_y2) == -1)
            return -1;
        break;

    case Is_Axe_taurus:
        aux_taurus = start->vec->element[pos].union_type_elementos.obj->union_enemies.e1;
        if (aux_taurus == NULL)
        {
            printf("erro vetor\n");
            return -1;
        }
        taurus_x1 = aux_taurus->x;
        taurus_x2 = aux_taurus->x + aux_taurus->width;
        taurus_y2 = aux_taurus->y + aux_taurus->height;
        taurus_y1 = aux_taurus->y;
        if ((p2_x1 > taurus_x1 && p2_x1 < taurus_x2) || (p2_x2 > taurus_x1 && p2_x2 < taurus_x2) || (p2_x1 >= taurus_x1 && p2_x2 <= taurus_x2))
        {
            if (p2_y2 >= taurus_y1)
            {

                if (start->conta_frames_character_p2 > 8 && start->conta_frames_character_p2 < 13)
                {
                    return -1;
                }
                else
                {

                    if (check_collision_pixel_per_pixel_p2(start, p2_x1, p2_x2, p2_y1, p2_y2, taurus_x1, taurus_x2, taurus_y1, taurus_y2, start->axe_taurus1) == -1)
                    {
                        return 2;
                    }
                }
            }
        }
        if (check_collision_fireball_p2_enemy(start, taurus_x1, taurus_x2, taurus_y1, taurus_y2) == -1)
            return -1;
        break;

    case Is_Helldog:
        aux_helldog = start->vec->element[pos].union_type_elementos.obj->union_enemies.e3;
        if (aux_helldog == NULL)
        {
            printf("Erro vetor\n");
            return -1;
        }
        helldog_x1 = aux_helldog->x;
        helldog_x2 = aux_helldog->x + aux_helldog->width;
        helldog_y2 = aux_helldog->y + aux_helldog->height;
        helldog_y1 = aux_helldog->y;
        if ((p2_x1 > helldog_x1 && p2_x1 < helldog_x2) || (p2_x2 > helldog_x1 && p2_x2 < helldog_x2) || (p2_x1 <= helldog_x1 && p2_x2 >= helldog_x2))
        {
            if (p2_y2 >= helldog_y1)
            {
                if (start->conta_frames_character_p2 > 8 && start->conta_frames_character_p2 < 13)
                    return -1;
                else
                {
                    if (check_collision_pixel_per_pixel_p2(start, p2_x1, p2_x2, p2_y1, p2_y2, helldog_x1, helldog_x2, helldog_y1, helldog_y2, start->Helldog_bitmap) == -1)
                    {
                        return 2;
                    }
                }
            }
        }
        if (check_collision_fireball_p2_enemy(start, helldog_x1, helldog_x2, helldog_y1, helldog_y2) == -1)
        {
            return -1;
        }
        break;
    }
    return 0;
}

int check_collision(boot_resources *start, int pos, int type)
{
    int p1_x1 = start->p1.x;
    int p1_x2 = start->p1.x + start->p1.width;
    int p1_y2 = start->p1.y + start->p1.height;
    int p1_y1 = start->p1.y;
    int fantasma_x1;
    int fantasma_x2;
    int fantasma_y1;
    int fantasma_y2;
    int taurus_x1;
    int taurus_y1;
    int taurus_x2;
    int taurus_y2;
    int helldog_x1;
    int helldog_y1;
    int helldog_x2;
    int helldog_y2;
    Fantasma *aux_Fantasma;
    Axe_taurus *aux_taurus;
    Helldog *aux_helldog;

    switch (type)
    {
    case Is_Fantasma:
        aux_Fantasma = start->vec->element[pos].union_type_elementos.obj->union_enemies.e2;
        if (aux_Fantasma == NULL)
        {
            printf("Erro no vetor\n");
            return -1;
        }
        fantasma_x1 = aux_Fantasma->x;
        fantasma_x2 = aux_Fantasma->x + aux_Fantasma->width;
        fantasma_y1 = aux_Fantasma->y;
        fantasma_y2 = aux_Fantasma->y + aux_Fantasma->height;
        if ((p1_x1 > fantasma_x1 && p1_x1 < fantasma_x2) || (p1_x2 > fantasma_x1 && p1_x2 < fantasma_x2) || (p1_x1 > fantasma_x1 && p1_x2 < fantasma_x2))
        {
            if ((p1_y1 < fantasma_y2 && p1_y2 > fantasma_y2) || (p1_y2 > fantasma_y1 && p1_y1 < fantasma_y1) || (p1_y1 > fantasma_y1 && p1_y2 < fantasma_y2))
            {
                if (start->conta_frames_character > 8 && start->conta_frames_character < 13)
                    return -1;
                else
                {
                    if (check_collision_pixel_per_pixel(start, p1_x1, p1_x2, p1_y1, p1_y2, fantasma_x1, fantasma_x2, fantasma_y1, fantasma_y2, start->fantasma_bitmap) == -1)
                    {
                        return 2;
                    }
                }
            }
        }
        if (check_collision_fireball_enemy(start, fantasma_x1, fantasma_x2, fantasma_y1, fantasma_y2) == -1)
            return -1;
        break;

    case Is_Axe_taurus:
        aux_taurus = start->vec->element[pos].union_type_elementos.obj->union_enemies.e1;
        if (aux_taurus == NULL)
        {
            printf("erro vetor\n");
            return -1;
        }
        taurus_x1 = aux_taurus->x;
        taurus_x2 = aux_taurus->x + aux_taurus->width;
        taurus_y2 = aux_taurus->y + aux_taurus->height;
        taurus_y1 = aux_taurus->y;
        if ((p1_x1 > taurus_x1 && p1_x1 < taurus_x2) || (p1_x2 > taurus_x1 && p1_x2 < taurus_x2) || (p1_x1 >= taurus_x1 && p1_x2 <= taurus_x2))
        {
            if (p1_y2 >= taurus_y1)
            {
                if (start->conta_frames_character > 8 && start->conta_frames_character < 13)
                    return -1;
                else
                {
                    if (check_collision_pixel_per_pixel(start, p1_x1, p1_x2, p1_y1, p1_y2, taurus_x1, taurus_x2, taurus_y1, taurus_y2, start->axe_taurus1) == -1)
                    {
                        return 2;
                    }
                }
            }
        }
        if (check_collision_fireball_enemy(start, taurus_x1, taurus_x2, taurus_y1, taurus_y2) == -1)
            return -1;
        break;

    case Is_Helldog:
        aux_helldog = start->vec->element[pos].union_type_elementos.obj->union_enemies.e3;
        if (aux_helldog == NULL)
        {
            printf("Erro vetor\n");
            return -1;
        }
        helldog_x1 = aux_helldog->x;
        helldog_x2 = aux_helldog->x + aux_helldog->width;
        helldog_y2 = aux_helldog->y + aux_helldog->height;
        helldog_y1 = aux_helldog->y;
        if ((p1_x1 > helldog_x1 && p1_x1 < helldog_x2) || (p1_x2 > helldog_x1 && p1_x2 < helldog_x2) || (p1_x1 <= helldog_x1 && p1_x2 >= helldog_x2))
        {
            if (p1_y2 >= helldog_y1)
            {
                if (start->conta_frames_character > 8 && start->conta_frames_character < 13)
                    return -1;
                else
                {
                    if (check_collision_pixel_per_pixel(start, p1_x1, p1_x2, p1_y1, p1_y2, helldog_x1, helldog_x2, helldog_y1, helldog_y2, start->Helldog_bitmap) == -1)
                    {
                        return 2;
                    }
                }
            }
        }
        if (check_collision_fireball_enemy(start, helldog_x1, helldog_x2, helldog_y1, helldog_y2) == -1)
        {
            return -1;
        }
        break;
    }
    return 0;
}

void draw_enemy(boot_resources *start)
{
    int tamanho = start->vec->tamanho, i;
    v_elements *retorno;
    Axe_taurus *aux_taurus = NULL;
    Fantasma *aux_Fantasma = NULL;
    Helldog *aux_helldog = NULL;
    int type = 1000;

    for (i = 0; i < start->vec->tamanho; i++)
    {
        retorno = vetor_elemento(start->vec, i);

        if (retorno == NULL)
        {
            printf("Erro no vetor-graph\n");
            return;
        }

        switch (retorno->type)
        {
        case Is_Enemy:
            switch (retorno->union_type_elementos.obj->type)
            {
            case Is_Axe_taurus:
                aux_taurus = retorno->union_type_elementos.obj->union_enemies.e1;
                if (aux_taurus == NULL)
                {
                    printf("Erro no taurus- vetorn\n");
                    return;
                }
                if ((aux_taurus->x) < -aux_taurus->width)
                {
                    vetor_remove(start->vec, i); //tem de ter o i--, e o segredo da cena, sempre que remove, a biblioteca já atualiza os valores caso contrario iriamos salta a frente o objeto entretanto atualizado para a posicao i
                    i--;
                }
                else
                {
                    type = Is_Axe_taurus;
                    drawBitmap(aux_taurus->bmp, aux_taurus->x, aux_taurus->y, ALIGN_LEFT, get_double_buffer());
                    if (start->menu == GAME)
                    {
                        if (start->dificuldade == 1)
                        {
                            aux_taurus->x -= start->background_sprite.speed; //atualiza a posicao dos taurus
                        }
                        else
                        {
                            aux_taurus->x -= start->background_sprite.speed + 2;
                        }
                    }
                    else if (start->menu == GAME_2PLAYERS)
                    {
                        aux_taurus->x -= start->speed_background_multiplayer + 2;
                    }
                }
                break;

            case Is_Fantasma:
                aux_Fantasma = retorno->union_type_elementos.obj->union_enemies.e2;
                if (aux_Fantasma == NULL)
                {
                    printf("Erro vetor\n");
                    return;
                }
                if ((aux_Fantasma->x) < -aux_Fantasma->width)
                {
                    vetor_remove(start->vec, i);
                    i--;
                }
                else
                {
                    type = Is_Fantasma;
                    drawBitmap(aux_Fantasma->bmp, aux_Fantasma->x, aux_Fantasma->y, ALIGN_LEFT, get_double_buffer());
                    if (start->menu == GAME)
                    {
                        aux_Fantasma->x -= 2 * (start->dificuldade);
                    }
                    else if (start->menu == GAME_2PLAYERS)
                    {
                        aux_Fantasma->x -= 2 * (start->dificuldade_multiplayer);
                    }
                }
                break;

            case Is_Helldog:
                aux_helldog = retorno->union_type_elementos.obj->union_enemies.e3;
                if (aux_helldog == NULL)
                {
                    printf("Erro vetor\n");
                    return;
                }
                if ((aux_helldog->x) < -aux_helldog->width)
                {
                    vetor_remove(start->vec, i);
                    i--;
                }
                else
                {
                    type = Is_Helldog;
                    drawBitmap(aux_helldog->bmp, aux_helldog->x, aux_helldog->y, ALIGN_LEFT, get_double_buffer());
                    if (start->menu == GAME)
                    {
                        if (start->dificuldade == 1)
                        {
                            aux_helldog->x -= start->background_sprite.speed;
                        }
                        else
                        {
                            aux_helldog->x -= start->background_sprite.speed + 2;
                        }
                    }
                    else if (start->menu == GAME_2PLAYERS)
                    {
                        aux_helldog->x -= start->speed_background_multiplayer + 2;
                    }
                }
                break;
            }

            // PLAYER1

            int retorno = check_collision(start, i, type);
            if (retorno == -1)
            {
                start->score[0]++;
                start->contador_highscore++;
                if (start->rage_mode == 0 && start->menu == GAME)
                {
                    start->score_geral++;
                }
                if (start->score[0] == 10)
                {
                    start->score[0] = 0;
                    start->score[1]++;
                }
                if (start->score[1] == 10)
                {
                    start->score[1] = 0;
                    start->score[2]++;
                }
                if (start->score[2] == 10)
                {
                    start->score[2] = 0;
                    start->score[3]++;
                }
                if (start->score[3] == 10)
                {
                    start->score[3] = 0;
                }
                vetor_remove(start->vec, i);
                i--;
            }

            else if (retorno == 2)
            {
                if (start->menu == GAME)
                {
                    update_menu(COLISION, start);
                }
                else if (start->menu == GAME_2PLAYERS)
                {
                    start->player1_vivo = 0;
                    start->conta_balas = 0;
                    start->conta_sword_ataques = 0;
                }
            }

            // PLAYER 2

            if (start->menu == GAME_2PLAYERS && retorno != -1)
            {

                int retorno1 = check_collision_p2(start, i, type);

                if (retorno1 == -1)
                {
                    start->score2[0]++;
                    start->contador_highscore2++;

                    if (start->score2[0] == 10)
                    {
                        start->score2[0] = 0;
                        start->score2[1]++;
                    }
                    if (start->score2[1] == 10)
                    {
                        start->score2[1] = 0;
                        start->score2[2]++;
                    }
                    if (start->score2[2] == 10)
                    {
                        start->score2[2] = 0;
                        start->score2[3]++;
                    }
                    if (start->score2[3] == 10)
                    {
                        start->score2[3] = 0;
                    }
                    vetor_remove(start->vec, i);
                    i--;
                }

                else if (retorno1 == 2)
                {
                    start->player2_vivo = 0;
                    start->conta_balas2 = 0;
                    start->conta_sword_ataques2 = 0;
                }
            }
            if (start->player1_vivo == 0 && start->player2_vivo == 0)
            {
                update_menu(BOTHDEAD, start);
            }
            break;
        case Is_Projectil:
            break;
        }
    }
    tamanho = start->vec->tamanho;
    return;
}

void draw_projetil(boot_resources *start)
{
    int i;
    v_elements *retorno;
    fireball *aux;

    for (i = 0; i < start->vec->tamanho; i++)
    {
        retorno = vetor_elemento(start->vec, i);

        if (retorno == NULL)
        {
            printf("Tive um retorno NULL linha 659\n");
            return;
        }

        if (retorno->type == Is_Projectil)
        {
            aux = retorno->union_type_elementos.proj->obj;

            if (aux == NULL)
            {
                printf("aux esta a dar nulo\n");
            }

            if ((aux->x) < -50 || (aux->x) > 805 || (aux->y) > 570 || (aux->y) < 42)
            {
                vetor_remove(start->vec, i); //tem de ter o i--, e o segredo da cena, sempre que remove, a biblioteca já atualiza os valores caso contrario iriamos salta a frente o objeto entretanto atualizado para a posicao i
                i--;
            }
            else
            {
                drawBitmap(aux->bmp, aux->x, aux->y, ALIGN_LEFT, get_double_buffer());
                aux->x += aux->speedx;
                aux->y -= aux->speedy;
            }
        }
    }

    if (start->menu == GAME_2PLAYERS)
    {
        for (i = 0; i < start->vec_p2->tamanho; i++)
        {
            retorno = vetor_elemento(start->vec_p2, i);

            if (retorno == NULL)
            {
                printf("Erro na linha 682\n");
                return;
            }

            if (retorno->type == Is_Projectil)
            {
                aux = retorno->union_type_elementos.proj->obj;
                if (aux == NULL)
                {
                    printf("No aux houve um NULL");
                    return;
                }

                if ((aux->x) < -50 || (aux->x) > 805 || (aux->y) > 570 || (aux->y) < 42)
                {
                    vetor_remove(start->vec_p2, i); //tem de ter o i--, e o segredo da cena, sempre que remove, a biblioteca já atualiza os valores caso contrario iriamos salta a frente o objeto entretanto atualizado para a posicao i
                    i--;
                }
                else
                {
                    drawBitmap(aux->bmp, aux->x, aux->y, ALIGN_LEFT, get_double_buffer());
                    aux->x += aux->speedx;
                    aux->y -= aux->speedy;
                }
            }
        }
    }
    return;
}

void draw_background(boot_resources *start)
{
    unsigned char *temp = start->background_sprite.bmp->bitmapData;
    const int half_width = (start->background_sprite.width / 2);
    const int half_width_pixel = half_width * (get_bits_per_pixel() / 8);
    if (start->menu == GAME)
    {
        start->background_sprite.x = (start->background_sprite.speed + start->background_sprite.x) % half_width;
    }
    else if (start->menu == GAME_2PLAYERS)
    {
        start->background_sprite.x = (start->speed_background_multiplayer + start->background_sprite.x) % half_width;
    }
    temp += start->background_sprite.x * (get_bits_per_pixel() / 8);

    for (int i = 0; i < start->background_sprite.height; i++)
    {
        memcpy(get_double_buffer() + i * half_width_pixel, temp + 2 * i * half_width_pixel, half_width_pixel);
    }
    return;
}

void draw_background_menu(boot_resources *start)
{
    if (start->menu == MAIN_MENU || start->menu == DIFICULTY_MENU || start->menu == MULTIPLAYER_MENU)
    {
        if (start->menu == MAIN_MENU)
        {
            drawBitmap(start->main_menu, 0, 0, ALIGN_LEFT, get_double_buffer());
        }
        else if (start->menu == DIFICULTY_MENU)
        {
            drawBitmap(start->dificulty_menu, 0, 0, ALIGN_LEFT, get_double_buffer());
        }
        else if (start->menu == MULTIPLAYER_MENU)
        {
            drawBitmap(start->multiplayer_menu, 0, 0, ALIGN_LEFT, get_double_buffer());
        }
        if (start->conta_frames_character == 1)
        {
            drawBitmap(start->character_idle[0], start->p1.x, FLOOR_POSITION, ALIGN_LEFT, get_double_buffer());
        }
        if (start->conta_frames_character == 2)
        {
            drawBitmap(start->character_idle[1], start->p1.x, FLOOR_POSITION, ALIGN_LEFT, get_double_buffer());
        }
        if (start->conta_frames_character == 3)
        {
            drawBitmap(start->character_idle[2], start->p1.x, FLOOR_POSITION, ALIGN_LEFT, get_double_buffer());
        }
        if (start->conta_frames_character == 4)
        {
            drawBitmap(start->character_idle[3], start->p1.x, FLOOR_POSITION, ALIGN_LEFT, get_double_buffer());
        }
        if (start->conta_frames_character == 5)
        {
            drawBitmap(start->character_idle[4], start->p1.x, FLOOR_POSITION, ALIGN_LEFT, get_double_buffer());
        }
    }
    else if (start->menu == HIGHSCORE_MENU)
    {
        int i;
        int vec_high[4];
        int aux, mem;
        vec_high[0] = start->high_data.lugar_1;
        vec_high[1] = start->high_data.lugar_2;
        vec_high[2] = start->high_data.lugar_3;
        vec_high[3] = start->high_data.lugar_4;
        drawBitmap(start->highscore_menu, 0, 0, ALIGN_LEFT, get_double_buffer());

        for (i = 0; i < 4; i++)
        {
            mem = vec_high[i];
            if (vec_high[i] > start->highscore_total)
            {
                start->score[3] = mem / 1000;
                aux = start->score[3] * 1000;
                mem = mem - aux;
                start->score[2] = mem / 100;
                aux = start->score[2] * 100;
                mem = mem - aux;
                start->score[1] = mem / 10;
                aux = start->score[1] * 10;
                mem = mem - aux;
                start->score[0] = mem;
            }
            else
            {
                start->score[3] = vec_high[i] / 1000;
                aux = start->score[3] * 1000;
                vec_high[i] = vec_high[i] - aux;
                start->score[2] = vec_high[i] / 100;
                aux = start->score[2] * 100;
                vec_high[i] = vec_high[i] - aux;
                start->score[1] = vec_high[i] / 10;
                aux = start->score[1] * 10;
                vec_high[i] = vec_high[i] - aux;
                start->score[0] = vec_high[i];
                vec_high[i] = start->highscore_total;
            }

            print_number(start->score[0], start, 357, 238 + i * 45);
            print_number(start->score[1], start, 332, 238 + i * 45);
            print_number(start->score[2], start, 307, 238 + i * 45);
            print_number(start->score[3], start, 282, 238 + i * 45);
            mem = start->high_data.read[i].month;
            start->month2 = ((start->high_data.read[i].month) & 0xF0) >> 4;
            start->month1 = (start->high_data.read[i].month & 0x0F);

            start->year2 = ((start->high_data.read[i].year) & 0xF0) >> 4;
            start->year1 = (start->high_data.read[i].year & 0x0F);

            start->high_data.read[i].month = mem;
            mem = start->high_data.read[i].day_month;
            start->day2 = ((start->high_data.read[i].day_month & 0xF0) >> 4);
            start->day1 = (start->high_data.read[i].day_month & 0x0F);
            start->high_data.read[i].day_month = mem;
            print_number(start->day2, start, 400, 238 + i * 45);
            print_number(start->day1, start, 420, 238 + i * 45);
            drawBitmap(start->slash, 432, 240 + i * 45, ALIGN_LEFT, get_double_buffer());
            print_number(start->month2, start, 445, 238 + i * 45);
            print_number(start->month1, start, 462, 238 + i * 45);

            drawBitmap(start->slash, 476, 240 + i * 45, ALIGN_LEFT, get_double_buffer());
            print_number(start->year2, start, 492, 238 + i * 45);
            print_number(start->year1, start, 509, 238 + i * 45);
        }
    }
    else if (start->menu == GAME_OVER_MENU)
    {
        drawBitmap(start->game_over_menu, 0, 0, ALIGN_LEFT, get_double_buffer());
    }
    else if (start->menu == PAUSE_MENU)
    {
        drawBitmap(start->pause_menu, 0, 0, ALIGN_LEFT, get_double_buffer());
    }
    else if (start->menu == GAME_OVER_MENU_2PLAYERS)
    {
        if (start->contador_highscore > start->contador_highscore2)
        {
            drawBitmap(start->game_over_menu_multiplayer_win, 0, 0, ALIGN_LEFT, get_double_buffer());
        }
        else if (start->contador_highscore2 > start->contador_highscore)
        {
            drawBitmap(start->game_over_menu_multiplayer_lose, 0, 0, ALIGN_LEFT, get_double_buffer());
        }
        else if (start->contador_highscore2 == start->contador_highscore)
        {
            drawBitmap(start->game_over_menu_multiplayer_draw, 0, 0, ALIGN_LEFT, get_double_buffer());
        }
    }
    draw_mouse(start);
    flip_display();
}

void draw_rage_bar(boot_resources *start)
{
    if (start->score_geral >= 0 && start->score_geral < 10)
    {
        drawBitmap(start->ragebar[0], 440, 55, ALIGN_LEFT, get_double_buffer());
    }
    else if (start->score_geral >= 10 && start->score_geral < 15)
    {
        drawBitmap(start->ragebar[1], 440, 55, ALIGN_LEFT, get_double_buffer());
    }
    else if (start->score_geral >= 15 && start->score_geral < 20)
    {
        drawBitmap(start->ragebar[2], 440, 55, ALIGN_LEFT, get_double_buffer());
    }
    else if (start->score_geral >= 20 && start->score_geral < 25)
    {
        drawBitmap(start->ragebar[3], 440, 55, ALIGN_LEFT, get_double_buffer());
    }
    else if (start->score_geral >= 25)
    {
        start->full_rage = 1;
        drawBitmap(start->ragebar[4], 440, 55, ALIGN_LEFT, get_double_buffer());
        drawBitmap(start->pressr, 400, 60 + start->ragebar[4]->bitmapInfoHeader.height, ALIGN_LEFT, get_double_buffer());
    }
    return;
}

void draw_frame(boot_resources *start)
{
    draw_background(start);
    draw_enemy(start);

    if (start->menu == GAME_2PLAYERS)
    {
        if (start->collision_time2 == 0)
        {
            draw_character(start, 2);
        }
        else if (start->collision_time2 == 1 && start->conta_interrupts_collision2 % 2 == 0)
        {
            draw_character(start, 2);
        }
    }

    if (start->collision_time == 0)
    {
        draw_character(start, 1);
    }
    else if (start->collision_time == 1 && start->conta_interrupts_collision % 2 == 0)
    {
        draw_character(start, 1);
    }

    draw_projetil(start);
    draw_contador_de_ataques(start);

    if (start->menu == GAME)
    {
        draw_rage_bar(start);
    }

    draw_mouse(start);
    flip_display();
    return;
}
