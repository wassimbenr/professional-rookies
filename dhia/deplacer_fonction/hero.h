#include "structs.h"

void initialiser_hero(entite *h,char name[20]);
void deplacer_hero(entite *h,SDL_Event event);
void animer_hero(entite *h,state movement);
void afficher_hero(entite *h, SDL_Surface* screen);
void free_hero(entite *h);