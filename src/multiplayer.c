/**
 * @file multiplayer.c
 */
#include "multiplayer.h"

void initialiser_hero2(hero *h, char name[20])
{
	if (TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	char image_load[40] = "";
	char score_str[10] = "";
	h->position.x = 550;
	h->position.y = 1565;

	h->current_ground_position = h->position.y;

	h->direction = RIGHT;
	h->state = IDLE;

	//load function
	strcpy(image_load, "../img/hero/");
	strcat(image_load, name);
	if (h->direction == RIGHT)
		strcat(image_load, "_right");
	else if (h->direction == LEFT)
		strcat(image_load, "_left");
	strcat(image_load, ".png");
	h->sprite.image = IMG_Load(image_load);

	//printf("%s\n", image_load);
	//end load function
	h->sprite.frame.x = 0;
	h->sprite.frame.y = 0;

	h->sprite.frame.w = h->sprite.image->w / 5;
	h->sprite.frame.h = h->sprite.image->h / 7;

	h->sprite.curframe = 0;

	h->vie_hero.nb_vie = 3;
	h->score_hero.valeur_score = 0;

	h->vie_hero.heart = IMG_Load("../img/hero/heart1.png");

	h->vie_hero.position_heart_a.x = 0;
	h->vie_hero.position_heart_a.y = SCREEN_HEIGHT / 2;
	h->vie_hero.position_heart_b.x = 50;
	h->vie_hero.position_heart_b.y = SCREEN_HEIGHT / 2;
	h->vie_hero.position_heart_c.x = 100;
	h->vie_hero.position_heart_c.y = SCREEN_HEIGHT / 2;

	h->score_hero.couleurNoire.b = 255;
	h->score_hero.couleurNoire.g = 255;
	h->score_hero.couleurNoire.r = 255;
	h->score_hero.score_font = TTF_OpenFont("../fonts/8bit.ttf", 15);
	snprintf(score_str, 10, "%d", h->score_hero.valeur_score);
	h->score_hero.texte_score = TTF_RenderText_Blended(h->score_hero.score_font, score_str, h->score_hero.couleurNoire);
	h->score_hero.position_texte.x = SCREEN_WIDTH - h->vie_hero.heart->w;
	h->score_hero.position_texte.y = 10;
}
void initialiser_background1(background *b)
{
	b->image = IMG_Load("../img/background/1.jpg");
	b->background_mask = IMG_Load("../img/background/2.jpg");

	b->posCamera.x = 400;
	b->posCamera.y = 900;
	b->posCamera.w = SCREEN_WIDTH;
	b->posCamera.h = SCREEN_HEIGHT / 2;

	b->position_background_mask.x = 400;
	b->position_background_mask.y = 900;
	b->position_background_mask.w = SCREEN_WIDTH;
	b->position_background_mask.h = SCREEN_HEIGHT / 2;
}
void animer_platforme2(platforme *p, int x)
{
	static int tempsActuel = 0;
	static int tempsPrecedent = 0;
	static int sens = 1;
	if (x == 0)
	{
		tempsActuel = SDL_GetTicks();
		if (tempsActuel - tempsPrecedent > 10)
		{
			p->position.x += 1 * sens;
			tempsPrecedent = tempsActuel;
		}
		if (p->position.x >= 1380)
			sens = -1;
		if (p->position.x <= 1180)
			sens = 1;
	}
	else if (x == 1)
	{
		tempsActuel = SDL_GetTicks();
		if (tempsActuel - tempsPrecedent > 10)
		{
			p->position.y += 1 * sens;
			tempsPrecedent = tempsActuel;
		}
		if (p->position.y >= 1380)
			sens = -1;
		if (p->position.y <= 1180)
			sens = 1;
	}
}
void initialiser_background2(background *b)
{
	b->image = IMG_Load("../img/background/1.jpg");
	b->background_mask = IMG_Load("../img/background/2.jpg");

	b->posCamera.x = 400;
	b->posCamera.y = 900;
	b->posCamera.w = SCREEN_WIDTH;
	b->posCamera.h = SCREEN_HEIGHT / 2;

	b->position_background_mask.x = 400;
	b->position_background_mask.y = 900;
	b->position_background_mask.w = SCREEN_WIDTH;
	b->position_background_mask.h = SCREEN_HEIGHT / 2;
}
void deplacer_hero1(hero *h, background *b, int *Jcontinuer, character c, platforme p)
{
	if (h->sprite.image != NULL)
	{
		int timeStepMs = 10; //if 20 it ruins mvt for some reason
		static int timeLastMs, timeAccumulatedMs, timeDeltaMs, timeCurrentMs = 0;
		static int current_ground_position;
		static float accel = 0;
		static int tanguiza = -1;

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
		{
			printf("%s", Mix_GetError());
		}
		Mix_Chunk *punch_sound;
		punch_sound = Mix_LoadWAV("../sfx/punch.wav");

		SDL_Event event;

		timeLastMs = timeCurrentMs;
		timeCurrentMs = SDL_GetTicks();
		timeDeltaMs = timeCurrentMs - timeLastMs;
		timeAccumulatedMs += timeDeltaMs;

		if (h->collision_DOWN)
		{
			h->current_ground_position = h->position.y;
			if (h->state != KICK && h->state != PUNCH)
				h->state = IDLE;
		}

		if (timeAccumulatedMs >= timeStepMs)
		{
			if (b->posCamera.x < b->image->w - SCREEN_WIDTH)
			{
				b->posCamera.x = (h->position.x + 5 * h->sprite.frame.w) - SCREEN_WIDTH;
			}
			if (b->posCamera.y < b->image->h - (SCREEN_HEIGHT / 2))
			{
				b->posCamera.y = (h->position.y + 6 * h->sprite.frame.h) - (SCREEN_HEIGHT);
			}
			if (b->posCamera.x < 0)
				b->posCamera.x = 1;
			if (b->posCamera.y < 0)
				b->posCamera.y = 1;

			Uint8 *keystates = SDL_GetKeyState(NULL);
			if (h->position.y > h->current_ground_position - JUMP_HEIGHT && tanguiza == 0 && !h->collision_UP)
			{
				animer_hero(h, JUMP, c);
				h->position.y -= JUMP_SPEED;
			}
			if (h->position.y == h->current_ground_position - JUMP_HEIGHT || h->collision_UP)
				tanguiza = 1;
			if (tanguiza == 1 && !h->collision_DOWN)
			{

				animer_hero(h, FALLING, c);
				h->position.y += JUMP_SPEED;
			}
			if (keystates[SDLK_RIGHT] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && (event.motion.x > h->position.x)))
			{
				h->direction = RIGHT;
				CollisionParfaite2(h, *b, p);

				if (!h->collision_DOWN && !h->collision_RIGHT)
				{
					h->position.x += 4 + accel;
				}
				else if (h->collision_DOWN && !h->collision_RIGHT)
				{

					h->position.x += 4 + accel;
					animer_hero(h, WALK_RIGHT, c);

					//animer_hero(h, WALK_RIGHT,c);
					/*if (accel < 5)
					accel += 0.1;*/
				}
			}
			if (keystates[SDLK_LEFT] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && (event.motion.x < h->position.x)))
			{
				h->direction = LEFT;
				CollisionParfaite2(h, *b, p);
				if (!h->collision_DOWN && !h->collision_LEFT)
				{

					h->position.x -= 4 + accel;
					/*if (accel < 5)
					accel += 0.1;*/
					if (h->position.x < 0)
						h->position.x = 0;
				}
				else if (h->collision_DOWN && !h->collision_LEFT)
				{
					h->position.x -= 4 + accel;
					animer_hero(h, WALK_LEFT, c);
					//animer_hero(h, WALK_LEFT,c);
					/*if (accel < 5)
					accel += 0.1;*/
					if (h->position.x < 0)
						h->position.x = 0;
				}
			}
			SDL_EnableKeyRepeat(2, 2);
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					(*Jcontinuer) = 0;
					break;
				case SDL_MOUSEBUTTONDOWN:

					if (event.button.button == SDL_BUTTON_RIGHT)
					{
						if (h->collision_DOWN)
						{
							tanguiza = 0;
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_RIGHT)
					{
						if (h->collision_UP || h->position.y == h->current_ground_position - JUMP_HEIGHT)
						{
							tanguiza = 1;
						}
					}
					else if (event.button.button == SDL_BUTTON_LEFT)
						accel = 0;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						(*Jcontinuer) = 0;
						break;
					case SDLK_UP:
						if (h->collision_DOWN)
						{
							tanguiza = 0;
						}

						break;
					case SDLK_x:
						Mix_PlayChannel(-1, punch_sound, 0);
						animer_hero(h, PUNCH, c);
						break;
					case SDLK_c:
						Mix_PlayChannel(-1, punch_sound, 0);
						animer_hero(h, KICK, c);
						break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
					case SDLK_UP:
						if (h->collision_UP || h->position.y == h->current_ground_position - JUMP_HEIGHT)
						{
							tanguiza = 1;
						}
						break;
					case SDLK_RIGHT:
					case SDLK_LEFT:
					{
						accel = 0;
					}
					break;
					}
					if (h->state == WALK_RIGHT || h->state == WALK_LEFT)
						h->state = IDLE;
					break;
				}
			}
			timeAccumulatedMs -= timeStepMs;
		}
	}
}
void afficher_hero1(hero h, SDL_Surface *screen, background b, hero h2)
{
	if (h.sprite.image != NULL)
	{
		SDL_Rect pos;
		if (TTF_Init() == -1)
		{
			fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
			exit(EXIT_FAILURE);
		}
		char score_str[10];
		switch (h.vie_hero.nb_vie)
		{
		case 2:
			h.vie_hero.position_heart_c.x = 0;
			break;
		case 1:
			h.vie_hero.position_heart_b.x = 0;
			break;
		case 0:
			h.vie_hero.heart = NULL;
			break;
		}

		pos.x = h.position.x - b.posCamera.x;
		pos.y = h.position.y - b.posCamera.y;

		SDL_BlitSurface(h.sprite.image, &h.sprite.frame, screen, &pos);

		pos.x = h2.position.x - b.posCamera.x;
		pos.y = h2.position.y - b.posCamera.y;

		SDL_BlitSurface(h.sprite.image, &h.sprite.frame, screen, &pos);

		SDL_BlitSurface(h.vie_hero.heart, NULL, screen, &h.vie_hero.position_heart_a);
		SDL_BlitSurface(h.vie_hero.heart, NULL, screen, &h.vie_hero.position_heart_b);
		SDL_BlitSurface(h.vie_hero.heart, NULL, screen, &h.vie_hero.position_heart_c);

		snprintf(score_str, 10, "%d", h.score_hero.valeur_score);
		h.score_hero.texte_score = TTF_RenderText_Blended(h.score_hero.score_font, score_str, h.score_hero.couleurNoire);
		SDL_BlitSurface(h.score_hero.texte_score, NULL, screen, &h.score_hero.position_texte);
	}
}
void afficher_hero2(hero h, SDL_Surface *screen, background b, hero h2)
{
	if (h.sprite.image != NULL)
	{
		SDL_Rect pos;
		if (TTF_Init() == -1)
		{
			fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
			exit(EXIT_FAILURE);
		}
		char score_str[10];
		switch (h.vie_hero.nb_vie)
		{
		case 2:
			h.vie_hero.position_heart_c.x = 0;
			break;
		case 1:
			h.vie_hero.position_heart_b.x = 0;
			break;
		case 0:
			h.vie_hero.heart = NULL;
			break;
		}

		pos.x = h.position.x - b.posCamera.x;
		pos.y = h.position.y - b.posCamera.y + (SCREEN_HEIGHT / 2);

		SDL_BlitSurface(h.sprite.image, &h.sprite.frame, screen, &pos);

		pos.x = h2.position.x - b.posCamera.x;
		pos.y = h2.position.y - b.posCamera.y + (SCREEN_HEIGHT / 2);

		SDL_BlitSurface(h.sprite.image, &h.sprite.frame, screen, &pos);

		SDL_BlitSurface(h.vie_hero.heart, NULL, screen, &h.vie_hero.position_heart_a);
		SDL_BlitSurface(h.vie_hero.heart, NULL, screen, &h.vie_hero.position_heart_b);
		SDL_BlitSurface(h.vie_hero.heart, NULL, screen, &h.vie_hero.position_heart_c);

		snprintf(score_str, 10, "%d", h.score_hero.valeur_score);
		h.score_hero.texte_score = TTF_RenderText_Blended(h.score_hero.score_font, score_str, h.score_hero.couleurNoire);
		SDL_BlitSurface(h.score_hero.texte_score, NULL, screen, &h.score_hero.position_texte);
	}
}
void deplacer_hero2(hero *h, background *b, int *Jcontinuer, character c, platforme p)
{
	if (h->sprite.image != NULL)
	{
		int timeStepMs = 10; //if 20 it ruins mvt for some reason
		static int timeLastMs, timeAccumulatedMs, timeDeltaMs, timeCurrentMs = 0;
		static int current_ground_position;
		static float accel = 0;
		static int tanguiza = -1;

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
		{
			printf("%s", Mix_GetError());
		}
		Mix_Chunk *punch_sound;
		punch_sound = Mix_LoadWAV("../sfx/punch.wav");

		SDL_Event event;

		timeLastMs = timeCurrentMs;
		timeCurrentMs = SDL_GetTicks();
		timeDeltaMs = timeCurrentMs - timeLastMs;
		timeAccumulatedMs += timeDeltaMs;

		if (h->collision_DOWN)
		{
			h->current_ground_position = h->position.y;
			if (h->state != KICK && h->state != PUNCH)
				h->state = IDLE;
		}

		if (timeAccumulatedMs >= timeStepMs)
		{
			if (b->posCamera.x < b->image->w - SCREEN_WIDTH)
			{
				b->posCamera.x = (h->position.x + 5 * h->sprite.frame.w) - SCREEN_WIDTH;
			}
			if (b->posCamera.y < b->image->h - (SCREEN_HEIGHT / 2))
			{
				b->posCamera.y = (h->position.y + 3 * h->sprite.frame.h) - (SCREEN_HEIGHT / 2);
			}
			if (b->posCamera.x < 0)
				b->posCamera.x = 1;
			if (b->posCamera.y < 0)
				b->posCamera.y = 1;

			Uint8 *keystates = SDL_GetKeyState(NULL);
			if (h->position.y > h->current_ground_position - JUMP_HEIGHT && tanguiza == 0 && !h->collision_UP)
			{
				animer_hero(h, JUMP, c);
				h->position.y -= JUMP_SPEED;
			}
			if (h->position.y == h->current_ground_position - JUMP_HEIGHT || h->collision_UP)
				tanguiza = 1;
			if (tanguiza == 1 && !h->collision_DOWN)
			{

				animer_hero(h, FALLING, c);
				h->position.y += JUMP_SPEED;
			}
			if (keystates[SDLK_d]) //|| (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && (event.motion.x > h->position.x)))
			{
				h->direction = RIGHT;
				CollisionParfaite2(h, *b, p);

				if (!h->collision_DOWN && !h->collision_RIGHT)
				{
					h->position.x += 4 + accel;
				}
				else if (h->collision_DOWN && !h->collision_RIGHT)
				{

					h->position.x += 4 + accel;
					animer_hero(h, WALK_RIGHT, c);

					//animer_hero(h, WALK_RIGHT,c);
					/*if (accel < 5)
					accel += 0.1;*/
				}
			}
			if (keystates[SDLK_q]) //|| (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && (event.motion.x < h->position.x)))
			{
				h->direction = LEFT;
				CollisionParfaite2(h, *b, p);
				if (!h->collision_DOWN && !h->collision_LEFT)
				{

					h->position.x -= 4 + accel;
					/*if (accel < 5)
					accel += 0.1;*/
					if (h->position.x < 0)
						h->position.x = 0;
				}
				else if (h->collision_DOWN && !h->collision_LEFT)
				{
					h->position.x -= 4 + accel;
					animer_hero(h, WALK_LEFT, c);
					//animer_hero(h, WALK_LEFT,c);
					/*if (accel < 5)
					accel += 0.1;*/
					if (h->position.x < 0)
						h->position.x = 0;
				}
			}
			if (keystates[SDLK_z])
			{
				if (h->collision_DOWN)
				{
					tanguiza = 0;
				}
			}
			else if (h->collision_UP || h->position.y == h->current_ground_position - JUMP_HEIGHT)
			{
				tanguiza = 1;
			}
			if (keystates[SDLK_l])
			{
				Mix_PlayChannel(-1, punch_sound, 0);
				animer_hero(h, PUNCH, c);
			}
			if (keystates[SDLK_m])
			{
				Mix_PlayChannel(-1, punch_sound, 0);
				animer_hero(h, KICK, c);
			}

			SDL_EnableKeyRepeat(2, 2);
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					(*Jcontinuer) = 0;
					break;
				case SDL_MOUSEBUTTONDOWN:

					if (event.button.button == SDL_BUTTON_RIGHT)
					{
						if (h->collision_DOWN)
						{
							tanguiza = 0;
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_RIGHT)
					{
						if (h->collision_UP || h->position.y == h->current_ground_position - JUMP_HEIGHT)
						{
							tanguiza = 1;
						}
					}
					else if (event.button.button == SDL_BUTTON_LEFT)
						accel = 0;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						(*Jcontinuer) = 0;
						break;
					case SDLK_z:
						if (h->collision_DOWN)
						{
							tanguiza = 0;
						}
						break;
					case SDLK_l:
						Mix_PlayChannel(-1, punch_sound, 0);
						animer_hero(h, PUNCH, c);
						break;
					case SDLK_m:
						Mix_PlayChannel(-1, punch_sound, 0);
						animer_hero(h, KICK, c);
						break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
					case SDLK_z:
						if (h->collision_UP || h->position.y == h->current_ground_position - JUMP_HEIGHT)
						{
							tanguiza = 1;
						}
						break;
					case SDLK_d:
					case SDLK_q:
					{
						accel = 0;
					}
					break;
					}
					if (h->state == WALK_RIGHT || h->state == WALK_LEFT)
						h->state = IDLE;
					break;
				}
			}
			timeAccumulatedMs -= timeStepMs;
		}
	}
}
void animer_hero2(hero *h, state movement, character c)
{
	if (h->sprite.image != NULL)
	{
		static int x = 0;
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
		case JUMP:
			h->sprite.frame.y = 2 * h->sprite.frame.h;
			h->sprite.frame.x = h->sprite.frame.w;
			h->state = JUMP;
			break;
		case FALLING:
			h->sprite.frame.y = 2 * h->sprite.frame.h;
			h->sprite.frame.x = 2 * h->sprite.frame.w;
			h->state = FALLING;
			break;
		}

		if (c == SAFWEN)
		{
			if (h->direction == RIGHT && x != 1)
			{
				h->sprite.image = IMG_Load("../img/hero/safwen_right.png");
				x = 1;
			}

			else if (h->direction == LEFT && x != 2)
			{
				h->sprite.image = IMG_Load("../img/hero/safwen_left.png");
				x = 2;
			}
		}
		else if (c == OMAR)
		{
			if (h->direction == RIGHT && x != 3)
			{
				h->sprite.image = IMG_Load("../img/hero/omar_right.png");
				x = 3;
			}

			if (h->direction == LEFT && x != 4)
			{
				h->sprite.image = IMG_Load("../img/hero/omar_left.png");
				x = 4;
			}
		}

		tempsActuel = SDL_GetTicks();
		if (movement != JUMP && movement != FALLING)
		{
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
	}
}
void CollisionParfaite2(hero *h, background b, platforme p)
{
	SDL_Color couleur_obstacle = {255, 255, 255};
	int i = 0;
	int collision = 0;
	SDL_Rect pos[8];

	h->collision_UP = -1;
	h->collision_DOWN = -1;
	h->collision_RIGHT = -1;
	h->collision_LEFT = -1;

	pos[0].x = h->position.x;
	pos[0].y = h->position.y;
	pos[1].x = h->position.x + h->sprite.frame.w / 3.9;
	pos[1].y = h->position.y;
	pos[2].x = h->position.x + h->sprite.frame.w / 2;
	pos[2].y = h->position.y;

	pos[3].x = h->position.x;
	pos[3].y = h->position.y + h->sprite.frame.h / 2;
	pos[4].x = h->position.x + h->sprite.frame.w / 2;
	pos[4].y = h->position.y + h->sprite.frame.h / 2;

	pos[5].x = h->position.x;
	pos[5].y = h->position.y + h->sprite.frame.h;
	pos[6].x = h->position.x + h->sprite.frame.w / 3.9;
	pos[6].y = h->position.y + h->sprite.frame.h;
	pos[7].x = h->position.x + h->sprite.frame.w / 2;
	pos[7].y = h->position.y + h->sprite.frame.h;

	for (i = 0; i < 8; i++)
	{
		couleur_obstacle = GetPixel(b.background_mask, pos[i].x, pos[i].y);
		if (couleur_obstacle.r == 0 && couleur_obstacle.g == 0 && couleur_obstacle.b == 0)
		{
			if (i == 0)
			{
				h->collision_LEFT++;
				h->collision_UP++;
			}
			if (i == 1)
			{
				h->collision_UP++;
			}
			if (i == 2)
			{
				h->collision_RIGHT++;
				h->collision_UP++;
			}
			if (i == 3)
			{
				h->collision_LEFT++;
			}
			if (i == 4)
			{
				h->collision_RIGHT++;
			}
			if (i == 5)
			{
				h->collision_LEFT++;
				h->collision_DOWN++;
			}
			if (i == 6)
			{
				h->collision_DOWN++;
			}
			if (i == 7)
			{
				h->collision_RIGHT++;
				h->collision_DOWN++;
			}
		}
	}
	if (h->collision_LEFT <= 0)
		h->collision_LEFT = 0;
	else
		h->collision_LEFT = 1;
	if (h->collision_RIGHT <= 0)
		h->collision_RIGHT = 0;
	else
		h->collision_RIGHT = 1;
	if (h->collision_UP <= 0)
		h->collision_UP = 0;
	else
		h->collision_UP;
	if (h->collision_DOWN <= 0)
		h->collision_DOWN = 0;
	else
		h->collision_DOWN = 1;

	if (!(h->position.y > p.position.y + p.image->h || h->position.y + h->sprite.frame.h < p.position.y || h->position.x > p.position.x + p.image->w || h->position.x <= p.position.x))
		h->collision_DOWN = 1;
	if (!(abs(h->position.y - p.position.y - p.image->h) > 5 || h->position.x > p.position.x + p.image->w || h->position.x <= p.position.x))
		h->collision_UP = 1;
	if (abs(h->position.y - b.posCamera.y) < 7)
		h->collision_UP = 1;
	if (abs(h->position.y + h->sprite.image->h - b.image->h - b.posCamera.h) < 170)
		h->collision_DOWN = 1;
}
void initialiser_platforme2(platforme *p, int x, int y)
{
	p->image = IMG_Load("../img/background/platform.png");
	p->position.x = x;
	p->position.y = y;
	p->image = SDL_DisplayFormat(p->image);
}
void afficher_platforme2(platforme p, background b, SDL_Surface *ecran)
{
	SDL_Rect pos;
	pos.x = p.position.x - b.posCamera.x;
	pos.y = p.position.y - b.posCamera.y;
	SDL_BlitSurface(p.image, NULL, ecran, &pos);
}
void multiplayer(SDL_Surface *ecran, etat *etat, parameter *p, character c)
{
	hero safwen, safwen2;
	background background1, background2;
	SDL_Event event;
	SDL_Rect pos, pos2;
	character c1 = SAFWEN;
	character c2 = SAFWEN;

	int Jcontinuer = 1;
	int verif = 0;
	initialiser_background1(&background1);
	initialiser_background2(&background2);

	SDL_Surface *pencil = IMG_Load("../img/line.png");
	SDL_Rect pos_pencil;
	pos_pencil.x = 0;
	pos_pencil.y = (SCREEN_HEIGHT / 2) - 45;

	SDL_Surface *player2wins = IMG_Load("../img/background/player2.png");
	SDL_Rect pos_player2wins;
	pos_player2wins.x = -100;
	pos_player2wins.y = -100;

	SDL_Surface *player1wins = IMG_Load("../img/background/playeronewins.png");
	SDL_Rect pos_player1wins;
	pos_player1wins.x = -100;
	pos_player1wins.y = -100;

	initialiser_hero(&safwen, "safwen");
	initialiser_hero2(&safwen2, "safwen");

	platforme platforme, platforme2;
	initialiser_platforme2(&platforme, 1180, 1400);
	initialiser_platforme2(&platforme2, 1180, 1400);

	while (Jcontinuer)
	{
		deplacer_hero1(&safwen, &background1, &Jcontinuer, c1, platforme);
		CollisionParfaite2(&safwen, background1, platforme);
		animer_hero(&safwen, safwen.state, c1);
		animer_platforme2(&platforme, 0);

		deplacer_hero2(&safwen2, &background2, &Jcontinuer, c2, platforme2);
		CollisionParfaite2(&safwen2, background2, platforme2);
		animer_hero2(&safwen2, safwen2.state, c2);
		animer_platforme2(&platforme2, 0);

		printf("pos: %d\t%d\n", safwen.position.x, safwen.position.y);

		pos.x = 0;
		pos.y = 0;
		pos2.x = 0;
		pos2.y = SCREEN_HEIGHT / 2;

		SDL_BlitSurface(background1.background_mask, &background1.posCamera, ecran, &background1.position_background_mask);
		SDL_BlitSurface(background1.image, &background1.posCamera, ecran, &pos);
		SDL_BlitSurface(background2.background_mask, &background2.posCamera, ecran, &background2.position_background_mask);
		SDL_BlitSurface(background2.image, &background2.posCamera, ecran, &pos2);

		afficher_platforme2(platforme, background1, ecran);
		afficher_platforme2(platforme2, background2, ecran);
		afficher_hero1(safwen, ecran, background1, safwen2);
		afficher_hero2(safwen2, ecran, background2, safwen);
		SDL_BlitSurface(pencil, NULL, ecran, &pos_pencil);
		if ((safwen.position.x >= 3840 && safwen.position.y >= 1100) && (safwen.position.x > safwen2.position.x))
			SDL_BlitSurface(player1wins, NULL, ecran, &pos_player1wins);
		if ((safwen2.position.x >= 3840 && safwen2.position.y >= 1100) && (safwen2.position.x > safwen.position.x))
			SDL_BlitSurface(player2wins, NULL, ecran, &pos_player2wins);
		SDL_Flip(ecran);
		if (Jcontinuer == 0)
		{
			SDL_EnableKeyRepeat(0, 0);
			*etat = MENU;
		}
	}
	free_background(&background1);
	free_background(&background2);
	free_hero(&safwen);
	free_hero(&safwen2);
	SDL_FreeSurface(platforme.image);
}