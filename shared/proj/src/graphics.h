#pragma once

/** @defgroup graphics graphics
 * @{
 * Functions to program the graphical side of the game, images, atacks, backgrounds
 */

#include "game.h"
#include "bitmap.h"

/**
 * @brief Copy the information from the double buffer to the video mem
 *
 * Uses function memset and memcpy , and get_double_buffer() and get_video_mem()
 * and get_vram_size()
 * @return doesnt return anything
 */
void flip_display();

/**
 * @brief draws a bitmap of the mouse on to the double buffer
 *
 * Uses function drawBitmap()
 * 
 * @param start , struct boot_resources that contains all variables, bitmaps and structs
 * @return doesnt return anything
 */
void draw_mouse(boot_resources *start);

/**
 * @brief draws into the double buffer the current frame of the character
 *
 * Uses function drawBitmap()
 *
 * @param start , struct boot_resources that contains all variables, bitmaps and structs
 * @return doesnt return anything
 */
void draw_character(boot_resources *start, int character);

/**
 * @brief update the highscore on the highscore menu
 * 
 * @param  struct boot_resources that contains all variables, bitmaps and structs
 * 
 * @return doesnt return anything
 */
void scores_update(boot_resources *start);

/**
 * @brief draw the logos for the life , jireball , sword ataques as well as the number
 * available for each one
 *
 * Uses function drawBitmap()
 *
 * @param  struct boot_resources that contains all variables, bitmaps and structs
 * @return doesnt return anything
 */
void draw_contador_de_ataques(boot_resources *start);

/**
 * @brief checks for a collision pixel_per_pixel for player1
 *
 * After detecting that theres is a collision bettween two bitmaps, it is
 * necessary to check to see if there is in fact a collision bettween the 
 * two bitmaps, therefore we need to check each individual pixel from the collision rectangle
 * to see if there is at leat one that is active on both bitmaps
 * 
 * @param start , struct boot_resources that contains all variables, bitmaps and structs
 *  p1_x1, position of the left side of the main chracter;
 *  p1_x2, position of the right side of the main characte;r
 *  p1_y1, position of the top side of the main character;
 *  p1_y2, position of the bottom side of the main character;
 *  enemy_x1, position of the left side of the enemy;
 *  enemy_x2, position of the right side of the enemy;
 *  enemy_y1, position of the top side of the enemy;
 *  enemy_y2, position of the bottom side of the enemy;
 *  enemy_bitmap enemy bitmap, can eihter be fantasma, taurus or helldog
 * 
 * @return 0 if no collision is detected, -1 if a  collision is detected
 */
int check_collision_pixel_per_pixel(boot_resources *start, int p1_x1, int p1_x2, int p1_y1, int p1_y2, int enemy_x1, int enemy_x2, int enemy_y1, int enemy_y2, Bitmap *enemy_bitmap);

/**
 * @brief checks for a collision pixel_per_pixel for player2
 *
 * After detecting that theres is a collision bettween two bitmaps, it is
 * necessary to check to see if there is in fact a collision bettween the 
 * two bitmaps, therefore we need to check each individual pixel from the collision rectangle
 * to see if there is at leat one that is active on both bitmaps
 * 
 * @param start , struct boot_resources that contains all variables, bitmaps and structs
 *  p1_x1, position of the left side of the main chracter;
 *  p1_x2, position of the right side of the main characte;r
 *  p1_y1, position of the top side of the main character;
 *  p1_y2, position of the bottom side of the main character;
 *  enemy_x1, position of the left side of the enemy;
 *  enemy_x2, position of the right side of the enemy;
 *  enemy_y1, position of the top side of the enemy;
 *  enemy_y2, position of the bottom side of the enemy;
 *  enemy_bitmap enemy bitmap, can eihter be fantasma, taurus or helldog
 * 
 * @return 0 if no collision is detected, -1 if a  collision is detected
 */
int check_collision_pixel_per_pixel_p2(boot_resources *start, int p2_x1, int p2_x2, int p2_y1, int p2_y2, int enemy_x1, int enemy_x2, int enemy_y1, int enemy_y2, Bitmap *enemy_bitmap);

