#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <stdio.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "defs.h"

typedef struct Background
{
	SDL_Surface *image;
	SDL_Surface *background_mask;
	SDL_Rect position_background_mask;
	SDL_Rect posCamera;
	SDL_Surface *platform;
	SDL_Rect pos_platform;
} background;

typedef struct Platforme
{
	SDL_Surface *image;
	SDL_Rect position;
} platforme;

typedef struct Text
{
	SDL_Surface *text;
	SDL_Rect position;
	TTF_Font *font;
	SDL_Color color;
}text;

//background
void scrolling(background *b, SDL_Event event);
void initialiser_background(background *b);
void afficher_background(background *b, SDL_Surface *screen);
void free_background(background *b);
//platforme
void initialiser_platforme(platforme *p, int x, int y);
void animer_platforme(platforme *p);
void afficher_platforme(platforme p, background b, SDL_Surface *ecran);
//texte
void initialiser_text(text *i,char message[40],int x,int y,int size);
void afficher_text(text i,background b,SDL_Surface *ecran);
#endif
