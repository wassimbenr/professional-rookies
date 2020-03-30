#include "entite_secondaire.h"
void init_entite(entite *E)
{
	E->Direction = 1;

	E->sprite.image = IMG_Load("img/es/es.png");
	E->sprite.frame.x = 0;
	E->sprite.frame.y = 0;
	E->sprite.maxframe = 4;
	E->sprite.frame.w = (E->sprite.image->w) / E->sprite.maxframe;
	E->sprite.frame.h = (E->sprite.image->h) / E->sprite.maxframe;
	E->sprite.curframe = 0;

	E->position_entite.x = 100;
	E->position_entite.y = 500;

	srand(time(NULL));
	E->posMin.x = rand() % 200 + E->position_entite.x;
	E->posMax.x = rand() % 200 + E->posMin.x;
}
void animation(entite *E)
{
	static int tempsActuel = 0;
	static int tempsPrecedent = 0;

	if (E->Direction == 0) //gauche
	{
		E->sprite.frame.y = 3*E->sprite.frame.h;
	}
	else if (E->Direction == 1)
	{
		E->sprite.frame.y = 2*E->sprite.frame.h;
	}
	tempsActuel = SDL_GetTicks();
	if (tempsActuel - tempsPrecedent > 100)
	{
		if (E->sprite.curframe > E->sprite.maxframe)
			E->sprite.curframe = 0;
		E->sprite.frame.x = E->sprite.curframe * E->sprite.frame.w;
		tempsPrecedent = tempsActuel;
		E->sprite.curframe += 1;
		
	}
}
void afficher_entite(entite *E, SDL_Surface *screen)
{
	SDL_BlitSurface(E->sprite.image, &E->sprite.frame, screen, &E->position_entite);
}
void deplacer_alea(entite *E)
{
	if (E->position_entite.x > E->posMax.x)
		E->Direction = 0;
	if (E->position_entite.x < E->posMin.x)
		E->Direction = 1;
	if (E->Direction == 0)
		(E->position_entite.x)--;
	if (E->Direction == 1)
		(E->position_entite.x)++;
}
void free_entite(entite *E)
{
	SDL_FreeSurface(E->sprite.image);
}