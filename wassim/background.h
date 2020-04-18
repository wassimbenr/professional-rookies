#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <stdio.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "defs.h"
#include "hero.h"

typedef struct Background
{
	SDL_Surface *image;
	SDL_Surface *background_mask;
	SDL_Rect position_background;
	SDL_Rect position_background_mask;
	SDL_Rect posCamera;
}background;

void scrolling(background *b,hero *h,SDL_Event event);
void initialiser_background(background *b);
void afficher_background(background *b,SDL_Surface *screen);
void cameraXY(background *b,SDL_Surface *screen);
void free_background(background *b);
#endif


/*
scrolling - direction



*/