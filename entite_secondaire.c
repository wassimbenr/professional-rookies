#include "entite_secondaire.h"
#include "colision.h"

void initialiser_entite(entite *E)
{
	E->sprite_entite.image = IMG_Load("img/es/walk.png");
	E->sprite_entite.maxframe = 5;
	E->sprite_entite.frame.x = 0;
	E->sprite_entite.frame.y = 0; //2=Nb de ligne(g/d)
	E->sprite_entite.frame.w = E->sprite_entite.image->w / E->sprite_entite.maxframe;
	E->sprite_entite.frame.h = E->sprite_entite.image->h / 2; //2=Nb de ligne(g/d)
	E->type = ENTITE;
	E->state_entite = WALK_entite;
	E->position.x = 100;
	E->position.y = GROUND_LEVEL;
	E->direction_entite = 1;
	E->type = 0;
	E->sprite_entite.curframe = 0; //unused
	srand(time(NULL));
	E->posMin.x = rand() % 200 + 100 + E->position.x; //+ position Hero
	E->posMax.x = rand() % 200 + E->posMin.x;
}
void animer_entite(entite *E)
{
	static int tempsActuel = 0;
	static int tempsPrecedent = 0;

	switch (E->state_entite)
	{
	case (DIE_entite):
	{
		E->sprite_entite.image = IMG_Load("img/es/Die.png");
		E->sprite_entite.maxframe = 4;
		break;
	}
	case (WALK_entite):
	{
		E->sprite_entite.image = IMG_Load("img/es/walk.png");
		E->sprite_entite.maxframe = 5;
		break;
	}
	case (FOLLOW_entite):
	{
		E->sprite_entite.image = IMG_Load("img/es/walk.png");
		E->sprite_entite.maxframe = 5;
		break;
	}
	case (ATTACK_entite):
	{
		E->sprite_entite.image = IMG_Load("img/es/attack.png");
		E->sprite_entite.maxframe = 3;
		break;
	}
	}
	E->sprite_entite.frame.w = E->sprite_entite.image->w / E->sprite_entite.maxframe;
	E->sprite_entite.frame.y = E->direction_entite * E->sprite_entite.frame.h; // nb =  E->direction * E->sprite_entite.frame.h
	tempsActuel = SDL_GetTicks();
	if (tempsActuel - tempsPrecedent > 200)
	{
		if (E->sprite_entite.frame.x == E->sprite_entite.image->w - E->sprite_entite.frame.w)
			E->sprite_entite.frame.x = 0;
		else
			E->sprite_entite.frame.x += E->sprite_entite.frame.w;
		tempsPrecedent = tempsActuel;
	}
	printf("%d", E->sprite_entite.frame.x);
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
void attack_entite(entite *E, hero *h)
{
	static int tempsActuel = 0;
	static int tempsPrecedent = -2000;
	E->state_entite = ATTACK_entite;
	if (collision(E, h) && (h->state != KICK || h->state != PUNCH))
	{
		tempsActuel = SDL_GetTicks();
		if (tempsActuel - tempsPrecedent >= 2000)
		{
			h->state = DAMAGE;
			h->vie_hero.nb_vie--;
			tempsPrecedent = tempsActuel;
		}
	}
	if (E->position.x >= h->position.x)
	{
		E->direction_entite = 0;
		E->position.x -= 2;
	}
	else if (E->position.x < h->position.x)
	{
		E->direction_entite = 1;
		E->position.x += 2;
	}
}
void input_ennemi(entite *E, hero *h)
{
	switch (E->state_entite)
	{
	case WALK_entite:
		//if (E->posMin.x <= h->position.x)
		E->state_entite = FOLLOW_entite;
		update_entite(E, h);
		break;
	case FOLLOW_entite:
		if (collision(E, h) == 0)
			E->state_entite = ATTACK_entite;
		update_entite(E, h);
		break;
	case ATTACK_entite:
		if (E->position.x - h->position.x != 0)
			E->state_entite = FOLLOW_entite;
		update_entite(E, h);
		break;
	}
}
void update_entite(entite *E, hero *h)
{
	switch (E->state_entite)
	{
	case WALK_entite:
		//deplacer_alea(E);
		animer_entite(E);
		break;
	case FOLLOW_entite:
		attack_entite(E, h);
		animer_entite(E);
		break;
	case ATTACK_entite:
		animer_entite(E);
		break;
	}
}
void afficher_entite(entite *E, SDL_Surface *screen)
{
	SDL_BlitSurface(E->sprite_entite.image, &E->sprite_entite.frame, screen, &E->position);
}
void free_entite(entite *E)
{
	SDL_FreeSurface(E->sprite_entite.image);
}