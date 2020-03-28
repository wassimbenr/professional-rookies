#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"

typedef struct Sprite
{
	SDL_Surface *image;
	SDL_Rect frame;
	int curframe,maxframe;
}sprite;

typedef struct Hero
{
	sprite sprite;
	SDL_Rect position_hero;
	int direction;
	int vitesse;
	int gravite;
}hero;

void initialiser_hero(hero *h);
void deplacer_hero(hero *h,SDL_Event event,SDL_Surface* backgroundMask);
void afficher_hero(hero *h, SDL_Surface* screen);
void animer_hero(hero *h);
void free_hero(hero *h);
