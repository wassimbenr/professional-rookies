#ifndef PLAY_H_
#define PLAY_H_
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "hero.h"
#include "structs.h"
void jeu(SDL_Surface *ecran, etat *etat,hero safwen,parameter *p,character c,background background);
#endif
