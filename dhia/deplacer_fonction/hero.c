#include "hero.h"

void initialiser_hero(hero *h, char name[20])
{
	char image_load[30] = "";
	h->position.x = 0;
	h->position.y = GROUND_LEVEL;

	h->direction = RIGHT;
	h->movement = IDLE;

	strcpy(image_load, "./img/hero/");
	strcat(image_load, name);
	strcat(image_load, ".png");
	h->sprite.image = IMG_Load(image_load);

	h->sprite.frame.x = 0;
	h->sprite.frame.y = 0;

	h->sprite.frame.w = h->sprite.image->w / 5;
	h->sprite.frame.h = h->sprite.image->h / 7;

	h->sprite.curframe = 0;

	h->acceleration=0;
	h->tanguiza=0;
}

void afficher_hero(hero *h, SDL_Surface *screen)
{
	SDL_BlitSurface(h->sprite.image, &h->sprite.frame, screen, &h->position);
}
void animer_hero(hero *h, movement movement)
{
	static int tempsActuel = 0;
	static int tempsPrecedent = 0;

	switch (movement)
	{
	case IDLE:
		h->sprite.frame.y = 0;
		h->sprite.maxframe = 3;
		break;
	case WALK_RIGHT:
		h->sprite.frame.y = h->sprite.frame.h;
		h->sprite.maxframe = 4;
		h->movement = WALK_RIGHT;
		h->direction = RIGHT;
		break;
	case WALK_LEFT:
		h->sprite.frame.y = h->sprite.frame.h;
		h->sprite.maxframe = 4;
		h->movement = WALK_LEFT;
		h->direction = LEFT;
		break;
	case JUMP:
		h->sprite.frame.y = 2 * h->sprite.frame.h;
		h->sprite.maxframe = 3;
		h->movement = JUMP;
		break;
	case PUNCH:
		h->sprite.frame.y = 3 * h->sprite.frame.h;
		h->sprite.maxframe = 4;
		h->movement = PUNCH;
		break;
	case KICK:
		h->sprite.frame.y = 4 * h->sprite.frame.h;
		h->sprite.maxframe = 4;
		h->movement = KICK;
		break;
	case HIT:
		h->sprite.frame.y = 5 * h->sprite.frame.h;
		h->sprite.maxframe = 4;
		h->movement = HIT;
		break;
	case DIE:
		h->sprite.frame.y = 6 * h->sprite.frame.h;
		h->sprite.maxframe = 3;
		h->movement = DIE;
		break;
	}

	if (h->direction == RIGHT)
		h->sprite.image = IMG_Load("./img/hero/safwen_right.png");
	if (h->direction == LEFT)
		h->sprite.image = IMG_Load("./img/hero/safwen_left.png");

	tempsActuel = SDL_GetTicks();
	if (tempsActuel - tempsPrecedent > 200)
	{
		if (h->sprite.curframe >= h->sprite.maxframe)
		{
			h->sprite.curframe = 0;
			if (h->movement != WALK_RIGHT && h->movement != WALK_LEFT)
				h->movement = IDLE; //to not interrupt animation (but can be interrupted with SDL_KEYUP)
		}

		h->sprite.frame.x = h->sprite.curframe * h->sprite.frame.w;
		tempsPrecedent = tempsActuel;
		h->sprite.curframe += 1;
	}
}

void deplacer_hero(hero *h)
{
	static int timeStepMs = 20;
	static int timeLastMs, timeAccumulatedMs, timeDeltaMs, timeCurrentMs = 0;


	static int current_ground_position;
	current_ground_position = h->position.y;

	if (h->collision_DOWN)
		current_ground_position = h->position.y;

	timeLastMs = timeCurrentMs;
	timeCurrentMs = SDL_GetTicks();
	timeDeltaMs = timeCurrentMs - timeLastMs;
	timeAccumulatedMs += timeDeltaMs;

	while (timeAccumulatedMs >= timeStepMs)
	{
		h->test = 0;
		Uint8 *keystates = SDL_GetKeyState(NULL);
		if (keystates[SDLK_UP]) // || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)))
		{
			if (h->position.y > current_ground_position - JUMP_HEIGHT && h->tanguiza == 0 && !h->collision_UP)
			{
				animer_hero(h, JUMP);
				h->position.y -= 7;
			}
			else if (h->position.y == current_ground_position - JUMP_HEIGHT || (h->tanguiza == 1 && !h->collision_DOWN))
			{
				animer_hero(h, JUMP);
				h->position.y += 7;
				h->tanguiza = 1;
				h->test = 1;
			}
		}
		if (keystates[SDLK_RIGHT]) //|| (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && (e.motion.x > h->position.x)))
		{
			if (!h->collision_DOWN && !h->collision_RIGHT)
			{
				h->position.x += 4 + h->acceleration;
			}
			else if (h->collision_DOWN && !h->collision_RIGHT)
			{
				h->position.x += 5 + h->acceleration;
				animer_hero(h, WALK_RIGHT);
				if (h->acceleration < 5)
					h->acceleration += 0.1;
			}
		}

		if (keystates[SDLK_LEFT]) //|| (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && (e.motion.x < h->position.x)))
		{
			if (!h->collision_DOWN && !h->collision_LEFT)
			{
				h->position.x -= 4 + h->acceleration;
				if (h->acceleration < 5)
					h->acceleration += 0.1;
				if (h->position.x < 0)
					h->position.x = 0;
			}
			else if (h->collision_DOWN && !h->collision_LEFT)
			{
				h->position.x -= 5 + h->acceleration;
				animer_hero(h, WALK_LEFT);
				if (h->acceleration < 5)
					h->acceleration += 0.1;
				if (h->position.x < 0)
					h->position.x = 0;
			}
		}
		if (!h->test && h->tanguiza == 1 && !h->collision_DOWN)
			h->position.y += 7;
		else if (h->collision_DOWN)
			h->tanguiza = 0;
		if (!h->collision_DOWN && !keystates[SDLK_UP])
			h->position.y += 7;

		/*while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_MOUSEBUTTONUP:
				if (e.button.button == SDL_BUTTON_RIGHT)
				{
					if ((!h->collision_DOWN) && (!h->test))
					{
						h->position.y += 7;
						h->tanguiza = 1;
					}
					else if (h->collision_DOWN)
						h->tanguiza = 0;
					break;
				}
				if (e.button.button == SDL_BUTTON_LEFT)
					h->acceleration = 0;
				break;
			case SDL_KEYUP:
				if (e.key.keysym.sym == SDLK_UP)
				{
					if ((!h->collision_DOWN) && (!h->test))
					{
						h->position.y += 7;
						h->tanguiza = 1;
					}
					else if (h->collision_DOWN)
						h->tanguiza = 0;
					break;
				}
				if (e.key.keysym.sym == SDLK_RIGHT || (e.key.keysym.sym == SDLK_LEFT))
				{
					h->acceleration = 0;
				}
				if (h->movement == WALK_RIGHT || h->movement == WALK_LEFT)
					h->movement = IDLE;
				break;
			}
		}*/
		timeAccumulatedMs -= timeStepMs;
	}
}

void free_hero(hero *h)
{
	SDL_FreeSurface(h->sprite.image);
}