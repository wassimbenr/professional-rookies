#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "structs.h"
void scrolling(background *b, entite *e);
void initialiser_background(background *b);
void afficher_background(background *b, SDL_Surface *screen);
void free_background(background *b);