#pragma once

/** @defgroup game game
 * @{
 * Functions for manipulating queues
 */

#include "bitmap.h"
#include "mousedriver.h"
#include "statemachine.h"
#include "vetor.h"
#include "fila.h"

#define FLOOR_POSITION 360


typedef struct Character_run
{
    Bitmap *bmp;
    int x;
    int y;
    int width;  ///< specifies width in pixels
    int height; ///< specifies height in pixels
} Character_run;

typedef struct Axe_taurus
{
    Bitmap *bmp;
    int x;
    int y;
    int width;  ///< specifies width in pixels
    int height; ///< specifies height in pixels
} Axe_taurus;

typedef struct Fantasma
{
    Bitmap *bmp;
    int y;
    int width;  ///< specifies width in pixels
    int height; ///< specifies height in pixels
    int x;
    int speed;
} Fantasma;

typedef struct Helldog
{
    Bitmap *bmp;
    int y;
    int width;  ///< specifies width in pixels
    int height; ///< specifies height in pixels
    int x;
} Helldog;

typedef struct background
{
    Bitmap *bmp;
    int x;
    int speed;
    int width;
    int height;
} background;

typedef struct fireball
{
    Bitmap *bmp;
    int x;
    int y;
    int speedx;
    int speedy;
    int width;
    int height;
    double delta_x;
    double delta_y;
    int b;
} fireball;

typedef struct
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hour;
    uint8_t day_month;
    uint8_t year;
    uint8_t month;
    char *day_week;
} rtc_read;

typedef struct
{
    int lugar_1;
    int lugar_2;
    int lugar_3;
    int lugar_4;
    rtc_read read[4];
} highscore;

