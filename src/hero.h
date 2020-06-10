#ifndef HERO_H
#define HERO_H
#include <stdio.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "structs.h"
#include "background.h"
#include "defs.h"


/**
 * @struct State
 * @brief Describe the hero state
 */
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
    KICK,
    FALLING
} state;

/**
 * @struct Direction
 * @brief Describe the hero direction
 */
typedef enum Direction
{
    RIGHT,
    LEFT
} direction;

/**
 * @struct Sprite
 * @brief to load and update the sprite
 */
typedef struct Sprite
{
    SDL_Surface *image;
    SDL_Rect frame;
    int curframe, maxframe;
} sprite;


/**
 * @struct Vie
 * @brief For life parameters
 */
typedef struct Vie
{
    SDL_Surface *heart;
    SDL_Rect position_heart_a;
    SDL_Rect position_heart_b;
    SDL_Rect position_heart_c;
    int nb_vie;
} vie;


/**
 * @struct Score
 * @brief For score updating
 */
typedef struct Score
{
    SDL_Surface *texte_score;
    SDL_Rect position_texte;
    TTF_Font *score_font;
    SDL_Color couleurNoire;
    int valeur_score;
} score;

/**
 * @struct Hero
 * @brief anything used by the main character
 */
typedef struct Hero
{
    SDL_Rect position;
    sprite sprite;
    state state;
    int collision_UP, collision_DOWN, collision_RIGHT, collision_LEFT,collision_DOWN_PLAT;
    int current_ground_position;
    direction direction;
    vie vie_hero;
    score score_hero;
} hero;


/**
 * @struct Dialogue
 * @brief To load the dialogue in the game
 */
typedef struct Dialogue
{
    text text;
    char script[20][40];
    SDL_Surface *dialogue_box, *hero_dialogue;
    SDL_Rect pos_dialogue_box, pos_hero_dialogue;
    int line;
    int talking;
    int first_time;
} dialogue;

void initialiser_hero(hero *h, char name[20]);
void deplacer_hero(hero *h, background *b, int *Jcontinuer, character c, platforme plats[], int *saving, int n,int *mini);
void animer_hero(hero *h, state movement, character c);
void afficher_hero(hero h, SDL_Surface *screen, background b);
void free_hero(hero *h);

void initialiser_dialogue(dialogue *d, SDL_Surface *ecran, character c);
void dialogue_choice(dialogue *d, SDL_Surface *ecran, int first_line);
void playing_dialogue(dialogue *d, hero h, SDL_Surface *ecran, timer timer);
void afficher_dialogue(dialogue d, SDL_Surface *ecran);
void linear_dialogue(dialogue *d, SDL_Surface *ecran);
void free_dialogue(dialogue *d);

void initialiser_minimap(minimap *m,background b, hero h);
void afficher_minimap(minimap *m, hero h,SDL_Surface *screen,int mini);
void free_minimap(minimap *m);

void initialiser_portal(portal *p);
void animer_portal(portal *p);
void afficher_portal(portal p, background b, hero h, SDL_Surface *screen);
void free_portal(portal *p);

void camera_pan(background *b, hero h, int x, int y, int *panning, int duree);

#endif