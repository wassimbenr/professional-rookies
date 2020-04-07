#include "entite_secondaire.h"
void init_entite(entite *E)
{
	E->Direction = 1;

	E->state = WAITING;

	E->sprite.image = IMG_Load("img/es/es.png"); //initialiser la premiere sprite
	E->sprite.frame.x = 0;
	E->sprite.frame.y = 0;
	E->sprite.maxframe = 4; //Nb de colone
	E->sprite.curframe = 0;
	E->sprite.frame.w = E->sprite.image->w / E->sprite.maxframe;
	E->sprite.frame.h = E->sprite.image->h / E->sprite.maxframe; //2=Nb de ligne(g/d)

	E->posEntite.x = 100;
	E->posEntite.y = 500;

	srand(time(NULL));
	E->posMin.x = rand() % 200 + E->posEntite.x;
	E->posMax.x = rand() % 200 + E->posMin.x;
}
void animation(entite *E)
{
	static int tempsActuel = 0;
	static int tempsPrecedent = 0;
	if (E->Direction == 0) //gauche
	{
		E->sprite.frame.y = 3 * E->sprite.frame.h;
	}
	else if (E->Direction == 1)
	{
		E->sprite.frame.y = 2 * E->sprite.frame.h;
	}
	tempsActuel = SDL_GetTicks();
	if (tempsActuel - tempsPrecedent > 50)
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