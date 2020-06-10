#ifndef MULTIPLAYER_H_
#define MULTIPLAYER_H_
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "hero.h"
#include "structs.h"
#include "background.h"
#include "collision.h"
#include "entite_secondaire.h"
#include "defs.h"
#include "enigme.h"
#include "menu.h"

void animer_platforme2(platforme *p, int x);
void afficher_platforme2(platforme p, background b, SDL_Surface *ecran);
void initialiser_platforme2(platforme *p, int x, int y);
void CollisionParfaite2(hero *h, background b, platforme p);
void afficher_hero1(hero h, SDL_Surface *screen, background b,hero h2);
void afficher_hero2(hero h, SDL_Surface *screen, background b,hero h2);
void initialiser_background1(background *b);
void initialiser_background2(background *b);
void initialiser_hero2(hero *h, char name[20]);
void multiplayer(SDL_Surface *ecran, etat *etat, parameter *p, character c);
void deplacer_hero1(hero *h, background *b, int *Jcontinuer, character c, platforme p);
void deplacer_hero2(hero *h, background *b, int *Jcontinuer, character c, platforme p);
void animer_hero2(hero *h, state movement, character c);


#endif
