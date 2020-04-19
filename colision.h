#ifndef COLISION_H
#define COLISION_H
#include "hero.h"
#include "entite_secondaire.h"
#include "defs.h"
#include "background.h"

SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y);
void CollisionParfaite(hero *h,background b);
//int Colision_bb(hero *h, entite *e);
int collision(entite *E, SDL_Rect pos);
#endif