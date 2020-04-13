#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <time.h>
#include "SDL/SDL_ttf.h"
typedef struct Background
{
	SDL_Surface *image;
	SDL_Surface *background_mask;
	SDL_Rect posBackground;
	SDL_Rect posBackground_mask;
	SDL_Rect posCamera;
} background;
typedef struct Sprite
{
	SDL_Surface *image;
	SDL_Rect frame;
	int curframe, maxframe;
} sprite;
typedef enum State
{
	IDLE,
	DIE,
	ATTACK,
	DAMAGE,
	JUMP,
	WALK,
	PUNCH, // if else
	KICK   // useless
} state;
typedef enum Direction
{
	LEFT,
	RIGHT
} direction;
typedef enum Type
{
	HERO,
	ENTITE,
	COIN
} type;
typedef struct Entite
{
	SDL_Rect posMax;
	SDL_Rect posMin;

	SDL_Rect position;
	sprite sprite;
	state state;
	direction direction;
	type type;

	int collision_UP, collision_DOWN, collision_RIGHT, collision_LEFT;
	int vitesse;

} entite;

#endif