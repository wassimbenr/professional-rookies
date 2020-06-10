#ifndef COLLISION_H
#define COLLISION_H
#include "hero.h"
#include "entite_secondaire.h"
#include "defs.h"
#include "background.h"

SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y);
void CollisionParfaite(hero *h, background b);
int collision_platforme(hero *h, platforme plats[], int n);
int collision_platforme2(hero *h, platforme plats[], int n);
//int Colision_bb(hero *h, entite *e);
int collision(entite *E, hero *h);
int collision_boss(boss *e, hero *h);
#endif