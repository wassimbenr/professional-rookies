/**
 * @file hero.c
 */
#include "hero.h"
#include "collision.h"

//! initalise la position de l'hero, sa vie et son score et charge les spritesheets
void initialiser_hero(hero *h, char name[20])
{
	if (TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	char image_load[40] = "";
	char score_str[10] = "";

	h->position.x = 530; //7070;//530;
	h->position.y = 1570; //10;//1570;

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
	h->vie_hero.position_heart_a.y = 0;
	h->vie_hero.position_heart_b.x = 50;
	h->vie_hero.position_heart_b.y = 0;
	h->vie_hero.position_heart_c.x = 100;
	h->vie_hero.position_heart_c.y = 0;

	h->score_hero.couleurNoire.b = 255;
	h->score_hero.couleurNoire.g = 255;
	h->score_hero.couleurNoire.r = 255;
	h->score_hero.score_font = TTF_OpenFont("../fonts/8bit.ttf", 15);
	snprintf(score_str, 10, "%d", h->score_hero.valeur_score);
	h->score_hero.texte_score = TTF_RenderText_Blended(h->score_hero.score_font, score_str, h->score_hero.couleurNoire);
	h->score_hero.position_texte.x = SCREEN_WIDTH_GAME - h->vie_hero.heart->w;
	h->score_hero.position_texte.y = 10;
}

void afficher_hero(hero h, SDL_Surface *screen, background b)
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

		SDL_BlitSurface(h.vie_hero.heart, NULL, screen, &h.vie_hero.position_heart_a);
		SDL_BlitSurface(h.vie_hero.heart, NULL, screen, &h.vie_hero.position_heart_b);
		SDL_BlitSurface(h.vie_hero.heart, NULL, screen, &h.vie_hero.position_heart_c);

		snprintf(score_str, 10, "%d", h.score_hero.valeur_score);
		h.score_hero.texte_score = TTF_RenderText_Blended(h.score_hero.score_font, score_str, h.score_hero.couleurNoire);
		SDL_BlitSurface(h.score_hero.texte_score, NULL, screen, &h.score_hero.position_texte);
	}
}
//! Anime l'hero en utilisant le spritesheet en fonction de son STATE
void animer_hero(hero *h, state movement, character c)
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

void free_hero(hero *h)
{
	SDL_FreeSurface(h->sprite.image);
	SDL_FreeSurface(h->vie_hero.heart);
	SDL_FreeSurface(h->score_hero.texte_score);
	TTF_CloseFont(h->score_hero.score_font);
}

