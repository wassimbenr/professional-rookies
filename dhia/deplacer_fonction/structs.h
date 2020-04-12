#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"

#include "defs.h"

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
	WALK_RIGHT,
	WALK_LEFT,
	PUNCH,
	KICK
}state;
typedef enum Direction
{
	RIGHT,LEFT
}direction;
struct Entite
{
	SDL_Rect posMax;
	SDL_Rect posMin;
	
	SDL_Rect posEntite;
	SDL_Rect position;

	sprite sprite;
	state state;
	int collision_UP,collision_DOWN,collision_RIGHT,collision_LEFT;
	int current_ground_position;
	direction direction;
	int Direction;
	int type; // 0=enemie - 1=coin
	int vitesse;
};
typedef struct Entite entite;
typedef struct Background
{
	SDL_Surface *image;
	SDL_Surface *background_mask;
	SDL_Rect position_background;
	SDL_Rect position_background_mask;
}background;
#endif