/**
 * @brief checks for a collision bettween the fireball from palyer 1 and any enemy on the screen
 *
 * @param start , struct boot_resources that contains all variables, bitmaps and structs
 *  enemy_x1, position of the left side of the enemy;
 *  enemy_x2, position of the right side of the enemy;
 *  enemy_y1, position of the top side of the enemy;
 *  enemy_y2, position of the bottom side of the enemy;
 *  enemy_bitmap enemy bitmap, can eihter be fantasma, taurus or helldog
 * 
 * @return 0 if no collision is detected, -1 if a  collision is detected
 */
int check_collision_fireball_enemy(boot_resources *start, int enemy_x1, int enemy_x2, int enemy_y1, int enemy_y2);

/**
 * @brief checks for a collision bettween the fireball from palyer 2 and any enemy on the screen
 *
 * @param start , struct boot_resources that contains all variables, bitmaps and structs
 *  enemy_x1, position of the left side of the enemy;
 *  enemy_x2, position of the right side of the enemy;
 *  enemy_y1, position of the top side of the enemy;
 *  enemy_y2, position of the bottom side of the enemy;
 *  enemy_bitmap enemy bitmap, can eihter be fantasma, taurus or helldog
 * 
 * @return 0 if no collision is detected, -1 if a  collision is detected
 */
int check_collision_fireball_p2_enemy(boot_resources *start, int enemy_x1, int enemy_x2, int enemy_y1, int enemy_y2);

/**
 * @brief checks for a collision pixel_per_pixel with playe1
 *
 * Calls fucntions check_colision fireball enemy() and check_collision_pixel_per_pixel()
 * 
 * @param start , struct boot_resources that contains all variables, bitmaps and structs
 *
 * 
 * @return 0 if no collision is detected, -1 if a  collision is detected but invalidated
 * because of a sword atack, 2 if in fact there occurs a collision uninterrupted
 */
void check_collision(boot_resources *start, enemies *aux);


/**
 * @brief checks for a collision pixel_per_pixel with player2
 *
 * Calls fucntions check_colision fireball enemy() and check_collision_pixel_per_pixel()
 * 
 * @param start , struct boot_resources that contains all variables, bitmaps and structs
 *
 * @return 0 if no collision is detected, -1 if a  collision is detected but invalidated
 * because of a sword atack, 2 if in fact there occurs a collision uninterrupted
 */
int check_collision_p2(boot_resources *start, int pos, int type);

/**
 * @brief draws the enemy into to the double buffer
 *
 * uses drawBitmap()
 *
 * @param start , struct boot_resources that contains all variables, bitmaps and structs
 * @return doesnt return anything
 */
void draw_enemy(boot_resources *start);

/**
 * @brief draws the fireball projectile into to the double buffer
 *
 * uses drawBitmap()
 *
 * @param start , struct boot_resources that contains all variables, bitmaps and structs
 * @return doesnt return anything
 */
void draw_projetil(boot_resources *start);

/**
 * @brief draw the background in the game section into the double_buffer
 *
 * Uses function drawBitmap()
 *
 * @param  struct boot_resources that contains all variables, bitmaps and structs
 * @return doesnt return anything
 */
void draw_background(boot_resources *start);

/**
 * @brief draw the background menu into the double_buffer
 *
 * Uses function drawBitmap()
 *
 * @param  struct boot_resources that contains all variables, bitmaps and structs
 * @return doesnt return anything
 */
void draw_background_menu(boot_resources *start);

/**
 * @brief draw the rage_bar and the pressr bitmap into the double_buffer
 *
 * Uses function drawBitmap()
 *
 * @param  struct boot_resources that contains all variables, bitmaps and structs
 * @return doesnt return anything
 */
void draw_rage_bar(boot_resources *start);

/**
 * @brief function used to assemble the next frame of the game
 *
 * Calls all other functions with draw on their name in order to assemble
 * the next frame of the game, call the fucntions on a specific order
 *
 * @param  struct boot_resources that contains all variables, bitmaps and structs
 * @return doesnt return anything
 */
void draw_frame(boot_resources *start);

/**
 * @brief prints the number the user want on screee
 *
 * @param condition, variable to use on the switch
 * @param  start, struct that contains all the varaibles, structs necessary to run the game
 * @param x ,  x  position on the screen  that we want to draw the number
 * @param y ,  y  position on the screen  that we want to draw the number
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
void print_number(int condition, struct boot_resources *start, int x, int y);



