#include "entite_secondaire.h"

void init_entite(entite *E)
{
  int test;
  E->image_secondaire = IMG_Load(entite.png);
  if (E->image_secondaire == NULL)
  {
    printf("Unable to load Entite png:%s\n", SDL_GetError());
    test = -1;
  }

  test = 0;
  if (test != -1)
  {
    E->positionEntite.x = 50;
    E->positionEntite.y = 200;
    posMax = 300;
    posMin = 100;
    E->Direction = 0;
    posSprite.x = 0 posSprite.y = 0 posSprite.w = 100;
    posSprite.h = 100;
  }
}
void animation(entite *E)
{
  E->posSprite.y = E->Direction if (posSprite.x = 600 - posSprite.w)
                       posSprite.x = 0;
  else
  {
    posSprite.x = posSprite.x + posSprite.w;
  }
}
void display_entite(entite E, SDL_Surface *screen)
{
  SDL_BlitSurface(E.image, &E.positionAnimation[E.Frame.i][E.Frame.j], screen, &E.positionAbsolue);
}

void deplacer_alea(entite *E)
{
}
