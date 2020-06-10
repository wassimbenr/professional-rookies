#ifndef PLAY_H_
#define PLAY_H_
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "background.h"
#include "entite_secondaire.h"
#include "hero.h"
#include "collision.h"
#include "defs.h"
#include "enigme.h"
#include "structs.h"
#include "menu.h"
#include "matchsticks.h"
#include "pendu.h"
#include "SDL/SDL_rotozoom.h"

void jeu(SDL_Surface *ecran, etat *etat,hero *safwen,parameter *p,character c,background background,dialogue d);
#endif
