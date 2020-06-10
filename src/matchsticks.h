#ifndef AI_H
#define AI_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "hero.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


/**
 * @struct Text_enigme
 * @brief for text generation in the enigma
 */
typedef struct Text_enigme
{
	SDL_Surface *text;
	SDL_Rect position;
	TTF_Font *font;
	SDL_Color color1;
	SDL_Color color2;
	int size;
} text_enigme;


/**
 * @struct Matchstick
 * @brief To load the match image
 */
typedef struct Matchstick
{
	SDL_Surface *Matchstick;
	SDL_Rect positionMatchstick;
	int MatchCount;
} Matchstick;

void AI_Game(SDL_Surface *screen);


int AI_enigme(SDL_Surface *screen,hero *h);

void initialiser_text_enigme(text_enigme *i, char message[40], int x, int y, int size);
void afficher_text_enigme(text_enigme i, SDL_Surface *ecran, char message[20]);

//void afficher_text_2(text_enigme i, SDL_Surface *ecran, char message[20]);
int rand_matchs(int MatchCount);
void Init(text_enigme *matchText, text_enigme *PturnText, text_enigme *AIturnText, Matchstick *match);
void affichage_matchs(SDL_Surface *screen, Matchstick *match);
void updateText(SDL_Surface *screen, int turn, text_enigme *PturnText, text_enigme *AIturnText);
void afficherText(SDL_Surface *screen, text_enigme matchtext, text_enigme PturnText, text_enigme AIturnText, int turn);
void game_end(Matchstick match, int Turn, text_enigme *PturnText, text_enigme *AIturnText, int *AIcontinuer,int *win);

#endif