void deplacer_hero(hero *h, background *b, int *Jcontinuer, character c, platforme plats[], int *saving, int n, int *mini)
{
	if (h->sprite.image != NULL)
	{
		static int i;
		int timeStepMs = 10; //if 20 it ruins mvt for some reason
		static int timeLastMs, timeAccumulatedMs, timeDeltaMs, timeCurrentMs = 0;
		static int current_ground_position;
		static float accel = 0;
		static float gravity = 0;
		static int tanguiza = -1;

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
		{
			printf("%s", Mix_GetError());
		}

		static Mix_Chunk *punch_sound;
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
			if (b->posCamera.x < b->image->w - SCREEN_WIDTH_GAME)
			{
				b->posCamera.x = (h->position.x + 5 * h->sprite.frame.w) - SCREEN_WIDTH_GAME;
			}
			if (b->posCamera.y < b->image->h - SCREEN_HEIGHT_GAME)
			{
				b->posCamera.y = (h->position.y + 4 * h->sprite.frame.h) - SCREEN_HEIGHT_GAME;
			}
			if (b->posCamera.x < 0)
				b->posCamera.x = 1;
			if (b->posCamera.y < 0)
				b->posCamera.y = 1;
			if (b->posCamera.y >= b->image->h - SCREEN_HEIGHT_GAME)
				b->posCamera.y = b->image->h - SCREEN_HEIGHT_GAME - 1;

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
				h->position.y += JUMP_SPEED + gravity;
				if (!h->collision_DOWN)
				{
					gravity += 0.25;
				}
			}
			if (tanguiza == 0)
				gravity = 0;
			if (keystates[SDLK_RIGHT] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && (event.motion.x > h->position.x)))
			{
				if (h->direction == LEFT && accel >= 1)
					accel = -2.5;

				h->direction = RIGHT;
				CollisionParfaite(h, *b);
				collision_platforme(h, plats, n);

				if (!h->collision_DOWN && !h->collision_RIGHT)
				{
					h->position.x += 4 + accel;
					if (accel > 0)
						accel -= 0.1;
				}
				else if (h->collision_DOWN && !h->collision_RIGHT)
				{

					h->position.x += 4 + accel;
					animer_hero(h, WALK_RIGHT, c);
					if (accel < 5)
						accel += 0.1;
				}
			}
			if (keystates[SDLK_LEFT] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && (event.motion.x < h->position.x)))
			{
				if (h->direction == RIGHT && accel >= 1)
					accel = -2.5;
				h->direction = LEFT;
				CollisionParfaite(h, *b);
				collision_platforme(h, plats, n);
				if (!h->collision_DOWN && !h->collision_LEFT)
				{

					h->position.x -= 4 + accel;
					if (accel > 0)
						accel -= 0.1;
					if (h->position.x < 0)
						h->position.x = 0;
				}
				else if (h->collision_DOWN && !h->collision_LEFT)
				{
					h->position.x -= 4 + accel;
					animer_hero(h, WALK_LEFT, c);
					if (accel < 5)
						accel += 0.1;
					if (h->position.x < 0)
						h->position.x = 0;
				}
			}
			//SDL_EnableKeyRepeat(2, 2);
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
					case SDLK_k:
						h->vie_hero.nb_vie = 0;
						break;
					case SDLK_s:
						*saving = 1;
						break;
					case SDLK_q:
						*saving = 0;
						break;
					case SDLK_y:
						if (*saving == 1)
							*saving = 2;
						break;

					case SDLK_f:
						h->position.x -= 200;
						break;
					case SDLK_h:
						h->position.x += 200;
						break;
					case SDLK_t:
						h->position.y -= 300;
						break;
					case SDLK_g:
						h->position.y += 300;
						break;
					case SDLK_TAB:
						(*mini) *= -1;
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
void initialiser_dialogue(dialogue *d, SDL_Surface *ecran, character c)
{
	int i = 0;
	FILE *f = NULL;
	f = fopen("../txt_files/dialogue.txt", "r");
	if (f == NULL)
	{
		fprintf(stderr, "Failed to open load file\n");
		exit(EXIT_FAILURE);
	}
	while (!feof(f))
	{
		fgets(d->script[i], 50, f);
		i++;
	}
	fclose(f);

	initialiser_text(&d->text, d->script[0], 100, 80, 30);
	d->text.position.x = 280;
	d->text.position.y = 530;

	d->line = 0;
	d->text.text = NULL;
	d->talking = 0;
	d->first_time = 0;
	if (c == SAFWEN)
		d->hero_dialogue = IMG_Load("../img/hero/safwen_choice_active.png");
	else if (c == OMAR)
		d->hero_dialogue = IMG_Load("../img/hero/omar_choice_active.png");
	d->dialogue_box = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 180, 32, 0, 0, 0, 0);
	SDL_FillRect(d->dialogue_box, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

	d->pos_dialogue_box.x = 0;
	d->pos_dialogue_box.y = SCREEN_HEIGHT_GAME - d->hero_dialogue->h;
	d->pos_hero_dialogue.x = 100;
	d->pos_hero_dialogue.y = SCREEN_HEIGHT_GAME - d->hero_dialogue->h;
}

