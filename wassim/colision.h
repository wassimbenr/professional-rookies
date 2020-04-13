#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "structs.h"
#include "background.h"

SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y);
void collisionParfaite(entite *h,background b);
int colision_bb(entite *h, entite *e);