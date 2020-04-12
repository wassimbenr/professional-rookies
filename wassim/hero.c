#include "hero.h"
#include "defs.h"
void initialiser_hero(entite *h)
{
	h->position.x = 0;
	h->position.y = 220;

	h->direction = RIGHT;
	h->state = IDLE;

	h->sprite.image = IMG_Load("./img/hero/safwen_right.png");

	h->sprite.frame.x = 0;
	h->sprite.frame.y = 0;

	h->sprite.frame.w = h->sprite.image->w / 5;
	h->sprite.frame.h = h->sprite.image->h / 7;

	h->sprite.curframe = 0;
}
void afficher_hero(entite *h, SDL_Surface *screen)
{
	SDL_BlitSurface(h->sprite.image, &h->sprite.frame, screen, &h->position);
}
void animer_hero(entite *h, state state)
{
	static int tempsActuel = 0;
	static int tempsPrecedent = 0;

	if (h->direction == RIGHT)
		h->sprite.image = IMG_Load("./img/hero/safwen_right.png");
	if (h->direction == LEFT)
		h->sprite.image = IMG_Load("./img/hero/safwen_left.png");

	switch (state)
	{
	case IDLE:
		h->sprite.frame.y = 0;
		h->sprite.maxframe = 3;
		break;
	case WALK:
		h->sprite.frame.y = h->sprite.frame.h;
		h->sprite.maxframe = 4;
		h->state = WALK;
		break;
	case JUMP:
		h->sprite.frame.y = 2 * h->sprite.frame.h;
		h->sprite.maxframe = 2;
		h->state = JUMP;
		break;
	case PUNCH:
		h->sprite.frame.y = 3 * h->sprite.frame.h;
		h->sprite.maxframe = 3;
		h->state = PUNCH;
		break;
	case KICK:
		h->sprite.frame.y = 4 * h->sprite.frame.h;
		h->sprite.maxframe = 3;
		h->state = KICK;
		break;
	case DAMAGE:
		h->sprite.frame.y = 5 * h->sprite.frame.h;
		h->sprite.maxframe = 4;
		h->state = DAMAGE;
		break;
	case DIE:
		h->sprite.frame.y = 6 * h->sprite.frame.h;
		h->sprite.maxframe = 2;
		h->state = DIE;
		break;
	}
	tempsActuel = SDL_GetTicks();
	if (tempsActuel - tempsPrecedent > 200)
	{
		if (h->sprite.curframe >= h->sprite.maxframe)
		{
			h->sprite.curframe = 0;
			if (h->state != WALK)
				h->state = IDLE; //to not interrupt animation (but can be interrupted with SDL_KEYUP)
		}

		h->sprite.frame.x = h->sprite.curframe * h->sprite.frame.w;
		tempsPrecedent = tempsActuel;
		h->sprite.curframe += 1;
	}
}

void free_hero(entite *h)
{
	SDL_FreeSurface(h->sprite.image);
}