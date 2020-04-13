#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"

typedef struct Sprite_entite
{
    SDL_Surface *image;
    SDL_Rect frame;
    int curframe, maxframe;
} sprite_entite;

typedef enum State_entite
{
    IDLE,
    DIE,
    ATTACK,
    DAMAGE,
    JUMP,
    WALK
} state_entite;

typedef enum Direction_entite
{
    LEFT,
    RIGHT
} direction_entite;

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
    sprite_entite sprite;
    state_entite state;
    direction_entite direction;

    type type;
    int vitesse;
} entite;

void initialiser_entite(entite *E);
void deplacer_alea(entite *E);
void animer_entite(entite *E);
void afficher_entite(entite *E, SDL_Surface *screen);
void free_entite(entite *E);