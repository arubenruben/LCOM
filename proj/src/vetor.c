#include <lcom/lcf.h>
#include <stdio.h>
#include "game.h"
#include "vetor.h"
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
#include "statemachine.h"
#include "vbe1.h"
#include "math.h"

vector *vetor_novo()
{
    vector *vec;
    /* aloca memoria para a estrutura vector */
    vec = (vector *)malloc(sizeof(vector));
    if (vec == NULL)
        return NULL;
    vec->tamanho = 0;
    vec->capacidade = 0;
    vec->n_balas = 0;
    vec->n_enemies = 0;
    vec->element = NULL;
    return vec;
}

void vetor_apaga(vector *vec)
{
    int i;
    if (vec == NULL)
        return;
    /* liberta memoria de cada string */
    for (i = 0; i < vec->tamanho; i++)
    {
        switch (vec->element[i].type)
        {
        case Is_Projectil:
            free(vec->element[i].union_type_elementos.proj->obj);
            //free(vec->element[i].union_type_elementos.proj);
            break;

        case Is_Enemy:

            switch (vec->element[i].union_type_elementos.obj->type)
            {
            case Is_Axe_taurus:
                free(vec->element[i].union_type_elementos.obj->union_enemies.e1);
                break;

            case Is_Fantasma:
                free(vec->element[i].union_type_elementos.obj->union_enemies.e2);
                break;

            case Is_Helldog:
                free(vec->element[i].union_type_elementos.obj->union_enemies.e3);
                break;
            }
            //free(vec->element[i].union_type_elementos.obj);
            break;
        }
    }
    /* liberta memoria dos apontares para as strings */
    free(vec->element);
    /* liberta memoria da estrutura vector */
    free(vec);
    //check
}

int vetor_remove(vector *vec, int pos)
{

    int i;

    switch (vec->element[pos].type)
    {
    case Is_Projectil:
        free(vec->element[pos].union_type_elementos.proj->obj);
        free(vec->element[pos].union_type_elementos.proj);
        vec->n_balas--;
        break;

    case Is_Enemy:
        vec->n_enemies--;
        switch (vec->element[pos].union_type_elementos.obj->type)
        {
        case Is_Axe_taurus:
            free(vec->element[pos].union_type_elementos.obj->union_enemies.e1);
            break;
        case Is_Fantasma:
            free(vec->element[pos].union_type_elementos.obj->union_enemies.e2);
            break;
        case Is_Helldog:
            free(vec->element[pos].union_type_elementos.obj->union_enemies.e3);
            break;
        }
        free(vec->element[pos].union_type_elementos.obj);
        break;
    }

    for (i = pos + 1; i < vec->tamanho; i++)
    {
        vec->element[i - 1] = vec->element[i];
    }
    vec->tamanho--;
    return 0;
}

int vetor_tamanho(vector *vec)
{
    if (vec == NULL)
        return -1;

    return vec->tamanho;
    //check
}

