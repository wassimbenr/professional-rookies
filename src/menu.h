#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "structs.h"
#include "jeu.h"
#include "hero.h"
#include "background.h"

void initialiser_parameters(parameter *p);
void menu(SDL_Surface *screen, etat *etat, parameter *p);
void game_load(hero *h, background *b, etat *etat, SDL_Surface *screen, parameter *p,character *c);
void settings(SDL_Surface *screen, parameter *p, etat *etat);
void character_choice(hero *h, etat *etat, SDL_Surface *screen, parameter *p, character *c);
void save_game(hero h, background b, character c);
void load_game(hero *h, background *b, character *c);
void game_over(SDL_Surface *screen, etat *etat, parameter *p);