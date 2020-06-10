/**
* @file background.c
*/

#include "background.h"

void initialiser_background(background *b, parameter p)
{
	/*b->image = IMG_Load("../img/background/background_new.jpg");
	b->background_mask = IMG_Load("../img/background/background_new_masque.jpg");*/
	b->image = IMG_Load("../img/background/1.jpg");
	b->background_mask = IMG_Load("../img/background/2.jpg");
	b->foreground = IMG_Load("../img/background/foreground_2.png");

	b->posCamera.x = 400;
	b->posCamera.y = 900;
	b->posCamera.w = SCREEN_WIDTH_GAME;
	b->posCamera.h = SCREEN_HEIGHT_GAME;

	b->position_background_mask.x = 400;
	b->position_background_mask.y = 900;
	b->position_background_mask.w = SCREEN_WIDTH_GAME;
	b->position_background_mask.h = SCREEN_HEIGHT_GAME;

	b->pos_foreground.x = 400;
	b->pos_foreground.y = 900;
	b->pos_foreground.w = SCREEN_WIDTH_GAME;
	b->pos_foreground.h = SCREEN_HEIGHT_GAME;
}

void initialiser_platforme(platforme *p, int x, int y, int interval, int sens)
{
	p->image = IMG_Load("../img/background/platform.png");
	p->position.x = x;
	p->position.y = y;
	p->pos_init.x = x;
	p->pos_init.y = y;
	p->interval = interval;
	p->sens = sens;
	p->interval = interval;
}

void initialiser_plats(platforme plats[], int n)
{
	initialiser_platforme(&plats[0], 1990, 1120, 680, 1);
	initialiser_platforme(&plats[1], 3200, 1120, 350, -1);

	initialiser_platforme(&plats[2], 450, 850, 80, 1);
	initialiser_platforme(&plats[3], 700, 750, 200, 1);
	initialiser_platforme(&plats[4], 950, 650, 150, 1);

	initialiser_platforme(&plats[5], 8200, 2200, 80, 1);
	initialiser_platforme(&plats[6], 8200, 2100, 200, 1);
	initialiser_platforme(&plats[7], 8200, 2000, 150, 1);

	initialiser_platforme(&plats[8], 8000, 1900, 180, 1);
	initialiser_platforme(&plats[9], 8000, 1800, 300, 1);
	initialiser_platforme(&plats[10], 8000, 1700, 250, 1);
	initialiser_platforme(&plats[11], 8000, 1600, 250, 1);

	initialiser_platforme(&plats[12], 7900, 1500, 250, 1);

}

void initialiser_plats_horiz(platforme plats[], int n)
{
	initialiser_platforme(&plats[0], 700, 1570, 500, 1);
	initialiser_platforme(&plats[1], 400, 1570, 500, 1);
}

void initialiser_text(text *i, char message[40], int x, int y, int size)
{
	TTF_Init();
	i->color.r = 255;
	i->color.g = 255;
	i->color.b = 255;
	i->font = TTF_OpenFont("../fonts/chalk_2.ttf", size);
	i->text = TTF_RenderText_Blended(i->font, message, i->color);
	i->position.x = x;
	i->position.y = y;
}

void initialiser_text_2(text *i, int x, int y, int size)
{
	TTF_Init();
	i->color.r = 255;
	i->color.g = 255;
	i->color.b = 255;
	i->position.x = x;
	i->position.y = y;
	i->font = TTF_OpenFont("../fonts/chalk_2.ttf", size);
}

void initialiser_instructions(text instructions[], int n)
{
	int i = 0;
	TTF_Init();
	char script[n][40];
	FILE *f = NULL;
	f = fopen("../txt_files/instructions.txt", "r");
	if (f == NULL)
	{
		fprintf(stderr, "Failed to open load file\n");
		exit(EXIT_FAILURE);
	}
	while (!feof(f))
	{
		fgets(script[i], 60, f);
		i++;
	}
	fclose(f);

	initialiser_text(&instructions[0], script[0], 600, 1500, 30);
	initialiser_text(&instructions[1], script[1], 2000, 1500, 30);
	initialiser_text(&instructions[2], script[2], 1310, 1265, 30);
	initialiser_text(&instructions[3], script[3], 2700, 1355, 30);
	initialiser_text(&instructions[4], script[4], 3720, 1100, 30);
	initialiser_text(&instructions[5], script[5], 1495, 850, 30);
}

void afficher_background(background *b, SDL_Surface *screen)
{

	SDL_BlitSurface(b->background_mask, &b->position_background_mask, screen, NULL);
	SDL_BlitSurface(b->image, &b->posCamera, screen, NULL);
}
void afficher_platformes(platforme plats[], background b, SDL_Surface *ecran, int n)
{
	static int i;
	SDL_Rect pos;
	for (i = 0; i < n; i++)
	{
		pos.x = plats[i].position.x - b.posCamera.x;
		pos.y = plats[i].position.y - b.posCamera.y;
		SDL_BlitSurface(plats[i].image, NULL, ecran, &pos);
	}
}

