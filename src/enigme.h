#ifndef ENIGME_H
#define ENIGME_H

#include <SDL/SDL.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "hero.h"
#include <math.h>
#include <time.h>


/**
 * @struct enigme 
 * @brief struct for the enigma
 */
typedef struct
{
    SDL_Surface *background, *bgansewr, *bghover;
    SDL_Surface *Question,*ansewr1,*ansewr2,*ansewr3,*ansewr4,*Yes,*No,*Final;
    SDL_Rect positionBackground;
    SDL_Rect positionAnsewr1, positionAnsewr2, positionAnsewr3, positionAnsewr4;
    SDL_Rect positionQ;
    SDL_Rect positionhover,positionFinal;
    int rangR,resolution;
} enigme;

void enigme_math(SDL_Surface *screen, enigme *E, hero *h);
void initenigme(enigme *E);
void afficherenigme(enigme *E, SDL_Surface *screen);
void freeenigme(enigme *E);
void resolutionenigme(enigme *E, SDL_Surface *screen);
void gestiontemps(enigme E, SDL_Surface screen);
int generation_auto_enig(enigme E, int randenig);
void generation_autoreponse_enig(enigme E, int randenig);
#endif