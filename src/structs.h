#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <time.h>
#include "SDL/SDL_ttf.h"

typedef enum etat
{
    MENU,
    SETTINGS,
    GAME,
    ENIGME,
    GAME_OVER,
    EXIT,
    CHARACTER,
    GAME_LOAD,
} etat;

typedef enum Character
{
    SAFWEN,
    OMAR,
    FIRAS,
}character;

typedef struct Parameter
{
    Mix_Music *music;
    Mix_Chunk *click;
    int volume;
    int fullscreen;
    int mute;
} parameter;

#endif