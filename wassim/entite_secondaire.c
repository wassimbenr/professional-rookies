#include "entite_secondaire.h"
void init_entite(entite *E)
{
  E->Direction = 0;
  E->sprite.image = IMG_Load("img/es/es.png");
  E->sprite.frame.x = 0;
  E->sprite.frame.y = 0;
  E->sprite.maxframe = 4;
  E->sprite.frame.w = (E->sprite.image->w) / 4 ;
  E->sprite.frame.h = (E->sprite.image->h) / 4 ;
  E->sprite.curframe = 0;
  
  E->position_entite.x = 100;
  E->position_entite.y = 500;
}
void animation(entite *E)
{
}
void afficher_entite(entite *E, SDL_Surface *screen)
{
  SDL_BlitSurface(E->sprite.image,&E->sprite.frame,screen,&E->position_entite);
}
void deplacer_alea(entite *E)
{
}