#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <stdio.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "defs.h"
#include "structs.h"

/**
 * @struct background
 * @brief for background
 */
typedef struct Background
{
	SDL_Surface *image;
	SDL_Surface *foreground;
	SDL_Surface *background_mask;
	SDL_Rect position_background_mask;
	SDL_Rect posCamera;
	SDL_Rect pos_foreground;
	SDL_Surface *platform;
	SDL_Rect pos_platform;
} background;

/**
 * @struct platforme
 * @brief for platforme
 */
typedef struct Platforme
{
	SDL_Surface *image;
	SDL_Rect position, pos_init;
	int interval;
	int sens;
} platforme;

/**
 * @struct text
 * @brief for text
 */
typedef struct Text
{
	SDL_Surface *text;
	SDL_Rect position;
	TTF_Font *font;
	SDL_Color color;
	int size;
} text;


/**
 * @struct heure
 * @brief for time
 */
typedef struct Heure
{
	int heures;
	int minutes;
	int secondes;
} heure;


/**
 * @struct timer 
 * @brief to count the time
 */
typedef struct Timer
{
	int startTicks;
	int pausedTicks;
	int paused;
	int started;
	heure time;
} timer;


/**
 * @struct minimap
 * @brief for the minimap
 */
typedef struct Minimap
{
	SDL_Surface *image, *hero;
	SDL_Rect pos_image,pos_hero;
}minimap;


/**
 * @struct Portal
 * @brief for the portal
 */
typedef struct Portal
{
	SDL_Surface *still[4],*enter[15];
	SDL_Rect pos_enter,pos_still;
	int frame_still,frame_enter;
}portal;

//background
void scrolling(background *b, SDL_Event event);
void initialiser_background(background *b, parameter p);
void afficher_background(background *b, SDL_Surface *screen);
void free_background(background *b);

//platforme
void initialiser_platforme(platforme *p, int x, int y, int interval,int sens);
void initialiser_plats_horiz(platforme plats[], int n);
void animer_platformes(platforme plats[], int n);
void animer_platformes_horiz(platforme plats[], int n);
void initialiser_plats(platforme plats[], int n);
void afficher_platformes(platforme plats[], background b, SDL_Surface *ecran, int n);
void free_platformes(platforme plats[], int n);
//texte
void initialiser_text(text *i, char message[40], int x, int y, int size);
void afficher_text(text i, background b, SDL_Surface *ecran);

void initialiser_text_2(text *i, int x, int y, int size);
void afficher_text_2(text i, SDL_Surface *ecran, char message[20]);

void initialiser_instructions(text instructions[], int n);
void afficher_instructions(text instructions[], int n, background b, SDL_Surface *ecran);
void free_instructions(text instructions[], int n);

void init_timer(timer *t);
void start_timer(timer *t);
void stop_timer(timer *t);
void get_time(timer *t);
void pause_timer(timer *t);
void resume_timer(timer *t);
void show_time(timer *t, SDL_Surface *screen);
void afficher_temps(text *t, timer *timer, SDL_Surface *ecran);

void free_param(parameter *p);





#endif
