#ifndef ES_H
#define ES_H
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include <time.h>
#include "hero.h"
#include "defs.h"

typedef struct Sprite_entite
{
    SDL_Surface *image;
    SDL_Rect frame;
    int curframe, maxframe;
} sprite_entite;

typedef enum State_entite
{
    WALK_entite,
    DIE_entite,
    ATTACK_entite,
    FOLLOW_entite
} state_entite;


typedef enum Type
{
    HERO,
    ENTITE,
    COIN
} type;

typedef struct Entite
{
    SDL_Rect posMax;
    SDL_Rect posMin;

    SDL_Rect position;
    sprite_entite sprite_entite;
    state_entite state_entite;
    int direction_entite;

    type type;
    int vitesse;
} entite;

void input_ennemi(entite *E, hero *h);
void update_entite(entite *E ,hero *h);
void attack_entite(entite *E,hero *h);
void initialiser_entite(entite *E);
void deplacer_alea(entite *E);
void animer_entite(entite *E);
void afficher_entite(entite *E, SDL_Surface *screen);
void free_entite(entite *E);
#endif