//Struct that contains all the variables, bitmaps, strucs and other usefull elements needed to run the game
typedef struct boot_resources
{
    int timer_irq_set, kbd_irq_set, mouse_irq_set, uart_irq_set; // Needed for interrupts cycles
    int dificuldade;                                             // dificulty of the game

    // sequence of bitmaps necessary to run the game
    Bitmap *character_p1_move[5]; // bitmaps necessary for the character movement
    Bitmap *character_p2_move[5];
    Bitmap *character_p1_jump[4]; // bitmaps necessary for the caracther jump and fly
    Bitmap *character_p2_jump[4];
    Bitmap *menu_gameover;
    Bitmap *background1;
    Bitmap *menu_start;
    Bitmap *mouse_icon;
    Bitmap *character_idle[5];
    Bitmap *fire_left; //bitmap necessary for the fireball projectile
    Bitmap *sword[5];  // bitmaps necessary for the sword atack
    Bitmap *sword_p2[5];
    Bitmap *main_menu; // main menu bitmap
    Bitmap *dificulty_menu;
    Bitmap *game_over_menu;
    Bitmap *highscore_menu;
    Bitmap *pause_menu;
    Bitmap *sword_ataque;
    Bitmap *ragebar[5]; // bitmaps for the ragebar that is displayed aboved the character in game
    Bitmap *pressr;     // bitmap for the message that displays after the rage bar is full
    Bitmap *life;
    Bitmap *numerical[10];   //bitmaps for each number from 0 to 9 acorddingly
    Bitmap *slash;           // bitmap for the slah, used for the date in the highscore menu
    Bitmap *fantasma_bitmap; // bitmap for ghost enemy
    Bitmap *axe_taurus1;     // bitmap for taurus enemy
    Bitmap *Helldog_bitmap;  // bitmap for the helldog Knight
    Bitmap *infinity;        // bitmap for the infinity symbol used in the rage mode
    Bitmap *fire_right;
    Bitmap *fire_up;
    Bitmap *fire_down;
    Bitmap *fire_right_p2;
    Bitmap *fire_left_p2;
    Bitmap *fire_down_p2;
    Bitmap *fire_up_p2;
    Bitmap *multiplayer_menu;
    Bitmap *game_over_menu_multiplayer_win;
    Bitmap *game_over_menu_multiplayer_lose;
    Bitmap *game_over_menu_multiplayer_draw;

    //geral ao jgo

    fila *fila_transmitter;
    fila *fila_receiver;
    int contador_bytes;           // used for counting the bytes in a mouse packet
    uint8_t mouse_byte;           // mouse_byte from the mouse_packet( 3 mouse_bytes )
    uint8_t day1;                 // first digit of the day
    uint8_t day2;                 // second digit of the day
    uint8_t month1;               // first digit of the month
    uint8_t month2;               // second digit of the month
    uint8_t hour1;                // first digit of the hout
    uint8_t hour2;                // second digit of the hout
    uint8_t minute1;              // first digit of the minutes
    uint8_t minute2;              // second digit of the minutes
    uint8_t year1;
    uint8_t year2;
    state_game menu;              // state of the game
    int exit;                     //  variable used to signaling the player exiting the game , if 0 player didnt press exit, if 1 player pressed the exit button
    background background_sprite; // struct that contains the background information
    int rand;
    int dificuldade_multiplayer;
    int speed_background_multiplayer;

    Mouse mouse_stats;          // struct that contains information about the mouse;
    struct packet mouse_packet; //specifies the mouse packtes of the last interrupt
    Character_run p1;           // struct that contains the current bitmap of the main character as well as his position and width and height;
    uint8_t scancode;           //keyboard scancode
    state_character state;
    vector *vec;
    int conta_frames_character;     // counter for the current frame of the character
    int conta_interrupts;           //  conunter of interrupts produced by timer 0
    int conta_interrupts1;          // number of interrupts counter
    int conta_interrupts_rage;      // number of interrupts in rage mode
    int segundos_rage_mode;         // number of seconds in rage mode
    int multiple_bytes;             // if the scancode received from the keyboard is 0xe0, means theirs is another scancode incoming
    int conta_balas;                // number of projectiles available at the moment
    int conta_sword_ataques;        // number of sword ataques currently available
    int lb_pressed;                 //signals if the left button is pressed or not
    int rb_pressed;                 // signals if the right button is pressed or not
    int rage_mode;                  // rage mode active at (1) , deativated at (0)
    int full_rage;                  // rage bar full (1), rage bar not full(0)
    int contador_de_vida;           // number of lifes lefts
    int sobe;                       // indication if the player is jumping or not
    int score_geral;                // used to increase the rage meter resets at 25;
    int score[4];                   // score displayed on the screen
    int highscore_total;            // score that is efectibly used for the highscore menu
    highscore high_data;            // structs that contains the highscores value
    int collision_time;             // used to count the number of seconds after a collision that the player cant take dmg
    int conta_interrupts_collision; // number of interrupts passed after a collision
    int contador_highscore;         // highscore counter
    uint8_t maquina_pronta_para_multiplayer;
    int player1_vivo;

    //---------------------PLAYER 2-------------------
    int conta_bytes_mouse_to_send;
    Mouse mouse_stats2;
    struct packet mouse_packet2; //specifies the mouse packtes of the last interrupt
    Character_run p2;            // struct that contains the current bitmap of the main character as well as his position and width and height;
    uint8_t scancode2;
    state_character state2; // state of the character
    vector *vec_p2;         // vector that holds all enemies and projectiles on the screen
    int conta_interrupts_p2;
    int conta_frames_character_p2;
    int conta_interrupts_p2_1;

    int multiple_bytes2;             // if the scancode received from the keyboard is 0xe0, means theirs is another scancode incoming
    int conta_balas2;                // number of projectiles available at the moment
    int conta_sword_ataques2;        // number of sword ataques currently available
    int lb_pressed2;                 //signals if the left button is pressed or not
    int rb_pressed2;                 // signals if the right button is pressed or not
    int contador_de_vida2;           // number of lifes lefts
    int sobe2;                       // indication if the player is jumping or not                   //  variable used to signaling the player exiting the game , if 0 player didnt press exit, if 1 player pressed the exit button
    int score_geral2;                // used to increase the rage meter resets at 252;
    int score2[4];                   // score displayed on the screen
    int highscore_total2;            // score that is efectibly used for the highscore menu
    highscore high_data2;            // structs that contains the highscores value
    int collision_time2;             // used to count the number of seconds after a collision that the player cant take dmg
    int conta_interrupts_collision2; // number of interrupts passed after a collision
    int contador_highscore2;         // highscore counter
    uint8_t maquina2_pronta_para_multiplayer;
    int player2_vivo;

} boot_resources;

/**
 * @brief Subscibes all the interrupts needed, loads the variables,structs,bitmap needed to run the game
 *
 * @return returns a struct boot_resources 
 */

boot_resources *game_load();

/**
 * @brief Frees all the pointers used in the boot_resources struct aswell as unsubscribing interrupts
 *
 * @return doest return anything
 */

void game_end(boot_resources *start);

/**
 * @brief Function that contains main interrupts cycles for the mouse , keyboard and timer
 *
 * Calls all the necessary functions to process interrupts , from the timer
 * update_variables(), from the kbd kdb_ih() and kbd_processing(), from the mouse mouse_ih() 
 * and mouse__processing()
 *
 * @return doesnt return anything
 */

void all_interrupts(boot_resources *start);

/**
 * @brief Resets all the necessary variables needed to start the game again form scratch
 *
 * Function in similiar nature to game_load(), except it doesnt load bitmaps, it only reset some 
 * variables to their starting values
 *
 * @return doesnt return anything
 */

void game_reboot(boot_resources *start);

/**
 * @brief Updates all the major variables after a timer interrupts
 *
 * @return doesnt return anything
 */

void update_variables(boot_resources *start);

void update_variables_p2(boot_resources *start);
