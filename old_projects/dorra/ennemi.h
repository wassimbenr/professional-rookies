#ifndef Ennemi_H
#define Ennemi_H
#include <SDL/SDL.h>

#include "functions.h"
typedef enum STATE STATE;
enum STATE
{WAITING,FOLLOWING,ATTACKING};
struct Ennemi{
        SDL_Rect positionAbsolue;
	SDL_Rect positionAnimation;
	SDL_Surface * image;
	int positionInitial;
	int direction;
	int moving;
STATE STATE;
};
typedef struct Ennemi Ennemi;

void  loadEnnemiImages(Ennemi * E);

void initEnnemi(Ennemi *E);

void AnnimateEnnemi(Ennemi *E);

void MoveEnnemi(Ennemi *E,SDL_Rect positionperso);

void freeEnnemi(Ennemi *E);
void UpdateEnnemi(Ennemi *E ,SDL_Rect positionperso);
void blitEnnemi(Ennemi *E, SDL_Surface* screen,SDL_Rect positionFond);
void input_ennemi(Ennemi *E , SDL_Rect positionperso);
int  collision(Ennemi *E , SDL_Rect positionperso);

#endif