void linear_dialogue(dialogue *d, SDL_Surface *ecran)
{
	static int tempsActuel = 0;
	static int tempsPrecedent = 0;

	if (d->script[d->line - 1][0] == 'x' || d->line == 0)
	{
		d->hero_dialogue = IMG_Load("../img/hero/safwen_choice_active.png");
		d->dialogue_box = SDL_CreateRGBSurface(SDL_HWSURFACE, SCREEN_WIDTH_GAME, 180, 32, 0, 0, 0, 0);
		SDL_FillRect(d->dialogue_box, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
		d->talking = 1;
	}
	printf("TALKING: %d\n", d->talking);
	if (d->talking)
	{
		tempsActuel = SDL_GetTicks();
		if (tempsActuel - tempsPrecedent > 2000)
		{
			d->text.text = TTF_RenderText_Blended(d->text.font, d->script[d->line], d->text.color);
			tempsPrecedent = tempsActuel;
			if (d->script[d->line][0] == 'x')
			{
				d->talking = 0;
			}
			else
			{
				d->line++;
			}
		}
	}
}

void playing_dialogue(dialogue *d, hero h, SDL_Surface *ecran, timer timer)
{

	static int reached = 0;
	static int passage;
	static int once = 0;

	passage = reached;

	if (h.position.x >= 800 && h.position.x < 1950 && once != 1)
	{

		once = 1;
		if (reached != 2)
			reached++;
	}
	else if (h.position.x >= 2000 && h.position.x < 2600 && once != 2)
	{
		once = 2;
		if (reached != 2)
			reached++;
	}
	/*else if (h.position.x >= 2450 && h.position.x < 2650 && once != 3)
	{
		once = 3;
		if (reached <4)
			reached++;
	}*/
	switch (reached)
	{
	case 1:
		linear_dialogue(d, ecran);
		break;
	case 2:
		if (reached > passage)
			d->line++;
		linear_dialogue(d, ecran);
		break;
		/*case 3:
		if (reached > passage)
			d->line++;
		linear_dialogue(d, ecran);
		break;*/
	}

	printf("LINE: %d\n", d->line);
	printf("REACHED: %d\n", reached);

	if (!d->talking)
	{
		d->text.text = NULL;
		d->dialogue_box = NULL;
		d->hero_dialogue = NULL;
	}

	/*if (timer.time.secondes >= 20 && timer.time.secondes < 25)
	{
		printf("HERE\n");
		d->text.text = TTF_RenderText_Blended(d->text.font, d->script[15], d->text.color);
		d->hero_dialogue = IMG_Load("../img/hero/safwen_choice_active.png");
		d->dialogue_box = SDL_CreateRGBSurface(SDL_HWSURFACE, SCREEN_WIDTH_GAME, 180, 32, 0, 0, 0, 0);
		SDL_FillRect(d->dialogue_box, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
	}*/
	/*if (h.position.x >= 1690 && h.position.x <= 1990 && h.position.y >= 1560)
	{

		d->text.text = TTF_RenderText_Blended(d->text.font, d->script[11], d->text.color);
		d->hero_dialogue = IMG_Load("../img/hero/safwen_choice_active.png");
		d->dialogue_box = SDL_CreateRGBSurface(SDL_HWSURFACE, SCREEN_WIDTH_GAME, 180, 32, 0, 0, 0, 0);
		SDL_FillRect(d->dialogue_box, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
	}*/
}

void afficher_dialogue(dialogue d, SDL_Surface *ecran)
{
	SDL_BlitSurface(d.dialogue_box, NULL, ecran, &d.pos_dialogue_box);
	SDL_BlitSurface(d.hero_dialogue, NULL, ecran, &d.pos_hero_dialogue);
	SDL_BlitSurface(d.text.text, NULL, ecran, &d.text.position);
}
void free_dialogue(dialogue *d)
{
	SDL_FreeSurface(d->dialogue_box);
	SDL_FreeSurface(d->hero_dialogue);
	SDL_FreeSurface(d->text.text);
	TTF_CloseFont(d->text.font);
}

void initialiser_minimap(minimap *m, background b, hero h)
{
	m->image = IMG_Load("../img/background/test2.jpg");
	m->hero = IMG_Load("../img/background/rouge.png");
	m->pos_image.x = (SCREEN_WIDTH_GAME / 2) - (m->image->w / 2);
	m->pos_image.y = 0;
	m->pos_hero.x = (SCREEN_WIDTH_GAME / 2) - (m->image->w / 2) + h.position.x / 52;
	m->pos_hero.y = (h.position.y / 52) - 2;
}

void afficher_minimap(minimap *m, hero h, SDL_Surface *screen, int mini)
{
	if (mini == 1)
	{
		m->pos_hero.x = (SCREEN_WIDTH_GAME / 2) - (m->image->w / 2) + h.position.x / 52;
		m->pos_hero.y = (h.position.y / 52) - 2;
	}
	else if (mini == -1)
	{
		m->pos_hero.x = (SCREEN_WIDTH_GAME / 2) - (m->image->w / 2) + h.position.x / 13.5;
		m->pos_hero.y = (h.position.y / 13.5);
	}

	SDL_BlitSurface(m->image, NULL, screen, &m->pos_image);
	SDL_BlitSurface(m->hero, NULL, screen, &m->pos_hero);
}

void free_minimap(minimap *m)
{
	SDL_FreeSurface(m->image);
	SDL_FreeSurface(m->hero);
}

void initialiser_portal(portal *p)
{
	int j;
	char image[20];
	p->still[0] = IMG_Load("../img/portal_2/1.png");
	p->still[1] = IMG_Load("../img/portal_2/2.png");
	p->still[2] = IMG_Load("../img/portal_2/3.png");
	p->still[3] = IMG_Load("../img/portal_2/4.png");

	for (j = 0; j < 15; j++)
	{
		sprintf(image, "../img/portal/%d.png", j + 1);
		p->enter[j] = IMG_Load(image);
	}

	p->pos_still.x = 5575;
	p->pos_still.y = 1020;

	p->pos_enter.x = 5587;
	p->pos_enter.y = 600;

	p->frame_still = 0;
	p->frame_enter = 0;
}

void animer_portal(portal *p)
{
	static int now = 0;
	static int now_2 = 0;
	static int then = 0;
	static int then_2;

	if (p->frame_still < 4)
	{
		now = SDL_GetTicks();
		if (now - then > 60)
		{
			p->frame_still++;
			then = now;
		}
	}

	else
	{
		p->frame_still = 0;
	}

	if (p->frame_enter < 14)
	{
		now_2 = SDL_GetTicks();
		if (now_2 - then > 60)
		{
			p->frame_enter++;
			then_2 = now_2;
		}
	}

	else
	{
		p->frame_enter = 0;
	}
}

void afficher_portal(portal p, background b, hero h, SDL_Surface *screen)
{
	SDL_Rect pos_rel;

	pos_rel.x = p.pos_still.x - b.posCamera.x;
	pos_rel.y = p.pos_still.y - b.posCamera.y;
	SDL_BlitSurface(p.still[p.frame_still], NULL, screen, &pos_rel);

	if (h.position.x >= 5100 && h.position.x <= 5340 && h.position.y >= 800 && h.position.y <= 1120)
	{
		pos_rel.x = p.pos_enter.x - b.posCamera.x;
		pos_rel.y = p.pos_enter.y - b.posCamera.y;
		SDL_BlitSurface(p.enter[p.frame_enter], NULL, screen, &pos_rel);
	}
}

void free_portal(portal *p)
{
	int i;
	for (i = 0; i < p->frame_enter; i++)
	{
		SDL_FreeSurface(p->enter[i]);
	}
	for (i = 0; i < p->frame_still; i++)
	{
		SDL_FreeSurface(p->still[i]);
	}
}

void camera_pan(background *b, hero h, int x, int y, int *panning, int duree)
{
	static int first = 0;
	static timer t;
	static int once = 0;

	printf("TIMER FCT: %d\n", t.time.secondes);

	if (first == 0)
	{
		init_timer(&t);
		first = 1;
	}

	if (*panning)
	{
		get_time(&t);
		if (abs(b->posCamera.x - x) < 10 && abs(b->posCamera.y - y) < 10)
		{
			if (!once)
			{
				start_timer(&t);
				once = 1;
			}
		}
		else
		{
			if (b->posCamera.x < x)
				b->posCamera.x += 3;
			if (b->posCamera.y < y)
				b->posCamera.y += 4;
		}

		if (t.time.secondes == duree)
		{
			*panning = 0;
			first = 0;
			once = 0;
			stop_timer(&t);
			b->posCamera.x = (h.position.x + 5 * h.sprite.frame.w) - SCREEN_WIDTH_GAME;
			b->posCamera.y = (h.position.y + 4 * h.sprite.frame.h) - SCREEN_HEIGHT_GAME;
		}
	}
}