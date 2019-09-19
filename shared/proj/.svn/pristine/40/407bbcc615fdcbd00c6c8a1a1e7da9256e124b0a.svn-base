#pragma once

/** @defgroup statemachine statemachine
 * @{
 *
 * Functions to update the state maachines of the game
 */

typedef enum
{
    MAIN_MENU,              // if menu is the start_menu " main menu"
    GAME,                   // if the currrent state of the game is the 1 player, single player, game
    GAME_2PLAYERS,          // if theres 2 players playing the game, multiplayer mode
    GAME_OVER_MENU,         // if one player losses the game, game over menu
    DIFICULTY_MENU,         // menu to choose the dificulty
    HIGHSCORE_MENU,         // highsocre menu for the 1 player mode, highscores for the 2 player mode not implemented
    MULTIPLAYER_MENU,       // multiplayer menu in wich the user awaits that the second player to go to the multiplayer menu aswell
    PAUSE_MENU,             // pause menu only available in 1 player mode
    GAME_OVER_MENU_2PLAYERS //gameover menu for the 2 players mode, only available when the two characters are dead
} state_game;

typedef enum
{
    PLAY_PRESSED,        //if play button is pressed
    EXIT_PRESSED,        //if exit button is pressed
    NOTHING1,            //if no button is pressed
    ESC_PRESSED,         //if esc button on the keyboard is pressed
    HARD_PRESSED,        //if hard dificulty is chosen
    EASY_PRESSED,        //if easy dificulty is chosen
    MEDIUM_PRESSED,      //if medium dificulty is chosen
    CONTINUE_PRESSED,    //if continu button is pressed in the pause menu
    RESTART_PRESSED,     //if restart button is pressed
    MAIN_MENU_PRESSED,   //if main menu button is pressed
    HIGHSCORE_PRESSED,   //if highscore button is pressed
    DIFICULTY_PRESSED,   //if dificulty button is pressed
    COLISION,            //if theres is a collision between the character and a enemy and the player has only 1 life left, only available in 1 player mode, "single player"
    PRONTO2MAQUINAS,     //if both machines are ready for the 2 players options, "multiplayer mode"
    MULTIPLAYER_PRESSED, //if 2 player is pressed, "multiplayer mode"
    BOTHDEAD             //if both players are death in 2 players mode

} event_game;

typedef enum
{
    RUN,     // if the character is running
    FLY1,    // if the character is flying
    JUMPONCE // if the character is jumping

} state_character;

typedef enum
{
    UP,      // if the user press w on the keyboard
    DOWN,    // if the user press s on the keyboard
    RIGHT,   // if the user press d on the keyboard
    LEFT,    // if the user press  a on the keyboard
    NOTHING, // if doesnt press anything on the keyboard
    JUMP,    // if the user press space on the keyboard
    CHAO     // if the character is on the ground level
} event_character;

struct boot_resources;

/**
 * @brief updates character in case of a character evt
 * 
 * state machine that is responsible for the character state
 * 
 * @param start, struct that contains all variables, struccs and more necessary to run the game
 * @param evt , game event that happened
 */
void update_character(event_character evt, struct boot_resources *start, int player);

/**
 * @brief updates the menu of the game in case of a game evt
 *
 * state machine that is responsible for the menus of the game
 *
 * @param start, struct that contains all variables, struccs and more necessary to run the game
 * @param evt , game event that happened
*/
void update_menu(event_game evt, struct boot_resources *start);
