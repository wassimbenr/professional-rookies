#include "entite_secondaire.h"
#include "collision.h"
#include "background.h"

void initialiser_entite(entite *E)
{
	E->sprite_entite.image = IMG_Load("../img/es/walk.png");
	E->sprite_entite.maxframe = 5;
	E->sprite_entite.frame.x = 0;
	E->sprite_entite.frame.y = 0; //2=Nb de ligne(g/d)
	E->sprite_entite.frame.w = E->sprite_entite.image->w / E->sprite_entite.maxframe;
	E->sprite_entite.frame.h = E->sprite_entite.image->h / 2; //2=Nb de ligne(g/d)
	E->type = ENTITE;
	E->state_entite = WALK_entite;
	E->position.x = 2100;
	E->position.y = 1265;
	E->direction_entite = 1;
	E->type = 0;
	E->sprite_entite.curframe = 0; //unused
	srand(time(NULL));
	E->posMin.x = rand() % 200 + 100 + E->position.x; //+ position Hero
	E->posMax.x = rand() % 100 + E->posMin.x;

	//optim

	E->sprite_entite.image = SDL_DisplayFormat(E->sprite_entite.image);
}
void animer_entite(entite *E)
{
	if (E->sprite_entite.image != NULL)
	{
		static int tempsActuel = 0;
		static int tempsPrecedent = 0;

		switch (E->state_entite)
		{
		case (DIE_entite):
		{
			E->sprite_entite.image = IMG_Load("../img/es/Die.png");
			E->sprite_entite.maxframe = 4;
			break;
		}
		case (WALK_entite):
		{
			E->sprite_entite.image = IMG_Load("../img/es/walk.png");
			E->sprite_entite.maxframe = 5;
			break;
		}
		case (FOLLOW_entite):
		{
			E->sprite_entite.image = IMG_Load("../img/es/attack.png");
			E->sprite_entite.maxframe = 3;
			break;
		}

		//opt
		E->sprite_entite.image = SDL_DisplayFormat(E->sprite_entite.image);
			/*case (ATTACK_entite):
	{
		E->sprite_entite.image = IMG_Load("img/es/attack.png");
		E->sprite_entite.maxframe = 3;
		break;
	}*/
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
	}
}
void deplacer_alea(entite *E)
{
	if (E->sprite_entite.image != NULL)
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
}
void attack_entite(entite *E, hero *h)
{
	if (E->sprite_entite.image != NULL)
	{
		//E->state_entite = FOLLOW_entite;
		if (E->position.x > h->position.x)
		{
			E->direction_entite = 0;
			E->position.x -= 2;
		}
		else if (E->position.x < h->position.x)
		{
			E->direction_entite = 1;
			E->position.x += 2;
		}
		else if (E->position.x == h->position.x)
			E->direction_entite = 0;
		if (collision(E, h) == 1)
		{
			static int tempsActuel = 0;
			static int tempsPrecedent = -2000;
			if ((h->state != KICK && h->state != PUNCH))
			{
				tempsActuel = SDL_GetTicks();
				h->state = DAMAGE;
				if (tempsActuel - tempsPrecedent >= 2000)
				{
					h->vie_hero.nb_vie--;
					tempsPrecedent = tempsActuel;
				}
			}
			if (h->state == PUNCH || h->state == KICK)
			{
				E->state_entite = DIE_entite;
				E->sprite_entite.image = NULL;
			}
			switch (h->vie_hero.nb_vie)
			{
			case 2:
				h->vie_hero.position_heart_c.x = 0;
				break;
			case 1:
				h->vie_hero.position_heart_b.x = 0;
				break;
			case 0:
				h->vie_hero.heart = NULL;
				break;
			}
		}
	}
}
void input_ennemi(entite *E, hero *h)
{
	switch (E->state_entite)
	{
	case WALK_entite:
		deplacer_alea(E);
		if (E->posMin.x <= h->position.x)
			E->state_entite = FOLLOW_entite;
		break;
	case FOLLOW_entite:
		attack_entite(E, h);
		break;
	/*case ATTACK_entite:
		attack_entite(E, h);
		if (E->position.x - h->position.x != 0)
			E->state_entite = FOLLOW_entite;
		break;*/
	case DIE_entite:
		E->state_entite = DIE_entite;
		break;
	}
}
void update_entite(entite *E, hero *h)
{
	switch (E->state_entite)
	{
	case WALK_entite:
		deplacer_alea(E);
		animer_entite(E);
		break;
	case FOLLOW_entite:
		attack_entite(E, h);
		animer_entite(E);
		break;
	case ATTACK_entite:
		attack_entite(E, h);
		animer_entite(E);
		break;
	case DIE_entite:
		animer_entite(E);
		break;
	}
}
void afficher_entite(entite *E, SDL_Surface *screen, background b)
{
	SDL_Rect pos;
	pos.x = E->position.x - b.posCamera.x;
	pos.y = E->position.y - b.posCamera.y;
	SDL_BlitSurface(E->sprite_entite.image, &E->sprite_entite.frame, screen, &pos);
}
void free_entite(entite *E)
{
	SDL_FreeSurface(E->sprite_entite.image);
}

void initialiser_pu(power_up *p, int x, int y)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		printf("%s", Mix_GetError());
	}
	p->click = Mix_LoadWAV("../sfx/coin_pick.wav");

	p->sprite.image = IMG_Load("../img/es/coin_small.png");
	p->sprite.curframe = 0;
	p->sprite.maxframe = 5;

	p->sprite.frame.x = 0;
	p->sprite.frame.y = 0;
	p->sprite.frame.w = p->sprite.image->w / 6;
	p->sprite.frame.h = p->sprite.image->h / 3;

	p->position.x = x;
	p->position.y = y;
}

void animer_pu(power_up *p_1, power_up *p_2)
{
	static int tempsActuel = 0;
	static int tempsPrecedent = 0;

	tempsActuel = SDL_GetTicks();
	if (tempsActuel - tempsPrecedent > 100)
	{
		if (p_1->sprite.curframe >= p_1->sprite.maxframe)
		{
			p_1->sprite.curframe = 0;
			p_2->sprite.curframe = 0;
		}

		p_1->sprite.frame.x = p_1->sprite.curframe * p_1->sprite.frame.w;
		p_1->sprite.curframe += 1;
		p_2->sprite.frame.x = p_2->sprite.curframe * p_2->sprite.frame.w;
		p_2->sprite.curframe += 1;

		tempsPrecedent = tempsActuel;
	}
}

void afficher_pu(power_up p, SDL_Surface *screen, background b)
{
	SDL_Rect pos;
	pos.x = p.position.x - b.posCamera.x;
	pos.y = p.position.y - b.posCamera.y;

	SDL_BlitSurface(p.sprite.image, &p.sprite.frame, screen, &pos);
}

void free_pu(power_up *p)
{
	SDL_FreeSurface(p->sprite.image);
}