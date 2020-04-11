#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <time.h>
#include "SDL/SDL_ttf.h"

//#include "hero.h"
typedef struct Sprite
{
	SDL_Surface *image;
	SDL_Rect frame;
	int curframe,maxframe;
}sprite;
typedef enum State
{
	IDLE,
	DIE,
	ATTACK,
	DAMAGE,
	JUMP,
	WALK,

}state;
struct Entite
{ 
        SDL_Rect posMax;
        SDL_Rect posMin;
        SDL_Rect posEntite;
        sprite sprite;
		state state;
		int Direction;
		int type;// 0=enemie - 1=coin
        int vitesse;
};
typedef  struct Entite entite;
void init_entite(entite *E);
void deplacer_alea(entite *E);
void animation_entite(entite *E);
void afficher_entite(entite *E, SDL_Surface* screen);
void free_entite(entite *E);
//int colisionBoundingBox(entite *E, Hero *h);