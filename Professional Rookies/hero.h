#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"

enum direction {RIGHT,LEFT};
enum movement {IDLE,WALK,JUMP,PUNCH,KICK,HIT,DIE};

typedef enum direction direction;
typedef enum movement movement;

typedef struct Sprite
{
	SDL_Surface *image;
	SDL_Rect frame;
	int curframe,maxframe;
}sprite;

typedef struct Hero
{
	sprite sprite;
	SDL_Rect position;
	direction direction;
	movement movement;

}hero;
void initialiser_hero(hero *h);
void animer_hero(hero *h,movement movement);
void afficher_hero(hero *h, SDL_Surface* screen);
void free_hero(hero *h);