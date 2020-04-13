#include <stdio.h>
#include <string.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"

#include "defs.h"

typedef enum State
{
    IDLE,
    DIE,
    ATTACK,
    DAMAGE,
    JUMP,
    WALK_RIGHT,
    WALK_LEFT,
    PUNCH,
    KICK
} state;
typedef enum Direction
{
    RIGHT,
    LEFT
} direction;
typedef struct Sprite
{
    SDL_Surface *image;
    SDL_Rect frame;
    int curframe, maxframe;
} sprite;
typedef struct Hero
{
    SDL_Rect position;
    sprite sprite;
    state state;
    int collision_UP, collision_DOWN, collision_RIGHT, collision_LEFT;
    int current_ground_position;
    direction direction;

} hero;

void initialiser_hero(hero *h, char name[20]);
void deplacer_hero(hero *h, SDL_Event event);
void animer_hero(hero *h, state movement);
void afficher_hero(hero h, SDL_Surface *screen);
void free_hero(hero *h);