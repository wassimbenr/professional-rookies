#include "entite_secondaire.h"

void init_entite(entite *E)
{
  E->Direction = 0;
  E->sprite.image = IMG_Load("img/es/es.png");
  E->sprite.frame.x = 0;
  E->sprite.frame.y = 0;
  E->sprite.frame.w = 50;
  E->sprite.frame.h = 69;
  E->sprite.curframe = 0;
  E->sprite.maxframe = 4;
  E->position_entite.x = 100;
  E->position_entite.y = 0;

  SDL_Rect posMax;
  SDL_Rect posMin;
  SDL_Surface *sprite_secondaire;
  SDL_Rect posScreen;
  SDL_Rect posSprite;
  SDL_Rect position_entite;
  sprite sprite;
  int vitesse;
}
void animation(entite *E)
{
}
void display_entite(entite E, SDL_Surface *screen)
{
}
void deplacer_alea(entite *E)
{
}