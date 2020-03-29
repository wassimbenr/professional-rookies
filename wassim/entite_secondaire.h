#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <time.h>
#include "SDL/SDL_ttf.h"

typedef struct Sprite
{
	SDL_Surface *image;
	SDL_Rect frame;
	int curframe,maxframe;
}sprite;

struct Entite
{ 
        SDL_Rect posScreen ;
        SDL_Rect posSprite ;

        SDL_Rect posMax;
        SDL_Rect posMin;
        SDL_Rect position_entite;
        sprite sprite;
	int Direction;
        int vitesse;
};
typedef  struct Entite entite;
void init_entite(entite *E);
void deplacer_alea(entite *E);
void animation (entite *E);
void afficher_entite(entite *E, SDL_Surface* screen);
void freeEnnemi(entite *E);
void free_entite(entite *E);