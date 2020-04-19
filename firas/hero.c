#include "hero.h"

void initialiser_hero(hero *h, char name[20])
{
	char image_load[40] = "";
	h->position.x = 0;
	h->position.y = GROUND_LEVEL;

	h->current_ground_position = h->position.y;

	h->direction = RIGHT;
	h->state = IDLE;

	//load function
	strcpy(image_load, "./img/hero/");
	strcat(image_load, name);
	if (h->direction == RIGHT)
		strcat(image_load, "_right");
	else if (h->direction == LEFT)
		strcat(image_load, "_left");
	strcat(image_load, ".png");
	h->sprite.image = IMG_Load(image_load);
	//end load function
	h->sprite.frame.x = 0;
	h->sprite.frame.y = 0;

	h->sprite.frame.w = h->sprite.image->w / 5;
	h->sprite.frame.h = h->sprite.image->h / 7;

	h->sprite.curframe = 0;
}

void afficher_hero(hero h, SDL_Surface *screen)
{
	SDL_BlitSurface(h.sprite.image, &h.sprite.frame, screen, &h.position);
}
void animer_hero(hero *h, state movement)
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
		h->state = WALK_RIGHT;
		h->direction = RIGHT;
		break;
	case WALK_LEFT:
		h->sprite.frame.y = h->sprite.frame.h;
		h->sprite.maxframe = 4;
		h->state = WALK_LEFT;
		h->direction = LEFT;
		break;
	case JUMP:
		h->sprite.frame.y = 2 * h->sprite.frame.h;
		h->sprite.maxframe = 2;
		h->state = JUMP;
		break;
	case PUNCH:
		h->sprite.frame.y = 3 * h->sprite.frame.h;
		h->sprite.maxframe = 4;
		h->state = PUNCH;
		break;
	case KICK:
		h->sprite.frame.y = 4 * h->sprite.frame.h;
		h->sprite.maxframe = 4;
		h->state = KICK;
		break;
	case DAMAGE:
		h->sprite.frame.y = 5 * h->sprite.frame.h;
		h->sprite.maxframe = 4;
		h->state = DAMAGE;
		break;
	case DIE:
		h->sprite.frame.y = 6 * h->sprite.frame.h;
		h->sprite.maxframe = 3;
		h->state = DIE;
		break;
	}
	if (h->direction == RIGHT)
		h->sprite.image = IMG_Load("./img/hero/safwen_right.png");
	if (h->direction == LEFT)
		h->sprite.image = IMG_Load("./img/hero/safwen_left.png");
	//because can changed by walking directions
	tempsActuel = SDL_GetTicks();
	if (tempsActuel - tempsPrecedent > 200)
	{
		if (h->sprite.curframe >= h->sprite.maxframe)
		{
			h->sprite.curframe = 0;
			if (h->state != WALK_RIGHT && h->state != WALK_LEFT)
				h->state = IDLE; //to not interrupt animation (but can be interrupted with SDL_KEYUP)
		}
		h->sprite.frame.x = h->sprite.curframe * h->sprite.frame.w;
		tempsPrecedent = tempsActuel;
		h->sprite.curframe += 1;
	}
}
void free_hero(hero *h)
{
	SDL_FreeSurface(h->sprite.image);
}

void deplacer_hero(hero *h, SDL_Event event)
{
	static int timeStepMs = 20;
	static int timeLastMs, timeAccumulatedMs, timeDeltaMs, timeCurrentMs = 0;
	static int current_ground_position;
	static float accel = 0;
	static int tanguiza = -1;

	timeLastMs = timeCurrentMs;
	timeCurrentMs = SDL_GetTicks();
	timeDeltaMs = timeCurrentMs - timeLastMs;
	timeAccumulatedMs += timeDeltaMs;

	while (timeAccumulatedMs >= timeStepMs)
	{
		if (h->collision_DOWN)
			h->current_ground_position = h->position.y;

		Uint8 *keystates = SDL_GetKeyState(NULL);
		if (h->position.y > h->current_ground_position - JUMP_HEIGHT && tanguiza == 0 && !h->collision_UP)
		{
			//animer_hero(h, JUMP);
			h->state=JUMP;

			h->position.y -= JUMP_SPEED;
		}
		if (h->position.y == h->current_ground_position - JUMP_HEIGHT || h->collision_UP)
			tanguiza = 1;
		if (tanguiza == 1 && !h->collision_DOWN)
		{
			//animer_hero(h, JUMP);
			h->state=JUMP;
			h->position.y += JUMP_SPEED;
		}

		if (keystates[SDLK_RIGHT] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && (event.motion.x > h->position.x)))
		{
			if (!h->collision_DOWN && !h->collision_RIGHT)
			{
				h->position.x += 4 + accel;
			}
			else if (h->collision_DOWN && !h->collision_RIGHT)
			{
				h->position.x += 4 + accel;
				
				//animer_hero(h, WALK_RIGHT);
				h->state=WALK_RIGHT;

				
			}
		}
		if (keystates[SDLK_LEFT] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && (event.motion.x < h->position.x)))
		{
			if (!h->collision_DOWN && !h->collision_LEFT)
			{
				h->position.x -= 4 + accel;
				
				if (h->position.x < 0)
					h->position.x = 0;
			}
			else if (h->collision_DOWN && !h->collision_LEFT)
			{
				h->position.x -= 4 + accel;

				h->state=WALK_LEFT;
				//animer_hero(h, WALK_LEFT);

				if (h->position.x < 0)
					h->position.x = 0;
			}
		}

		if (!keystates[SDLK_RIGHT] && !keystates[SDLK_LEFT])
			h->state = IDLE;
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				if (h->collision_DOWN)
					tanguiza = 0;
			}
		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				if (h->collision_UP || h->position.y == h->current_ground_position - JUMP_HEIGHT)
					tanguiza = 1;
			}
			if (event.button.button == SDL_BUTTON_LEFT)
				accel = 0;
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_UP)
				if (h->collision_DOWN)
					tanguiza = 0;
			if (event.key.keysym.sym == SDLK_d)
				//animer_hero(h, PUNCH);
				h->state=PUNCH;

			if (event.key.keysym.sym == SDLK_s)
				//animer_hero(h, KICK);
				h->state=KICK;
		}
		if (event.type == SDL_KEYUP)
		{

			if (event.key.keysym.sym == SDLK_UP)
			{
				if (h->collision_UP || h->position.y == h->current_ground_position - JUMP_HEIGHT)
					tanguiza = 1;
			}
			if (event.key.keysym.sym == SDLK_RIGHT || (event.key.keysym.sym == SDLK_LEFT))
			{
				accel = 0;
			}
			if (h->state == WALK_RIGHT || h->state == WALK_LEFT)
				h->state = IDLE;
		}
		timeAccumulatedMs -= timeStepMs;
	}
}