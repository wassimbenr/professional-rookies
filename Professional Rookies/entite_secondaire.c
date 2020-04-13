#include "entite_secondaire.h"
#include "defs.h"

void initialiser_entite(entite *E)
{
	E->sprite_entite.image = IMG_Load("img/es/WALK_entite.png");
	E->sprite_entite.frame.x = 0;
	E->sprite_entite.frame.y = 0;
	E->sprite_entite.maxframe = 5; //Nb de colone
	E->sprite_entite.frame.w = E->sprite_entite.image->w / E->sprite_entite.maxframe;
	E->sprite_entite.frame.h = E->sprite_entite.image->h / 2; //2=Nb de ligne(g/d)
	E->type = ENTITE;
	E->state_entite = WALK_entite;
	E->position.x = SCREEN_WIDTH / 2;
	E->position.y = SCREEN_HEIGHT / 2;
	//E->direction = 1;
	
	E->direction_entite = 1;
	E->type = 0;
	E->sprite_entite.curframe = 0; //unused
	srand(time(NULL));
	E->posMin.x = rand() % 200 + E->position.x; //+ position Hero
	E->posMax.x = rand() % 200 + E->posMin.x;
}
void animer_entite(entite *E)
{
	static int tempsActuel = 0;
	static int tempsPrecedent = 0;

	switch (E->state_entite)
	{
	case (WALK_entite):
	{
		E->sprite_entite.image = IMG_Load("img/es/WALK_entite.png");
		E->sprite_entite.maxframe = 5;
		break;
	}
	case (DIE_entite):
	{
		E->sprite_entite.image = IMG_Load("img/es/Die.png");
		E->sprite_entite.maxframe = 4;
		break;
	}
	case (ATTACK_entite):
	{
		E->sprite_entite.image = IMG_Load("img/es/attack.png");
		E->sprite_entite.maxframe = 3;
		break;
	}
	}
	E->sprite_entite.frame.y = E->direction_entite * E->sprite_entite.frame.h; // nb =  E->direction * E->sprite_entite.frame.h
	tempsActuel = SDL_GetTicks();
	if (tempsActuel - tempsPrecedent > 50)
	{
		if (E->sprite_entite.frame.x == E->sprite_entite.image->w - E->sprite_entite.frame.w)
			E->sprite_entite.frame.x = 0;
		else
			E->sprite_entite.frame.x += E->sprite_entite.frame.w;
		tempsPrecedent = tempsActuel;
	}
}
void deplacer_alea(entite *E)
{
	if (E->position.x > E->posMax.x)
		E->direction_entite = 0;
	if (E->position.x < E->posMin.x)
		E->direction_entite = 1;
	if (E->direction_entite == 0)
		(E->position.x)--;
	if (E->direction_entite == 1)
		(E->position.x)++;
}
void afficher_entite(entite *E, SDL_Surface *screen)
{
	SDL_BlitSurface(E->sprite_entite.image, &E->sprite_entite.frame, screen, &E->position);
}
void free_entite(entite *E)
{
	SDL_FreeSurface(E->sprite_entite.image);
}