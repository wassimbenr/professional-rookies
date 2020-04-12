#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <time.h>
#include "SDL/SDL_ttf.h"
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
	direction direction;
	int Direction;
	int type; // 0=enemie - 1=coin
	int vitesse;
};
typedef struct Entite entite;
#endif