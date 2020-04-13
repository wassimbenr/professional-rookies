#include "entite_secondaire.h"
#include "defs.h"

void init_entite(entite *E)
{
	E->sprite.image = IMG_Load("img/es/walk.png");
	E->sprite.frame.x = 0;
	E->sprite.frame.y = 0;
	E->sprite.maxframe = 5; //Nb de colone
	E->sprite.frame.w = E->sprite.image->w / E->sprite.maxframe;
	E->sprite.frame.h = E->sprite.image->h / 2; //2=Nb de ligne(g/d)
	E->type = ENTITE;
	E->state = WALK;
	E->position.x = SCREEN_WIDTH / 2;
	E->position.y = SCREEN_HEIGHT / 2;
	//E->direction = 1;
	
	E->direction = RIGHT;
	E->type = 0;
	E->sprite.curframe = 0; //unused
	srand(time(NULL));
	E->posMin.x = rand() % 200 + E->position.x; //+ position Hero
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
		E->sprite.image = IMG_Load("img/es/idle.png");
		E->sprite.maxframe = 4;
		break;
	}
	case (WALK):
	{
		E->sprite.image = IMG_Load("img/es/walk.png");
		E->sprite.maxframe = 5;
		break;
	}
	case (DIE):
	{
		E->sprite.image = IMG_Load("img/es/Die.png");
		E->sprite.maxframe = 4;
		break;
	}
	case (ATTACK):
	{
		E->sprite.image = IMG_Load("img/es/attack.png");
		E->sprite.maxframe = 3;
		break;
	}
	case (DAMAGE):
	{
		E->sprite.image = IMG_Load("img/es/Damage.png");
		E->sprite.maxframe = 5;
		break;
	}
	case (JUMP):
	{
		E->sprite.image = IMG_Load("img/es/jump.png");
		E->sprite.maxframe = 3;
		break;
	}
	}
	E->sprite.frame.y = E->direction * E->sprite.frame.h; // nb =  E->direction * E->sprite.frame.h
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
void deplacer_alea(entite *E)
{
	if (E->position.x > E->posMax.x)
		E->direction = 0;
	if (E->position.x < E->posMin.x)
		E->direction = 1;
	if (E->direction == 0)
		(E->position.x)--;
	if (E->direction == 1)
		(E->position.x)++;
}
void afficher_entite(entite *E, SDL_Surface *screen)
{
	SDL_BlitSurface(E->sprite.image, &E->sprite.frame, screen, &E->position);
}
void free_entite(entite *E)
{
	SDL_FreeSurface(E->sprite.image);
}