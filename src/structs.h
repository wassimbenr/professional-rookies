#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <time.h>
#include "SDL/SDL_ttf.h"


/**
 * @struct etat
 * @brief for the game state
 */
typedef enum etat
{
    MENU,
    SETTING,
    GAME,
    ENIGME,
    GAME_OVER,
    EXIT,
    CHARACTER,
    MULTIPLAYER,
    GAME_LOAD,
    INTRO,
    CHEAT,
    CREDS,
    STORY_INTRO
} etat;


/**
 * @struct character
 * @brief for character choice
 */
typedef enum Character
{
    SAFWEN,
    OMAR,
    FIRAS,
}character;


/**
 * @struct parameter
 * @brief for the game settings
 */
typedef struct Parameter
{
    Mix_Music *music;
    Mix_Chunk *click;
    Mix_Chunk *keyboard_click;
    int volume;
    int fullscreen;
    int mute;
} parameter;

#endif