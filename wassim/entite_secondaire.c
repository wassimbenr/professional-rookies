#include "entite_secondaire.h"
void init_entite(entite *E)
{
	E->Direction = 1;
	E->type = 0;
	E->state = WALK;
	E->sprite.image = IMG_Load("img/es/walk2.png"); //initialiser la premiere sprite
	E->sprite.frame.x = 0;
	E->sprite.frame.y = 0;
	E->sprite.maxframe = 5; //Nb de colone

	E->sprite.curframe = 0; //unused

	E->sprite.frame.w = E->sprite.image->w / E->sprite.maxframe;
	E->sprite.frame.h = E->sprite.image->h / 2; //2=Nb de ligne(g/d)

	E->posEntite.x = 0;
	E->posEntite.y = 0;

	srand(time(NULL));
	E->posMin.x = rand() % 200 + E->posEntite.x; //+ position Hero
	E->posMax.x = rand() % 200 + E->posMin.x;
}
void animation_entite(entite *E)
{
	static int tempsActuel = 0;
	static int tempsPrecedent = 0;

	switch (E->state)
	{
	case (IDLE):
	{
		E->sprite.image = IMG_Load("img/es/walk2.png");
		E->sprite.maxframe = 5;
		break;
	}
	case (WALK):
	{
		E->sprite.image = IMG_Load("img/es/walk2.png");
		E->sprite.maxframe = 5;
		break;
	}
	}
	E->sprite.frame.y = E->Direction * E->sprite.frame.h; // nb =  E->Direction * E->sprite.frame.h
	tempsActuel = SDL_GetTicks();
	if (tempsActuel - tempsPrecedent > 50)
	{
		if (E->sprite.frame.x == E->sprite.image->w - E->sprite.frame.w)
			E->sprite.frame.x = 0;
		else
			E->sprite.frame.x += E->sprite.frame.w;
		tempsPrecedent = tempsActuel;
	}
}
void afficher_entite(entite *E, SDL_Surface *screen)
{
	SDL_BlitSurface(E->sprite.image, &E->sprite.frame, screen, &E->posEntite);
}
void deplacer_alea(entite *E)
{
	if (E->posEntite.x > E->posMax.x)
		E->Direction = 0;
	if (E->posEntite.x < E->posMin.x)
		E->Direction = 1;
	if (E->Direction == 0)
		(E->posEntite.x)--;
	if (E->Direction == 1)
		(E->posEntite.x)++;
}
void free_entite(entite *E)
{
	SDL_FreeSurface(E->sprite.image);
}
/*
int colisionBoundingBox(entite *E, Hero *h)
{

  if ((h->position.x + h->position.w < E->posEntite.x) || (h->position.x > E->posEntite.x + E->posEntite.w) || (h->position.y + h->position.h < E->posEntite.y) || (h->position.y > E->posEntite.y + E->posEntite.h))
  {
    return 0;
  }
  else
  {
    return 1;
  }
}*/