void afficher_text(text i, background b, SDL_Surface *ecran)
{
	SDL_Rect pos;
	pos.x = i.position.x - b.posCamera.x;
	pos.y = i.position.y - b.posCamera.y;
	SDL_BlitSurface(i.text, NULL, ecran, &pos);
}
void afficher_text_2(text i, SDL_Surface *ecran, char message[20])
{
	i.text = TTF_RenderText_Blended(i.font, message, i.color);
	SDL_BlitSurface(i.text, NULL, ecran, &i.position);
}

void afficher_instructions(text instructions[], int n, background b, SDL_Surface *ecran)
{
	int i;
	SDL_Rect pos;
	for (i = 0; i < n; i++)
	{
		pos.x = instructions[i].position.x - b.posCamera.x;
		pos.y = instructions[i].position.y - b.posCamera.y;
		SDL_BlitSurface(instructions[i].text, NULL, ecran, &pos);
	}
}
void animer_platformes(platforme plats[], int n)
{
	static int i;
	static int tempsActuel = 0;
	static int tempsPrecedent = 0;

	tempsActuel = SDL_GetTicks();
	if (tempsActuel - tempsPrecedent > 10)
	{
		for (i = 0; i < n; i++)
		{
			plats[i].position.x += 1 * plats[i].sens;
			tempsPrecedent = tempsActuel;
		}
	}
	for (i = 0; i < n; i++)
	{
		if (plats[i].position.x >= plats[i].pos_init.x + plats[i].interval)
			plats[i].sens = -1;
		if (plats[i].position.x <= plats[i].pos_init.x)
			plats[i].sens = 1;
	}
}

void animer_platformes_horiz(platforme plats[], int n)
{
	static int i;
	static int tempsActuel = 0;
	static int tempsPrecedent = 0;

	tempsActuel = SDL_GetTicks();
	if (tempsActuel - tempsPrecedent > 10)
	{
		for (i = 0; i < n; i++)
		{
			plats[i].position.y += 1 * plats[i].sens;
			tempsPrecedent = tempsActuel;
		}
	}
	for (i = 0; i < n; i++)
	{
		if (plats[i].position.y >= plats[i].pos_init.y + plats[i].interval)
			plats[i].sens = -1;
		if (plats[i].position.y <= plats[i].pos_init.y)
			plats[i].sens = 1;
	}
}

void init_timer(timer *t)
{
	t->startTicks = 0;
	t->pausedTicks = 0;
	t->paused = 0;
	t->started = 0;
}
void start_timer(timer *t)
{
	t->started = 1;
	t->paused = 0;
	t->startTicks = SDL_GetTicks();
}
void stop_timer(timer *t)
{
	t->paused = 0;
	t->started = 0;
}
void get_time(timer *t)
{
	int x;
	if (t->started)
	{
		if (t->paused)
		{
			x = t->pausedTicks / 1000;
		}

		else
		{
			x = (SDL_GetTicks() - t->startTicks) / 1000;
		}
		t->time.heures = x / 3600;
		t->time.minutes = x / 60;
		t->time.secondes = x % 60;
	}
	else
	{
		t->time.heures = 0;
		t->time.minutes = 0;
		t->time.secondes = 0;
	}
}
void pause_timer(timer *t)
{
	if (t->started && !t->paused)
	{
		t->paused = 1;
		t->pausedTicks = SDL_GetTicks() - t->startTicks;
	}
}
void resume_timer(timer *t)
{
	if (t->paused)
	{
		t->paused = 0;

		t->startTicks = SDL_GetTicks() - t->pausedTicks;
		t->pausedTicks = 0;
	}
}

void show_time(timer *t, SDL_Surface *screen)
{
	static text time;
	static char cont[20];
	static int once = 0;

	if (!once)
	{
		initialiser_text(&time, "", (SCREEN_WIDTH_GAME / 2) - 85, 0, 30);
		once = 1;
	}

	get_time(t);
	sprintf(cont, "%02d:%02d:%02d\n", t->time.heures, t->time.minutes, t->time.secondes);
	time.text = TTF_RenderText_Blended(time.font, cont, time.color);
	SDL_BlitSurface(time.text, NULL, screen, &time.position);

	printf("%02d:%02d:%02d\n", t->time.heures, t->time.minutes, t->time.secondes);
}

void afficher_temps(text *t, timer *timer, SDL_Surface *ecran)
{
	static char cont[20];
	sprintf(cont, "%02d:%02d:%02d\n", timer->time.heures, timer->time.minutes, timer->time.secondes);
	t->text = TTF_RenderText_Blended(t->font, cont, t->color);
	SDL_BlitSurface(t->text, NULL, ecran, &t->position);
}

void free_param(parameter *p)
{
	Mix_FreeMusic(p->music);
	Mix_FreeChunk(p->keyboard_click);
	Mix_FreeChunk(p->click);
}

void free_background(background *b)
{
	SDL_FreeSurface(b->image);
	SDL_FreeSurface(b->background_mask);
}

void free_platformes(platforme plats[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		SDL_FreeSurface(plats[i].image);
}

void free_instructions(text instructions[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		SDL_FreeSurface(instructions[i].text);
		TTF_CloseFont(instructions[i].font);
	}
}