int vetor_insere(vector *vec, struct boot_resources *start, enum Element_type type, enum Enemy_type ene_type, int pos, int player)
{
    int i;
    double delta_x, delta_y;

    if (vec == NULL || pos < -1 || pos > vec->tamanho)
        return -1;
    /* aumenta elementos_projectil do vetor_projectil se capacidade nao for suficiente */

    if (vec->tamanho == vec->capacidade)
    {
        if (vec->capacidade == 0)
            vec->capacidade = 1;
        else
            vec->capacidade *= 2;

        vec->element = (v_elements *)realloc(vec->element, vec->capacidade * sizeof(v_elements));

        if (vec->element == NULL)
        {
            printf("Erro no malloc\n");
            return -1;
        }
    }

    /* se pos=-1 insere no fim do vetor_projectil */

    if (pos == -1)
        pos = vec->tamanho;
    /* copia todos os elementos_projectil a partir da posicao pos ate' ao fim do vetor_projectil para pos+1 */

    for (i = vec->tamanho - 1; i >= pos; i--)
    {
        vec->element[i + 1] = vec->element[i];
    }

    switch (type)
    {

    case Is_Projectil:

        vec->n_balas++;
        vec->element[pos].type = Is_Projectil;
        vec->element[pos].union_type_elementos.proj = (projectil *)malloc(sizeof(projectil));
        if (vec->element[pos].union_type_elementos.proj == NULL)
        {
            printf("Erro no malloc\n");
            return -1;
        }

        vec->element[pos].union_type_elementos.proj->obj = (fireball *)calloc(1, sizeof(fireball));

        if (vec->element[pos].union_type_elementos.proj->obj == NULL)
        {
            printf("Erro no malloc\n");

            return -1;
        }

        if (player == 1)
        {
            if (start->conta_frames_character == 5)
            {
                vec->element[pos].union_type_elementos.proj->obj->x = start->p1.x + 70;
                vec->element[pos].union_type_elementos.proj->obj->y = start->p1.y + 135;
            }

            else if (start->conta_frames_character == 6)
            {
                vec->element[pos].union_type_elementos.proj->obj->x = start->p1.x + 60;
                vec->element[pos].union_type_elementos.proj->obj->y = start->p1.y + 135;
            }

            else
            {
                vec->element[pos].union_type_elementos.proj->obj->x = start->p1.x + 50;
                vec->element[pos].union_type_elementos.proj->obj->y = start->p1.y + 50;
            }

            if (start->mouse_stats.x > start->p1.x + 50)
            {
                vec->element[pos].union_type_elementos.proj->obj->bmp = start->fire_right;
                vec->element[pos].union_type_elementos.proj->obj->width = start->fire_right->bitmapInfoHeader.width;
                vec->element[pos].union_type_elementos.proj->obj->height = start->fire_right->bitmapInfoHeader.height;
            }

            else if (start->mouse_stats.x < start->p1.x - 50)
            {
                vec->element[pos].union_type_elementos.proj->obj->bmp = start->fire_left;
                vec->element[pos].union_type_elementos.proj->obj->width = start->fire_left->bitmapInfoHeader.width;
                vec->element[pos].union_type_elementos.proj->obj->height = start->fire_left->bitmapInfoHeader.height;
            }

            else if (start->mouse_stats.x > start->p1.x - 50 && start->mouse_stats.x < start->p1.x + 50 && start->mouse_stats.y < start->p1.y)
            {
                vec->element[pos].union_type_elementos.proj->obj->bmp = start->fire_up;
                vec->element[pos].union_type_elementos.proj->obj->width = start->fire_up->bitmapInfoHeader.width;
                vec->element[pos].union_type_elementos.proj->obj->height = start->fire_up->bitmapInfoHeader.height;
            }

            else if (start->mouse_stats.x > start->p1.x - 50 && start->mouse_stats.x < start->p1.x + 50 && start->mouse_stats.y > start->p1.y)
            {
                vec->element[pos].union_type_elementos.proj->obj->bmp = start->fire_down;
                vec->element[pos].union_type_elementos.proj->obj->width = start->fire_down->bitmapInfoHeader.width;
                vec->element[pos].union_type_elementos.proj->obj->height = start->fire_down->bitmapInfoHeader.height;
            }
            delta_x = start->mouse_stats.x - vec->element[pos].union_type_elementos.proj->obj->x;
            delta_y = -1 * (start->mouse_stats.y - vec->element[pos].union_type_elementos.proj->obj->y);

            double hipotenusa, seno, cosseno;
            hipotenusa = sqrt(delta_x * delta_x + delta_y * delta_y);
            seno = delta_y / hipotenusa;
            cosseno = delta_x / hipotenusa;
            vec->element[pos].union_type_elementos.proj->obj->speedx = 15 * cosseno;
            vec->element[pos].union_type_elementos.proj->obj->speedy = 15 * seno;
        }

        else if (player == 2)
        {
            if (start->conta_frames_character_p2 == 5)
            {
                vec->element[pos].union_type_elementos.proj->obj->x = start->p2.x + 70;
                vec->element[pos].union_type_elementos.proj->obj->y = start->p2.y + 135;
            }
            else if (start->conta_frames_character_p2 == 6)
            {
                vec->element[pos].union_type_elementos.proj->obj->x = start->p2.x + 60;
                vec->element[pos].union_type_elementos.proj->obj->y = start->p2.y + 135;
            }
            else
            {
                vec->element[pos].union_type_elementos.proj->obj->x = start->p2.x + 50;
                vec->element[pos].union_type_elementos.proj->obj->y = start->p2.y + 50;
            }

            if (start->mouse_stats2.x > start->p2.x + 50)
            {
                vec->element[pos].union_type_elementos.proj->obj->bmp = start->fire_right_p2;
                vec->element[pos].union_type_elementos.proj->obj->width = start->fire_right_p2->bitmapInfoHeader.width;
                vec->element[pos].union_type_elementos.proj->obj->height = start->fire_right_p2->bitmapInfoHeader.height;
            }

            else if (start->mouse_stats2.x < start->p2.x - 50)
            {
                vec->element[pos].union_type_elementos.proj->obj->bmp = start->fire_left_p2;
                vec->element[pos].union_type_elementos.proj->obj->width = start->fire_left_p2->bitmapInfoHeader.width;
                vec->element[pos].union_type_elementos.proj->obj->height = start->fire_left_p2->bitmapInfoHeader.height;
            }

            else if (start->mouse_stats2.x > start->p2.x - 50 && start->mouse_stats2.x < start->p2.x + 50 && start->mouse_stats2.y < start->p2.y)
            {
                vec->element[pos].union_type_elementos.proj->obj->bmp = start->fire_up_p2;
                vec->element[pos].union_type_elementos.proj->obj->width = start->fire_up_p2->bitmapInfoHeader.width;
                vec->element[pos].union_type_elementos.proj->obj->height = start->fire_up_p2->bitmapInfoHeader.height;
            }

            else if (start->mouse_stats2.x > start->p2.x - 50 && start->mouse_stats2.x < start->p2.x + 50 && start->mouse_stats2.y > start->p2.y)
            {
                vec->element[pos].union_type_elementos.proj->obj->bmp = start->fire_down_p2;
                vec->element[pos].union_type_elementos.proj->obj->width = start->fire_down_p2->bitmapInfoHeader.width;
                vec->element[pos].union_type_elementos.proj->obj->height = start->fire_down_p2->bitmapInfoHeader.height;
            }

            delta_x = start->mouse_stats2.x - vec->element[pos].union_type_elementos.proj->obj->x;
            delta_y = -1 * (start->mouse_stats2.y - vec->element[pos].union_type_elementos.proj->obj->y);

            double hipotenusa, seno, cosseno;
            hipotenusa = sqrt(delta_x * delta_x + delta_y * delta_y);
            seno = delta_y / hipotenusa;
            cosseno = delta_x / hipotenusa;
            vec->element[pos].union_type_elementos.proj->obj->speedx = 15 * cosseno;
            vec->element[pos].union_type_elementos.proj->obj->speedy = 15 * seno;
        }
        break;

    case Is_Enemy:

        vec->element[pos].type = Is_Enemy;
        vec->n_enemies++;
        vec->element[pos].union_type_elementos.obj = (enemies *)malloc(sizeof(enemies));
        if (vec->element[pos].union_type_elementos.obj == NULL)
        {
            printf("Erro no malloc\n");
            return -1;
        }
        switch (ene_type)
        {
        case Is_Axe_taurus:
            vec->element[pos].union_type_elementos.obj->type = Is_Axe_taurus;
            vec->element[pos].union_type_elementos.obj->union_enemies.e1 = (Axe_taurus *)calloc(1, sizeof(Axe_taurus));
            if (vec->element[pos].union_type_elementos.obj->union_enemies.e1 == NULL)
            {
                printf("Erro no malloc");
                return 0;
            }
            vec->element[pos].union_type_elementos.obj->union_enemies.e1->bmp = start->axe_taurus1;
            vec->element[pos].union_type_elementos.obj->union_enemies.e1->width = start->axe_taurus1->bitmapInfoHeader.width;
            vec->element[pos].union_type_elementos.obj->union_enemies.e1->height = start->axe_taurus1->bitmapInfoHeader.height;
            vec->element[pos].union_type_elementos.obj->union_enemies.e1->x = get_h_res();
            vec->element[pos].union_type_elementos.obj->union_enemies.e1->y = FLOOR_POSITION;
            break;

        case Is_Fantasma:

            vec->element[pos].union_type_elementos.obj->type = Is_Fantasma;
            vec->element[pos].union_type_elementos.obj->union_enemies.e2 = (Fantasma *)calloc(1, sizeof(Fantasma));
            if (vec->element[pos].union_type_elementos.obj->union_enemies.e2 == NULL)
            {
                printf("Erro no malloc");
                return -1;
            }
            vec->element[pos].union_type_elementos.obj->union_enemies.e2->bmp = start->fantasma_bitmap;
            vec->element[pos].union_type_elementos.obj->union_enemies.e2->width = start->fantasma_bitmap->bitmapInfoHeader.width;
            vec->element[pos].union_type_elementos.obj->union_enemies.e2->height = start->fantasma_bitmap->bitmapInfoHeader.height;
            vec->element[pos].union_type_elementos.obj->union_enemies.e2->x = get_h_res();
            vec->element[pos].union_type_elementos.obj->union_enemies.e2->y = FLOOR_POSITION - 220;
            break;

        case Is_Helldog:

            vec->element[pos].union_type_elementos.obj->type = Is_Helldog;
            vec->element[pos].union_type_elementos.obj->union_enemies.e3 = (Helldog *)calloc(1, sizeof(Helldog));
            if (vec->element[pos].union_type_elementos.obj->union_enemies.e3 == NULL)
            {
                printf("Erro no malloc");
                return -1;
            }
            vec->element[pos].union_type_elementos.obj->union_enemies.e3->bmp = start->Helldog_bitmap;
            vec->element[pos].union_type_elementos.obj->union_enemies.e3->width = start->Helldog_bitmap->bitmapInfoHeader.width;
            vec->element[pos].union_type_elementos.obj->union_enemies.e3->height = start->Helldog_bitmap->bitmapInfoHeader.height;
            vec->element[pos].union_type_elementos.obj->union_enemies.e3->x = get_h_res();
            vec->element[pos].union_type_elementos.obj->union_enemies.e3->y = FLOOR_POSITION;
            break;
        }
        break;
    }
    vec->tamanho++;
    return pos;
}

v_elements *vetor_elemento(vector *vec, int indice)
{
    if (vec == NULL || indice > vec->tamanho)
    {
        printf("No vetor elemento retornei null\n");
        return NULL;
    }
    else
    {
        return &vec->element[indice];
    }
    return NULL;
}

int FileExits(const char *filename)
{

    FILE *file = fopen(filename, "r");
    if (file)
    {
        fclose(file);
        return 1;
    }
    return 0;
}
