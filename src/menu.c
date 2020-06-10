/**
 * @file menu.c
 */
#include "menu.h"

#define SIZE 100
#define TIME 30
void load_story_intro(SDL_Surface *tab[])
{
	int i;
	char image[50];

	for (i = 0; i < 799; i++)
	{
		sprintf(image, "../cinematics/story_intro/  (%d).jpg", i + 1);
		tab[i] = IMG_Load(image);
	}
}
void play_story_intro(SDL_Surface *screen, etat *etat, parameter *p, SDL_Surface *tab[])
{
	static int now = 0;
	static int then = 0;
	static int frame = 0;
	static int once = 0;

	static text skip;

	static SDL_Event event;

	static SDL_Rect pos;

	if (!once)
	{
		p->music = Mix_LoadMUS("../sfx/story_intro.wav");
		Mix_PlayMusic(p->music, -1);
		once = 1;
		pos.x = 40;
		pos.y = 30;
	}

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				*etat = GAME;
				Mix_PlayChannel(-1, p->click, 0);
				break;
			}
			break;
		}
	}

	SDL_BlitSurface(tab[frame], NULL, screen, &pos);
	SDL_BlitSurface(skip.text, NULL, screen, &skip.position);
	SDL_Flip(screen);

	now = SDL_GetTicks();
	if (now - then > 30)
	{
		frame++;
		then = now;
	}

	if (frame == 200)
	{
		initialiser_text(&skip, "Press SPACEBAR to skip", 470, 550, 13);
		skip.font = TTF_OpenFont("../fonts/8bit.ttf", 13);
		skip.text = TTF_RenderText_Blended(skip.font, "Press SPACEBAR to skip", skip.color);
	}

	if (frame >= 799)
		(*etat) = GAME;
}

void play_credits(SDL_Surface *screen, etat *etat, parameter *p)
{
	SDL_Surface *background = IMG_Load("../img/black.jpg");

	SDL_Rect position_back;
	position_back.x = 0;
	position_back.y = 0;

	SDL_Event event;

	int continuer = 1;
	int i = 0;
	int nb_lines = 32;
	int distance = 500;

	text cred[nb_lines];

	char credits_script[nb_lines][40];

	if (!p->mute)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
	if (p->fullscreen)
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);

	FILE *f;
	f = fopen("../txt_files/credits.txt", "r");
	if (f == NULL)
		exit(EXIT_FAILURE);
	while (!feof(f))
	{
		fgets(credits_script[i], 30, f);
		i++;
	}
	fclose(f);

	for (i = 0; i < nb_lines; i++)
	{
		initialiser_text(&cred[i], credits_script[i], 100, distance, 30);
		distance += 30;
	}

	//centering
	for (i = 0; i < nb_lines - 3; i++)
	{
		cred[i].position.x = (800 / 2) - (cred[i].text->w) / 2;
	}

	while (continuer)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					*etat = MENU;
					continuer = 0;
				}
				break;
			}
		}
		SDL_BlitSurface(background, NULL, screen, &position_back);
		for (i = 0; i < nb_lines; i++)
		{
			SDL_BlitSurface(cred[i].text, NULL, screen, &cred[i].position);
		}
		SDL_Flip(screen);
		for (i = 0; i < nb_lines; i++)
		{
			cred[i].position.y -= 1;
			if (cred[i].position.y < 0)

				cred[i].text = TTF_RenderText_Blended(cred[i].font, "", cred[i].color);
		}
	}
	for (i = 0; i < nb_lines; i++)
	{
		SDL_FreeSurface(cred[i].text);
		TTF_CloseFont(cred[i].font);
	}
	SDL_FreeSurface(background);
}
unsigned long
hash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % SIZE;
}

char *hack(char pass[][20])
{
	int i;
	for (i = 0; i < 100; i++)
	{
		if (!strcmp(pass[hash(pass[i])], pass[hash("password")]))
			return pass[i];
	}
}

void cheat(SDL_Surface *ecran, etat *etat, parameter p)
{

	char pass[101][20];
	int i = 0;
	char *hacked;

	char entry_char[15];
	entry_char[0] = '\0';

	int continuer = 1;

	FILE *f;
	f = fopen("../txt_files/passwords.txt", "r");
	while (!feof(f))
	{
		fscanf(f, "%s", pass[i]);
		i++;
	}
	fclose(f);

	SDL_Surface *background = SDL_LoadBMP("../img/menu/background/ZEUUN.bmp");
	SDL_Rect pos_background;
	pos_background.x = 0;
	pos_background.y = 0;

	SDL_Surface *back = IMG_Load("../img/menu/buttons/back.png");
	SDL_Rect pos_back;
	pos_back.x = 330;
	pos_back.y = 330;

	SDL_Surface *text_field = IMG_Load("../img/menu/objects/text_field.png");
	SDL_Rect pos_text_field;
	pos_text_field.x = 180;
	pos_text_field.y = 210;

	SDL_Event event;
	text entry, message, enter;

	initialiser_text(&entry, entry_char, 240, 255, 20);
	entry.color.r = 0;
	entry.color.g = 0;
	entry.color.b = 0;
	initialiser_text(&message, "", 250, 300, 30);
	initialiser_text(&enter, "Enter Cheat Code", 200, 190, 20);
	enter.color.r = 255;
	enter.color.g = 255;
	enter.color.b = 255;

	int back_choice = 0;
	if (!p.mute)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
	if (p.fullscreen)
		ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);

	while (continuer)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				continuer = 0;
				*etat = MENU;
				break;
			case SDL_KEYDOWN:
				Mix_PlayChannel(-1, p.click, 0);
				switch (event.key.keysym.sym)
				{
				case SDLK_DOWN:
					back_choice = 1;
					back = IMG_Load("../img/menu/buttons/back_active.png");
					break;
				case SDLK_UP:
					back_choice = 0;
					back = IMG_Load("../img/menu/buttons/back.png");
					break;
				case SDLK_RETURN:
					if (back_choice == 1)
					{
						continuer = 0;
						*etat = MENU;
					}
					else if (!strcmp(pass[hash(entry_char)], pass[hash("password")]))
					{
						message.color.r = 50;
						message.color.g = 205;
						message.color.b = 50;
						message.text = TTF_RenderText_Blended(entry.font, "NOICE!", message.color);
						entry_char[0] = '\0';
					}
					else
					{
						message.color.r = 250;
						message.color.g = 0;
						message.color.b = 0;
						message.text = TTF_RenderText_Blended(entry.font, "WRONG PASSWORD", message.color);
						entry_char[0] = '\0';
					}
					printf("%s %s\n", pass[hash(entry_char)], pass[hash("password")]);
					printf("hacked: %s\n", hack(pass));
					break;
				case SDLK_BACKSPACE:
					entry_char[strlen(entry_char) - 1] = '\0';
					break;

				case SDLK_a:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "a");
					break;
				case SDLK_b:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "b");
					break;
				case SDLK_c:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "c");
					break;
				case SDLK_d:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "d");
					break;
				case SDLK_e:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "e");
					break;
				case SDLK_f:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "f");
					break;
				case SDLK_g:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "g");
					break;
				case SDLK_h:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "h");
					break;
				case SDLK_i:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "i");
					break;
				case SDLK_j:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "j");
					break;
				case SDLK_k:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "k");
					break;
				case SDLK_l:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "l");
					break;
				case SDLK_m:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "m");
					break;
				case SDLK_n:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "n");
					break;
				case SDLK_o:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "o");
					break;
				case SDLK_p:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "p");
					break;
				case SDLK_q:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "q");
					break;
				case SDLK_r:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "r");
					break;
				case SDLK_s:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "s");
					break;
				case SDLK_t:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "t");
					break;
				case SDLK_u:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "u");
					break;
				case SDLK_v:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "v");
					break;
				case SDLK_w:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "w");
					break;
				case SDLK_x:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "x");
					break;
				case SDLK_y:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "y");
					break;
				case SDLK_z:
					if (strlen(entry_char) < 10)
						strcat(entry_char, "z");
					break;
				}
				entry.text = TTF_RenderText_Blended(entry.font, entry_char, entry.color);
				break;
			}
		}
		SDL_BlitSurface(background, NULL, ecran, &pos_background);
		SDL_BlitSurface(text_field, NULL, ecran, &pos_text_field);
		SDL_BlitSurface(entry.text, NULL, ecran, &entry.position);
		SDL_BlitSurface(message.text, NULL, ecran, &message.position);
		SDL_BlitSurface(enter.text, NULL, ecran, &enter.position);
		SDL_BlitSurface(back, NULL, ecran, &pos_back);
		SDL_Flip(ecran);
	}
	SDL_FreeSurface(entry.text);
	SDL_FreeSurface(enter.text);
	SDL_FreeSurface(message.text);
	SDL_FreeSurface(back);
	SDL_FreeSurface(text_field);
	SDL_FreeSurface(background);
}

void load_intro(SDL_Surface *tab[])
{
	int i;
	char image[50];
	for (i = 0; i < 341; i++)
	{
		sprintf(image, "../cinematics/intro/  (%d).jpg", i + 1);
		tab[i] = IMG_Load(image);
	}
}
void play_intro(SDL_Surface *tab[], SDL_Surface *ecran, etat *etat, parameter *p)
{
	static int i = 0;
	static int tempsActuel = 0;
	static int tempsPrecedent = 0;
	static int once = 0;

	SDL_Event event;

	SDL_Rect pos;
	pos.x = 0;
	pos.y = 0;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				*etat = STORY_INTRO;
				break;
			}
			break;
		}
	}
	SDL_BlitSurface(tab[i], NULL, ecran, &pos);
	SDL_Flip(ecran);
	tempsActuel = SDL_GetTicks();
	if (tempsActuel - tempsPrecedent > 30)
	{
		i++;
		tempsPrecedent = tempsActuel;
	}

	if (i >= 341)
		*etat = STORY_INTRO;
	else
	{
		*etat = INTRO;
	}
}
void game_over(SDL_Surface *screen, etat *etat, parameter *p, hero *h)
{
	SDL_Event event;
	TTF_Init();

	SDL_Surface *game_over_bg = IMG_Load("../img/menu/background/game_over.jpg");
	SDL_Rect position_game_over;
	position_game_over.x = 0;
	position_game_over.y = 0;

	text main_menu, restart;

	initialiser_text_2(&main_menu, 430, 300, 50);
	initialiser_text_2(&restart, 80, 300, 50);
	main_menu.text = TTF_RenderText_Blended(main_menu.font, "Main Menu", main_menu.color);
	restart.text = TTF_RenderText_Blended(restart.font, "Restart", restart.color);

	int continuer = 1;
	int rang = 0;

	if (!p->mute)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();

	while (continuer)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				continuer = 0;
				*etat = EXIT;
				break;
			case SDL_MOUSEMOTION:
				if (event.motion.x > restart.position.x && event.motion.x < restart.position.x + restart.text->w && event.motion.y > restart.position.y && event.motion.y < restart.position.y + restart.text->h)
				{
					main_menu.color.r = 255;
					main_menu.color.g = 255;
					main_menu.color.b = 255;
					main_menu.size = 50;

					restart.color.r = 255;
					restart.color.g = 0;
					restart.color.b = 0;
					//restart.size = 65;
					rang = 0;
				}
				else if (event.motion.x > main_menu.position.x && event.motion.x < main_menu.position.x + main_menu.text->w && event.motion.y > main_menu.position.y && event.motion.y < main_menu.position.y + main_menu.text->h)
				{
					main_menu.color.r = 255;
					main_menu.color.g = 0;
					main_menu.color.b = 0;
					main_menu.size = 65;

					restart.color.r = 255;
					restart.color.g = 255;
					restart.color.b = 255;
					//restart.size = 50;
					rang = 1;
				}
				else
				{
					restart.color.r = 255;
					restart.color.g = 255;
					restart.color.b = 255;

					main_menu.color.r = 255;
					main_menu.color.g = 255;
					main_menu.color.b = 255;
				}

				break;
			case SDL_MOUSEBUTTONUP:
				if (event.motion.x > restart.position.x && event.motion.x < restart.position.x + restart.text->w && event.motion.y > restart.position.y && event.motion.y < restart.position.y + restart.text->h)
				{
					*etat = GAME;
					initialiser_hero(h, "safwen");
					continuer = 0;
				}
				if (event.motion.x > main_menu.position.x && event.motion.x < main_menu.position.x + main_menu.text->w && event.motion.y > main_menu.position.y && event.motion.y < main_menu.position.y + main_menu.text->h)
				{
					*etat = MENU;
					continuer = 0;
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
					//Mix_PlayChannel(-1, p->click, 0);
					main_menu.color.r = 255;
					main_menu.color.g = 0;
					main_menu.color.b = 0;
					main_menu.size = 65;

					restart.color.r = 255;
					restart.color.g = 255;
					restart.color.b = 255;
					restart.size = 50;
					rang = 1;
					break;
				case SDLK_LEFT:
					//Mix_PlayChannel(-1, p->click, 0);
					main_menu.color.r = 255;
					main_menu.color.g = 255;
					main_menu.color.b = 255;
					main_menu.size = 50;

					restart.color.r = 255;
					restart.color.g = 0;
					restart.color.b = 0;
					restart.size = 65;
					rang = 0;
					break;
				case SDLK_RETURN:
					//Mix_PlayChannel(-1, p->click, 0);
					if (rang == 0)
					{
						*etat = GAME;
						initialiser_hero(h, "safwen");
						continuer = 0;
					}
					else if (rang == 1)
					{
						*etat = MENU;
						p->music = Mix_LoadMUS("../sfx/game_menu_music.wav");
						Mix_PlayMusic(p->music, -1);
						continuer = 0;
					}
					break;
				}
				break;
			}
		}
		SDL_BlitSurface(game_over_bg, NULL, screen, &position_game_over);
		afficher_text_2(restart, screen, "Restart");
		afficher_text_2(main_menu, screen, "Main Menu");
		SDL_Flip(screen);
	}
	SDL_FreeSurface(game_over_bg);
	SDL_FreeSurface(restart.text);
	SDL_FreeSurface(main_menu.text);
	//SDL_Quit();
}

//! utilise les fonctions load_game afin de charger le porgres
void game_load(hero *h, background *b, etat *etat, SDL_Surface *screen, parameter *p, character *c, dialogue *d)
{
	SDL_Event event;
	int continuer = 1;

	SDL_Surface *character_choice = SDL_LoadBMP("../img/menu/background/ZEUUN.bmp");
	SDL_Rect position_character_choice;
	position_character_choice.x = 0;
	position_character_choice.y = 0;
	position_character_choice.w = SCREEN_WIDTH;
	position_character_choice.h = SCREEN_HEIGHT;

	SDL_Surface *new_game = IMG_Load("../img/menu/buttons/new_game.png");
	SDL_Rect pos_new_game;
	pos_new_game.x = 210;
	pos_new_game.y = 210;

	SDL_Surface *cont = IMG_Load("../img/menu/buttons/continue.png");
	SDL_Rect pos_continue;
	pos_continue.x = 210;
	pos_continue.y = 250;

	SDL_Surface *multiplayer = IMG_Load("../img/menu/buttons/multiplayer.png");
	SDL_Rect pos_multiplayer;
	pos_multiplayer.x = 210;
	pos_multiplayer.y = 290;

	SDL_Surface *back = IMG_Load("../img/menu/buttons/back.png");
	SDL_Rect pos_back;
	pos_back.x = 330;
	pos_back.y = 330;

	int rang = -1;

	if (!p->mute)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();

	while (continuer)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_DOWN:
					Mix_PlayChannel(-1, p->click, 0);
					if (rang == -1)
					{
						new_game = IMG_Load("../img/menu/buttons/new_game_active.png");
						cont = IMG_Load("../img/menu/buttons/continue.png");
						multiplayer = IMG_Load("../img/menu/buttons/multiplayer.png");
						back = IMG_Load("../img/menu/buttons/back.png");
						rang++;
					}
					else if (rang == 0)
					{
						cont = IMG_Load("../img/menu/buttons/continue_active.png");
						new_game = IMG_Load("../img/menu/buttons/new_game.png");
						multiplayer = IMG_Load("../img/menu/buttons/multiplayer.png");
						back = IMG_Load("../img/menu/buttons/back.png");
						rang++;
					}
					else if (rang == 1)
					{
						multiplayer = IMG_Load("../img/menu/buttons/multiplayer_active.png");
						cont = IMG_Load("../img/menu/buttons/continue.png");
						new_game = IMG_Load("../img/menu/buttons/new_game.png");
						back = IMG_Load("../img/menu/buttons/back.png");
						rang++;
					}
					else if (rang == 2)
					{
						back = IMG_Load("../img/menu/buttons/back_active.png");
						cont = IMG_Load("../img/menu/buttons/continue.png");
						multiplayer = IMG_Load("../img/menu/buttons/multiplayer.png");
						new_game = IMG_Load("../img/menu/buttons/new_game.png");
						rang++;
					}
					else if (rang == 3)
					{
						back = IMG_Load("../img/menu/buttons/back.png");
						cont = IMG_Load("../img/menu/buttons/continue.png");
						multiplayer = IMG_Load("../img/menu/buttons/multiplayer.png");
						new_game = IMG_Load("../img/menu/buttons/new_game_active.png");
						rang = 0;
					}
					break;
				case SDLK_UP:
					Mix_PlayChannel(-1, p->click, 0);
					if (rang == 0)
					{
						back = IMG_Load("../img/menu/buttons/back_active.png");
						cont = IMG_Load("../img/menu/buttons/continue.png");
						multiplayer = IMG_Load("../img/menu/buttons/multiplayer.png");
						new_game = IMG_Load("../img/menu/buttons/new_game.png");
						rang = 3;
					}
					else if (rang == 1)
					{
						new_game = IMG_Load("../img/menu/buttons/new_game_active.png");
						cont = IMG_Load("../img/menu/buttons/continue.png");
						multiplayer = IMG_Load("../img/menu/buttons/multiplayer.png");
						back = IMG_Load("../img/menu/buttons/back.png");
						rang--;
					}
					else if (rang == 2)
					{
						cont = IMG_Load("../img/menu/buttons/continue_active.png");
						new_game = IMG_Load("../img/menu/buttons/new_game.png");
						multiplayer = IMG_Load("../img/menu/buttons/multiplayer.png");
						back = IMG_Load("../img/menu/buttons/back.png");
						rang--;
					}
					else if (rang == 3)
					{
						multiplayer = IMG_Load("../img/menu/buttons/multiplayer_active.png");
						cont = IMG_Load("../img/menu/buttons/continue.png");
						new_game = IMG_Load("../img/menu/buttons/new_game.png");
						back = IMG_Load("../img/menu/buttons/back.png");
						rang--;
					}
					break;
				case SDLK_RETURN:
					Mix_PlayChannel(-1, p->click, 0);
					switch (rang)
					{
					case 0:
						*etat = CHARACTER;
						continuer = 0;
						break;
					case 1:
						load_game(h, b, c, d);
						*etat = GAME;
						continuer = 0;
						break;
					case 2:
						*etat = MULTIPLAYER;
						continuer = 0;
						break;
					case 3:
						*etat = MENU;
						continuer = 0;
					}
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				if (event.motion.x > pos_continue.x && event.motion.x < pos_continue.x + cont->w && event.motion.y > pos_continue.y && event.motion.y < pos_continue.y + cont->h)
				{
					cont = IMG_Load("../img/menu/buttons/continue_active.png");
					multiplayer = IMG_Load("../img/menu/buttons/multiplayer.png");
					new_game = IMG_Load("../img/menu/buttons/new_game.png");
					back = IMG_Load("../img/menu/buttons/back.png");
				}
				else if (event.motion.x > pos_new_game.x && event.motion.x < pos_new_game.x + new_game->w && event.motion.y > pos_new_game.y && event.motion.y < pos_new_game.y + new_game->h)
				{
					new_game = IMG_Load("../img/menu/buttons/new_game_active.png");
					cont = IMG_Load("../img/menu/buttons/continue.png");
					back = IMG_Load("../img/menu/buttons/back.png");
					multiplayer = IMG_Load("../img/menu/buttons/multiplayer.png");
				}
				else if (event.motion.x < pos_multiplayer.x + multiplayer->w && event.motion.x > pos_multiplayer.x && event.motion.y < pos_multiplayer.y + multiplayer->h && event.motion.y > pos_multiplayer.y)
				{
					multiplayer = IMG_Load("../img/menu/buttons/multiplayer_active.png");
					new_game = IMG_Load("../img/menu/buttons/new_game.png");
					cont = IMG_Load("../img/menu/buttons/continue.png");
					back = IMG_Load("../img/menu/buttons/back.png");
				}
				else if (event.motion.x < pos_back.x + back->w && event.motion.x > pos_back.x && event.motion.y < pos_back.y + back->h && event.motion.y > pos_back.y)
				{
					back = IMG_Load("../img/menu/buttons/back_active.png");
					cont = IMG_Load("../img/menu/buttons/continue.png");
					multiplayer = IMG_Load("../img/menu/buttons/multiplayer.png");
					new_game = IMG_Load("../img/menu/buttons/new_game.png");
				}
				else
				{
					cont = IMG_Load("../img/menu/buttons/continue.png");
					multiplayer = IMG_Load("../img/menu/buttons/multiplayer.png");
					new_game = IMG_Load("../img/menu/buttons/new_game.png");
					back = IMG_Load("../img/menu/buttons/back.png");
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (event.motion.x > pos_continue.x && event.motion.x < pos_continue.x + cont->w && event.motion.y > pos_continue.y && event.motion.y < pos_continue.y + cont->h)
					{
						load_game(h, b, c, d);
						*etat = GAME;
						continuer = 0;
					}
					else if (event.motion.x > pos_new_game.x && event.motion.x < pos_new_game.x + new_game->w && event.motion.y > pos_new_game.y && event.motion.y < pos_new_game.y + new_game->h)
					{
						*etat = CHARACTER;
						continuer = 0;
					}
					else if (event.motion.x < pos_multiplayer.x + multiplayer->w && event.motion.x > pos_multiplayer.x && event.motion.y < pos_multiplayer.y + multiplayer->h && event.motion.y > pos_multiplayer.y)
					{
						*etat = MULTIPLAYER;
						continuer = 0;
					}
					else if (event.motion.x < pos_back.x + back->w && event.motion.x > pos_back.x && event.motion.y < pos_back.y + back->h && event.motion.y > pos_back.y)
					{
						*etat = MENU;
						continuer = 0;
					}
				}
				break;
			}
		}
		SDL_BlitSurface(character_choice, NULL, screen, &position_character_choice);
		SDL_BlitSurface(cont, NULL, screen, &pos_continue);
		SDL_BlitSurface(multiplayer, NULL, screen, &pos_multiplayer);
		SDL_BlitSurface(new_game, NULL, screen, &pos_new_game);
		SDL_BlitSurface(back, NULL, screen, &pos_back);
		SDL_Flip(screen);
	}
}

//! sauvegarde la position de l'hero, sa vie et son score dans un fichier texte et sera appelée dans la boucle du jeu
void save_game(hero h, background b, character c, dialogue d)
{
	FILE *f = NULL;
	f = fopen("../txt_files/niveau.txt", "w");
	if (f == NULL)
	{
		fprintf(stderr, "Failed to open save file\n");
		exit(EXIT_FAILURE);
	}
	if (c == SAFWEN)
		fprintf(f, "%d %d %d %d %d %d\n", h.vie_hero.nb_vie, h.score_hero.valeur_score, h.position.x, h.position.y, d.line, 0);
	else if (c == OMAR)
		fprintf(f, "%d %d %d %d %d %d\n", h.vie_hero.nb_vie, h.score_hero.valeur_score, h.position.x, h.position.y, d.line, 1);
	if (ferror(f))
	{
		fprintf(stderr, "Failed to print to file\n");
		exit(EXIT_FAILURE);
	}
	fclose(f);
}
//! utilise le fichier txt de sauvegarde pour charger la position de l'hero, sa vie et son score et sera appelée dans l'ecran de chargement de l'hero
void load_game(hero *h, background *b, character *c, dialogue *d)
{
	int i;
	FILE *f = NULL;
	f = fopen("../txt_files/niveau.txt", "r");
	if (f == NULL)
	{
		fprintf(stderr, "Failed to open load file\n");
		exit(EXIT_FAILURE);
	}
	initialiser_hero(h, "safwen");

	//initialiser_background(b,p);

	fscanf(f, "%d %d %hd %hd %d %d", &h->vie_hero.nb_vie, &h->score_hero.valeur_score, &h->position.x, &h->position.y, &d->line, &i);
	if (i == 0)
		*c = SAFWEN;
	else if (i == 1)
		*c = OMAR;
	printf("char: %d\n", i);
	if (ferror(f))
	{
		fprintf(stderr, "Failed to print to file\n");
		exit(EXIT_FAILURE);
	}
	fclose(f);
}

//! permet de choisir le spritesheet a charger au depend du hero choisi (character c)
void character_choice(hero *h, etat *etat, SDL_Surface *screen, parameter *p, character *c)
{
	SDL_Event event;

	background b;
	//load_game(h, &b, c);

	SDL_Surface *character_choice = SDL_LoadBMP("../img/menu/background/ZEUUN.bmp");
	SDL_Rect position_character_choice;
	position_character_choice.x = 0;
	position_character_choice.y = 0;
	position_character_choice.w = SCREEN_WIDTH;
	position_character_choice.h = SCREEN_HEIGHT;

	SDL_Surface *safwen_image = IMG_Load("../img/hero/safwen_choice_small.png");
	SDL_Rect position_safwen;
	position_safwen.x = 200;
	position_safwen.y = 210;

	SDL_Surface *omar = IMG_Load("../img/hero/omar_choice_small.png");
	SDL_Rect position_omar;
	position_omar.x = 300;
	position_omar.y = 210;

	SDL_Surface *back = IMG_Load("../img/menu/buttons/back.png");
	SDL_Rect pos_back;
	pos_back.x = 330;
	pos_back.y = 330;

	SDL_Surface *arrow = NULL;
	SDL_Rect pos_arrow;

	SDL_Surface *lock = IMG_Load("../img/menu/objects/lock.png");
	SDL_Rect pos_lock;
	pos_lock.x = 310;
	pos_lock.y = 240;
	printf("score: %d\n", h->score_hero.valeur_score);
	if (h->score_hero.valeur_score >= 40)
		lock = NULL;

	int continuer = 1;
	choice choice = NO;

	if (!p->mute)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();

	while (continuer)
	{
		while (SDL_PollEvent(&event))
		{
			if (choice == SAF)
			{
				pos_arrow.x = 210;
				pos_arrow.y = 140;
				position_safwen.x = 190;
				position_safwen.y = 200;
				arrow = IMG_Load("../img/hero/arrow.png");
				safwen_image = IMG_Load("../img/hero/safwen_choice_active.png");
				omar = IMG_Load("../img/hero/omar_choice_small.png");
				back = IMG_Load("../img/menu/buttons/back.png");
			}
			else if (choice == OM)
			{
				pos_arrow.x = 320;
				pos_arrow.y = 140;
				position_omar.x = 290;
				position_omar.y = 200;
				arrow = IMG_Load("../img/hero/arrow.png");
				omar = IMG_Load("../img/hero/omar_choice_active.png");
				safwen_image = IMG_Load("../img/hero/safwen_choice_small.png");
				back = IMG_Load("../img/menu/buttons/back.png");
			}
			else if (choice == BACK)
			{
				back = IMG_Load("../img/menu/buttons/back_active.png");
				safwen_image = IMG_Load("../img/hero/safwen_choice_small.png");
				omar = IMG_Load("../img/hero/omar_choice_small.png");
				arrow = NULL;
				position_omar.x = 300;
				position_omar.y = 210;
				position_safwen.x = 200;
				position_safwen.y = 210;
			}
			else if (choice == NO)
			{
				safwen_image = IMG_Load("../img/hero/safwen_choice_small.png");
				omar = IMG_Load("../img/hero/omar_choice_small.png");
				back = IMG_Load("../img/menu/buttons/back.png");
				arrow = NULL;
				position_omar.x = 300;
				position_omar.y = 210;
				position_safwen.x = 200;
				position_safwen.y = 210;
			}
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
					Mix_PlayChannel(-1, p->click, 0);
					if (choice == SAF || choice == NO)
						choice = OM;
					else if (choice == OM)
						choice = SAF;
					break;
				case SDLK_LEFT:
					Mix_PlayChannel(-1, p->click, 0);
					if (choice == OM || choice == NO)
						choice = SAF;
					else if (choice == SAF)
						choice = OM;
					break;
				case SDLK_UP:
					Mix_PlayChannel(-1, p->click, 0);
					if (choice == BACK)
						choice = SAF;
					break;
				case SDLK_DOWN:
					Mix_PlayChannel(-1, p->click, 0);
					choice = BACK;
					break;
				case SDLK_RETURN:
					Mix_PlayChannel(-1, p->click, 0);
					switch (choice)
					{
					case SAF:
						initialiser_hero(h, "safwen");
						*c = SAFWEN;
						*etat = INTRO;
						p->music = Mix_LoadMUS("../sfx/ds.mp3");
						Mix_PlayMusic(p->music, -1);
						continuer = 0;
						break;
					case OM:
						if (h->score_hero.valeur_score >= 40)
						{
							initialiser_hero(h, "omar");
							*c = OMAR;
							*etat = INTRO;
							continuer = 0;
						}
						break;
					case BACK:
						*etat = MENU;
						continuer = 0;
						break;
					}
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (event.motion.x < position_safwen.x + safwen_image->w && event.motion.x > position_safwen.x && event.motion.y < position_safwen.y + safwen_image->h && event.motion.y > position_safwen.y)
					{
						initialiser_hero(h, "safwen");
						*c = SAFWEN;
						*etat = INTRO;
						continuer = 0;
					}
					if (event.motion.x < position_omar.x + omar->w && event.motion.x > position_omar.x && event.motion.y < position_omar.y + omar->h && event.motion.y > position_omar.y)
					{
						initialiser_hero(h, "omar");
						*c = OMAR;
						*etat = INTRO;
						continuer = 0;
					}
					if (event.motion.x < pos_back.x + back->w && event.motion.x > pos_back.x && event.motion.y < pos_back.y + back->h && event.motion.y > pos_back.y)
					{
						*etat = MENU;
						continuer = 0;
					}
				}
				break;
			case SDL_MOUSEMOTION:
				if (event.motion.x < position_safwen.x + safwen_image->w && event.motion.x > position_safwen.x && event.motion.y < position_safwen.y + safwen_image->h && event.motion.y > position_safwen.y)
				{
					pos_arrow.x = 210;
					pos_arrow.y = 140;
					position_safwen.x = 190;
					position_safwen.y = 200;
					arrow = IMG_Load("../img/hero/arrow.png");
					safwen_image = IMG_Load("../img/hero/safwen_choice_active.png");
				}
				else if (event.motion.x < position_omar.x + omar->w && event.motion.x > position_omar.x && event.motion.y < position_omar.y + omar->h && event.motion.y > position_omar.y)
				{
					pos_arrow.x = 320;
					pos_arrow.y = 140;
					position_omar.x = 290;
					position_omar.y = 200;
					arrow = IMG_Load("../img/hero/arrow.png");
					omar = IMG_Load("../img/hero/omar_choice_active.png");
				}
				else if (event.motion.x < pos_back.x + back->w && event.motion.x > pos_back.x && event.motion.y < pos_back.y + back->h && event.motion.y > pos_back.y)
				{
					back = IMG_Load("../img/menu/buttons/back_active.png");
				}
				else
				{
					safwen_image = IMG_Load("../img/hero/safwen_choice_small.png");
					omar = IMG_Load("../img/hero/omar_choice_small.png");
					back = IMG_Load("../img/menu/buttons/back.png");
					arrow = NULL;
					position_omar.x = 300;
					position_omar.y = 210;
					position_safwen.x = 200;
					position_safwen.y = 210;
				}
				break;
			}
		}
		SDL_BlitSurface(character_choice, NULL, screen, &position_character_choice);
		SDL_BlitSurface(safwen_image, NULL, screen, &position_safwen);
		SDL_BlitSurface(omar, NULL, screen, &position_omar);
		SDL_BlitSurface(back, NULL, screen, &pos_back);
		SDL_BlitSurface(arrow, NULL, screen, &pos_arrow);
		SDL_BlitSurface(lock, NULL, screen, &pos_lock);
		SDL_Flip(screen);
	}
}
void settings(SDL_Surface *screen, parameter *p, etat *etat)
{
	SDL_Surface *background;
	SDL_Rect pos_backg;
	SDL_Event event;
	SDL_Surface *full = NULL, *mute = NULL, *back = NULL, *screen_mode = NULL, *sound = NULL, *volume_bar = NULL, *plus = NULL, *moins = NULL;
	SDL_Rect pos_mute, pos_full, pos_back, pos_sound, pos_screen, pos_vol_bar, pos_plus, pos_moins;
	Mix_Chunk *click;
	int continuer = 1, f = 0, m = 0, b = 0;
	TTF_Font *police = NULL;
	police = TTF_OpenFont("../fonts/8bit.ttf", 15);
	SDL_Color couleurBlanche = {255, 255, 255};
	SDL_Color couleurRouge = {255, 0, 0};

	plus = TTF_RenderText_Blended(police, "+", couleurBlanche);
	moins = TTF_RenderText_Blended(police, "-", couleurBlanche);

	pos_backg.x = 0;
	pos_backg.y = 0;
	pos_sound.x = 200;
	pos_sound.y = 219;
	pos_mute.x = 280;
	pos_mute.y = pos_sound.y;
	pos_screen.x = 200;
	pos_screen.y = 260;
	pos_full.x = 320;
	pos_full.y = pos_screen.y - 10;
	pos_back.x = 200;
	pos_back.y = 300;
	pos_vol_bar.x = 340;
	pos_vol_bar.y = 212;
	pos_plus.x = 405;
	pos_plus.y = 220;
	pos_moins.x = 425;
	pos_moins.y = 220;
	switch (p->volume)
	{
	case 0:
		p->mute = 1;
		volume_bar = NULL;
		break;
	case 24:
		volume_bar = IMG_Load("../img/menu/buttons/1_bar.png");
		break;
	case 48:
		volume_bar = IMG_Load("../img/menu/buttons/2_bars.png");
		break;
	case 72:
		volume_bar = IMG_Load("../img/menu/buttons/3_bars.png");
		break;
	case 96:
		volume_bar = IMG_Load("../img/menu/buttons/4_bars.png");
		break;
	case 120:
		volume_bar = IMG_Load("../img/menu/buttons/5_bars.png");
		break;
	}
	sound = IMG_Load("../img/menu/buttons/sound.png");
	if (p->mute == 0)
		mute = IMG_Load("../img/menu/buttons/mute.png");
	else
		mute = IMG_Load("../img/menu/buttons/mute_tick.png");
	screen_mode = IMG_Load("../img/menu/buttons/screen.png");
	if (p->fullscreen == 0)
		full = IMG_Load("../img/menu/buttons/full.png");
	else
		full = IMG_Load("../img/menu/buttons/full_tick.png");
	back = IMG_Load("../img/menu/buttons/back.png");

	click = Mix_LoadWAV("../sfx/click.wav");

	background = SDL_LoadBMP("../img/menu/background/ZEUUN.bmp");

	while (continuer)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					continuer = 0;
					break;
				case SDLK_LEFT:
					if (m == 1)
					{
						p->volume -= 24;
						switch (p->volume)
						{
						case 0:
							p->mute = 1;
							volume_bar = NULL;
							break;
						case 24:
							volume_bar = IMG_Load("../img/menu/buttons/1_bar.png");
							break;
						case 48:
							volume_bar = IMG_Load("../img/menu/buttons/2_bars.png");
							break;
						case 72:
							volume_bar = IMG_Load("../img/menu/buttons/3_bars.png");
							break;
						case 96:
							volume_bar = IMG_Load("../img/menu/buttons/4_bars.png");
							break;
						case 120:
							volume_bar = IMG_Load("../img/menu/buttons/5_bars.png");
							break;
						}
					}
					break;
				case SDLK_RIGHT:
					if (m == 1)
					{
						p->volume += 24;
						p->mute = 0;
						switch (p->volume)
						{
						case 0:
							p->mute = 1;
							volume_bar = NULL;
							break;
						case 24:
							volume_bar = IMG_Load("../img/menu/buttons/1_bar.png");
							break;
						case 48:
							volume_bar = IMG_Load("../img/menu/buttons/2_bars.png");
							break;
						case 72:
							volume_bar = IMG_Load("../img/menu/buttons/3_bars.png");
							break;
						case 96:
							volume_bar = IMG_Load("../img/menu/buttons/4_bars.png");
							break;
						case 120:
							volume_bar = IMG_Load("../img/menu/buttons/5_bars.png");
							break;
						}
					}
					break;
				case SDLK_RETURN:
					if (b == 1)
					{
						Mix_PlayChannel(-1, p->click, 0);
						continuer = 0;
						*etat = MENU;
					}
					if (f == 1 && p->fullscreen == 0)
					{
						Mix_PlayChannel(-1, p->click, 0);
						screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
						full = IMG_Load("../img/menu/buttons/full_active_tick.png");
						//SDL_Flip(screen);
						p->fullscreen = 1;
					}
					else if (f == 1 && p->fullscreen == 1)
					{
						Mix_PlayChannel(-1, p->click, 0);
						screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
						full = IMG_Load("../img/menu/buttons/full_active.png");
						//SDL_Flip(screen);
						p->fullscreen = 0;
					}
					if (m == 1 && p->mute == 0)
					{
						Mix_PauseMusic();
						mute = IMG_Load("../img/menu/buttons/mute_active_tick.png");
						p->mute = 1;
					}
					else if (m == 1 && p->mute == 1)
					{
						Mix_ResumeMusic();
						mute = IMG_Load("../img/menu/buttons/mute_active.png");
						p->mute = 0;
					}
					break;
				case SDLK_DOWN:
					if (m == 0 && f == 0 && b == 0)
					{

						Mix_PlayChannel(-1, p->click, 0);
						if (p->mute == 0)
							mute = IMG_Load("../img/menu/buttons/mute_active.png");
						else
							mute = IMG_Load("../img/menu/buttons/mute_active_tick.png");
						if (p->fullscreen == 0)
							full = IMG_Load("../img/menu/buttons/full.png");
						else
							full = IMG_Load("../img/menu/buttons/full_tick.png");
						m = 1;
						f = 0;
						b = 0;
					}
					else if (m == 1 && f == 0 && b == 0)
					{
						Mix_PlayChannel(-1, p->click, 0);
						if (p->mute == 0)
							mute = IMG_Load("../img/menu/buttons/mute.png");
						else
							mute = IMG_Load("../img/menu/buttons/mute_tick.png");
						if (p->fullscreen == 0)
							full = IMG_Load("../img/menu/buttons/full_active.png");
						else
							full = IMG_Load("../img/menu/buttons/full_active_tick.png");
						m = 0;
						f = 1;
						b = 0;
					}
					else if (m == 0 && f == 1 && b == 0)
					{
						Mix_PlayChannel(-1, p->click, 0);
						if (p->fullscreen == 0)
							full = IMG_Load("../img/menu/buttons/full.png");
						else
							full = IMG_Load("../img/menu/buttons/full_tick.png");
						if (p->mute == 0)
							mute = IMG_Load("../img/menu/buttons/mute.png");
						else
							mute = IMG_Load("../img/menu/buttons/mute_tick.png");
						back = IMG_Load("../img/menu/buttons/back_active.png");
						m = 0;
						f = 0;
						b = 1;
					}
					break;
				case SDLK_UP:
					if (m == 0 && f == 0 && b == 1)
					{
						Mix_PlayChannel(-1, p->click, 0);
						if (p->fullscreen == 0)
							full = IMG_Load("../img/menu/buttons/full_active.png");
						else
							full = IMG_Load("../img/menu/buttons/full_active_tick.png");
						if (p->mute == 0)
							mute = IMG_Load("../img/menu/buttons/mute.png");
						else
							mute = IMG_Load("../img/menu/buttons/mute_tick.png");
						back = IMG_Load("../img/menu/buttons/back.png");
						m = 0;
						f = 1;
						b = 0;
					}
					else if (m == 0 && f == 1 && b == 0)
					{
						Mix_PlayChannel(-1, p->click, 0);
						if (p->fullscreen == 0)
							full = IMG_Load("../img/menu/buttons/full.png");
						else
							full = IMG_Load("../img/menu/buttons/full_tick.png");
						if (p->mute == 0)
							mute = IMG_Load("../img/menu/buttons/mute_active.png");
						else
							mute = IMG_Load("../img/menu/buttons/mute_active_tick.png");
						back = IMG_Load("../img/menu/buttons/back.png");
						m = 1;
						f = 0;
						b = 0;
					}
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				if (event.motion.x > pos_plus.x && event.motion.x < pos_plus.x + plus->w && event.motion.y > pos_plus.y && event.motion.y < pos_plus.y + plus->h)
				{
					plus = TTF_RenderText_Blended(police, "+", couleurRouge);
					if (p->mute == 0)
						mute = IMG_Load("../img/menu/buttons/mute.png");
					else
						mute = IMG_Load("../img/menu/buttons/mute_tick.png");
					if (p->fullscreen == 0)
						full = IMG_Load("../img/menu/buttons/full.png");
					else
						full = IMG_Load("../img/menu/buttons/full_tick.png");
					moins = TTF_RenderText_Blended(police, "-", couleurBlanche);
				}
				else if (event.motion.x > pos_moins.x && event.motion.x < pos_moins.x + moins->w && event.motion.y > pos_moins.y && event.motion.y < pos_moins.y + moins->h)
				{
					moins = TTF_RenderText_Blended(police, "-", couleurRouge);
					if (p->mute == 0)
						mute = IMG_Load("../img/menu/buttons/mute.png");
					else
						mute = IMG_Load("../img/menu/buttons/mute_tick.png");
					if (p->fullscreen == 0)
						full = IMG_Load("../img/menu/buttons/full.png");
					else
						full = IMG_Load("../img/menu/buttons/full_tick.png");
					plus = TTF_RenderText_Blended(police, "+", couleurBlanche);
				}
				else if (event.motion.x > pos_mute.x && event.motion.x < pos_mute.x + mute->w && event.motion.y > pos_mute.y && event.motion.y < pos_mute.y + mute->h)
				{
					if (p->mute == 0)
						mute = IMG_Load("../img/menu/buttons/mute_active.png");
					else
						mute = IMG_Load("../img/menu/buttons/mute_active_tick.png");
					if (p->fullscreen == 0)
						full = IMG_Load("../img/menu/buttons/full.png");
					else
						full = IMG_Load("../img/menu/buttons/full_tick.png");
					back = IMG_Load("../img/menu/buttons/back.png");
					plus = TTF_RenderText_Blended(police, "+", couleurBlanche);
					moins = TTF_RenderText_Blended(police, "-", couleurBlanche);
				}
				else if (event.motion.x > pos_full.x && event.motion.x < pos_full.x + full->w && event.motion.y > pos_full.y && event.motion.y < pos_full.y + full->h)
				{
					if (p->fullscreen == 0)
						full = IMG_Load("../img/menu/buttons/full_active.png");
					else
						full = IMG_Load("../img/menu/buttons/full_active_tick.png");
					if (p->mute == 0)
						mute = IMG_Load("../img/menu/buttons/mute.png");
					else
						mute = IMG_Load("../img/menu/buttons/mute_tick.png");
					back = IMG_Load("../img/menu/buttons/back.png");
					plus = TTF_RenderText_Blended(police, "+", couleurBlanche);
					moins = TTF_RenderText_Blended(police, "-", couleurBlanche);
				}
				else if (event.motion.x > pos_back.x && event.motion.x < pos_back.x + back->w && event.motion.y > pos_back.y && event.motion.y < pos_back.y + back->h)
				{
					if (p->mute == 0)
						mute = IMG_Load("../img/menu/buttons/mute.png");
					else
						mute = IMG_Load("../img/menu/buttons/mute_tick.png");
					if (p->fullscreen == 0)
						full = IMG_Load("../img/menu/buttons/full.png");
					else
						full = IMG_Load("../img/menu/buttons/full_tick.png");
					back = IMG_Load("../img/menu/buttons/back_active.png");
					plus = TTF_RenderText_Blended(police, "+", couleurBlanche);
					moins = TTF_RenderText_Blended(police, "-", couleurBlanche);
				}
				else
				{
					if (p->mute == 0)
						mute = IMG_Load("../img/menu/buttons/mute.png");
					else
						mute = IMG_Load("../img/menu/buttons/mute_tick.png");
					if (p->fullscreen == 0)
						full = IMG_Load("../img/menu/buttons/full.png");
					else
						full = IMG_Load("../img/menu/buttons/full_tick.png");
					back = IMG_Load("../img/menu/buttons/back.png");
					plus = TTF_RenderText_Blended(police, "+", couleurBlanche);
					moins = TTF_RenderText_Blended(police, "-", couleurBlanche);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (event.motion.x > pos_plus.x && event.motion.x < pos_plus.x + plus->w && event.motion.y > pos_plus.y && event.motion.y < pos_plus.y + plus->h)
					{
						p->volume += 24;
						p->mute = 0;
						switch (p->volume)
						{
						case 0:
							p->mute = 1;
							volume_bar = NULL;
							break;
						case 24:
							volume_bar = IMG_Load("../img/menu/buttons/1_bar.png");
							break;
						case 48:
							volume_bar = IMG_Load("../img/menu/buttons/2_bars.png");
							break;
						case 72:
							volume_bar = IMG_Load("../img/menu/buttons/3_bars.png");
							break;
						case 96:
							volume_bar = IMG_Load("../img/menu/buttons/4_bars.png");
							break;
						case 120:
							volume_bar = IMG_Load("../img/menu/buttons/5_bars.png");
							break;
						}
					}
					else if (event.motion.x > pos_moins.x && event.motion.x < pos_moins.x + moins->w && event.motion.y > pos_moins.y && event.motion.y < pos_moins.y + moins->h)
					{

						p->volume -= 24;
						switch (p->volume)
						{
						case 0:
							p->mute = 1;
							volume_bar = NULL;
							break;
						case 24:
							volume_bar = IMG_Load("../img/menu/buttons/1_bar.png");
							break;
						case 48:
							volume_bar = IMG_Load("../img/menu/buttons/2_bars.png");
							break;
						case 72:
							volume_bar = IMG_Load("../img/menu/buttons/3_bars.png");
							break;
						case 96:
							volume_bar = IMG_Load("../img/menu/buttons/4_bars.png");
							break;
						case 120:
							volume_bar = IMG_Load("../img/menu/buttons/5_bars.png");
							break;
						}
					}
					else if (event.motion.x > pos_mute.x && event.motion.x < pos_mute.x + mute->w && event.motion.y > pos_mute.y && event.motion.y < pos_mute.y + mute->h)
					{
						Mix_PlayChannel(-1, p->click, 0);
						if (p->mute == 0)
						{
							Mix_PauseMusic();
							mute = IMG_Load("../img/menu/buttons/mute_active_tick.png");
							p->mute = 1;
						}
						else
						{
							Mix_ResumeMusic();
							mute = IMG_Load("../img/menu/buttons/mute_active.png");
							p->mute = 0;
						}
					}
					else if (event.motion.x > pos_full.x && event.motion.x < pos_full.x + full->w && event.motion.y > pos_full.y && event.motion.y < pos_full.y + full->h)
					{
						Mix_PlayChannel(-1, p->click, 0);
						if (p->fullscreen == 0)
						{
							screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
							full = IMG_Load("../img/menu/buttons/full_active_tick.png");
							p->fullscreen = 1;
						}
						else
						{
							screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
							full = IMG_Load("../img/menu/buttons/full_active.png");
							p->fullscreen = 0;
						}
					}
					else if (event.motion.x > pos_back.x && event.motion.x < pos_back.x + back->w && event.motion.y > pos_back.y && event.motion.y < pos_back.y + back->h)
					{
						Mix_PlayChannel(-1, p->click, 0);
						continuer = 0;
						*etat = MENU;
					}
				}
				break;
			}
		}
		SDL_BlitSurface(background, NULL, screen, &pos_backg);
		SDL_BlitSurface(screen_mode, NULL, screen, &pos_screen);
		SDL_BlitSurface(full, NULL, screen, &pos_full);
		SDL_BlitSurface(sound, NULL, screen, &pos_sound);
		SDL_BlitSurface(mute, NULL, screen, &pos_mute);
		SDL_BlitSurface(back, NULL, screen, &pos_back);
		SDL_BlitSurface(volume_bar, NULL, screen, &pos_vol_bar);
		SDL_BlitSurface(plus, NULL, screen, &pos_plus);
		SDL_BlitSurface(moins, NULL, screen, &pos_moins);
		Mix_VolumeMusic(p->volume);
		SDL_Flip(screen);
	}
	SDL_FreeSurface(background);
}
void initialiser_parameters(parameter *p)
{
	p->mute = 0;
	p->volume = 120;
	p->fullscreen = 0;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		printf("%s", Mix_GetError());
	}
	p->music = Mix_LoadMUS("../sfx/game_menu_music.wav");
	p->click = Mix_LoadWAV("../sfx/click.wav");
	//p->keyboard_click=Mix_LoadWAV("../sfx/keyboard_click.wav");
	Mix_PlayMusic(p->music, -1);
	Mix_VolumeMusic(p->volume);
}

void menu(SDL_Surface *screen, etat *etat, parameter *p)
{
	static int i = 250;
	static int once = 0;
	once++;
	SDL_Surface *black = IMG_Load("../img/black.jpg");

	SDL_Rect position_black;
	position_black.x = 0;
	position_black.y = 0;
	SDL_Event event;

	SDL_Surface *backgroundP = NULL;
	SDL_Surface *note = NULL, *loop = NULL;
	SDL_Surface *coffeeLogo;
	SDL_Rect positionCoffeeLogo;
	SDL_Rect positionBackgroundP;
	SDL_Rect positionNote, positionLoop;

	SDL_Rect positionClic;
	text text;

	SDL_Surface *rotation = NULL;
	SDL_Rect rect;

	button buttons[6];

	buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlay.png");
	buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettings.png");
	buttons[CREDITS].image = IMG_Load("../img/menu/buttons/buttonCredits.png");
	buttons[BONUS].image = IMG_Load("../img/menu/buttons/buttonBonus.png");
	buttons[QUIT].image = IMG_Load("../img/menu/buttons/buttonQuit.png");

	buttons[PLAY].position.x = 227;
	buttons[PLAY].position.y = 219;
	buttons[SETTINGS].position.x = 227;
	buttons[SETTINGS].position.y = 244;
	buttons[CREDITS].position.x = 227;
	buttons[CREDITS].position.y = 269;
	buttons[BONUS].position.x = 227;
	buttons[BONUS].position.y = 294;
	buttons[QUIT].position.x = 229;
	buttons[QUIT].position.y = 319;

	int continuer = 1;
	int rang = 0;
	int tempsActuel = 0, tempsPrecedent = 0;
	int t = 0, ind = 1;
	int choice;

	int verif = 0;

	if (TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	initialiser_text(&text, "© 2020 All rights reserved, Professional Rookies", 510, 590, 10);

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("unable to initialize SDL : %s\n", SDL_GetError());
	}

	if (!p->fullscreen)
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	else
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);

	if (!p->mute)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();

	backgroundP = SDL_LoadBMP("../img/menu/background/backgroundP.bmp");

	buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlay.png");
	buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettings.png");
	buttons[CREDITS].image = IMG_Load("../img/menu/buttons/buttonCredits.png");
	buttons[BONUS].image = IMG_Load("../img/menu/buttons/buttonBonus.png");
	buttons[QUIT].image = IMG_Load("../img/menu/buttons/buttonQuit.png");
	coffeeLogo = IMG_Load("../img/menu/objects/coffeeLogo1.png");
	loop = NULL;

	positionBackgroundP.x = 0;
	positionBackgroundP.y = 0;

	positionCoffeeLogo.x = 500;
	positionCoffeeLogo.y = 100;
	positionNote.x = 348;
	positionNote.y = 150;
	positionLoop.x = 0;
	positionLoop.y = 0;
	while (continuer)
	{

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_RETURN:
					if (rang == 1 && verif == 0)
					{
						Mix_PlayChannel(-1, p->click, 0);
						//Mix_PauseMusic();
						*etat = GAME_LOAD;
						continuer = 0;
						verif = 1;
						Mix_ResumeMusic();
					}
					if (rang == 2)
					{
						Mix_PlayChannel(-1, p->click, 0);
						buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettingsSelected.png");
						*etat = SETTING;
						continuer = 0;
						//settings(screen, p);
					}
					if (rang == 3)
					{
						Mix_PlayChannel(-1, p->click, 0);
						*etat = CREDS;
						continuer = 0;
					}
					if (rang == 4)
					{
						Mix_PlayChannel(-1, p->click, 0);
						*etat = CHEAT;
						continuer = 0;
					}
					if (rang == 5)
					{
						Mix_PlayChannel(-1, p->click, 0);
						buttons[QUIT].image = IMG_Load("../img/menu/buttons/buttonQuitSelected.png");
						continuer = 0;
						*etat = EXIT;
					}
					break;
				case SDLK_DOWN:
					if (rang == 0)
					{
						buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlayActive.png");
						Mix_PlayChannel(-1, p->click, 0);
						rang++;
					}
					else if (rang == 1)
					{
						buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlay.png");
						buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettingsActive.png");
						Mix_PlayChannel(-1, p->click, 0);
						rang++;
					}
					else if (rang == 2)
					{
						buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettings.png");
						buttons[CREDITS].image = IMG_Load("../img/menu/buttons/buttonCreditsActive.png");
						Mix_PlayChannel(-1, p->click, 0);
						rang++;
					}
					else if (rang == 3)
					{
						buttons[BONUS].image = IMG_Load("../img/menu/buttons/buttonBonusActive.png");
						buttons[CREDITS].image = IMG_Load("../img/menu/buttons/buttonCredits.png");
						Mix_PlayChannel(-1, p->click, 0);
						rang++;
					}
					else if (rang == 4)
					{
						buttons[BONUS].image = IMG_Load("../img/menu/buttons/buttonBonus.png");
						buttons[QUIT].image = IMG_Load("../img/menu/buttons/buttonQuitActive.png");
						Mix_PlayChannel(-1, p->click, 0);
						rang++;
					}
					else if (rang == 5)
					{
						buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlayActive.png");
						buttons[QUIT].image = IMG_Load("../img/menu/buttons/buttonQuit.png");
						Mix_PlayChannel(-1, p->click, 0);
						rang = 1;
					}
					break;
				case SDLK_UP:
					if (rang == 5)
					{
						buttons[QUIT].image = IMG_Load("../img/menu/buttons/buttonQuit.png");
						buttons[BONUS].image = IMG_Load("../img/menu/buttons/buttonBonusActive.png");
						Mix_PlayChannel(-1, p->click, 0);
						rang--;
					}
					else if (rang == 4)
					{
						buttons[BONUS].image = IMG_Load("../img/menu/buttons/buttonBonus.png");
						buttons[CREDITS].image = IMG_Load("../img/menu/buttons/buttonCreditsActive.png");
						Mix_PlayChannel(-1, p->click, 0);
						rang--;
					}
					else if (rang == 3)
					{
						buttons[CREDITS].image = IMG_Load("../img/menu/buttons/buttonCredits.png");
						buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettingsActive.png");
						Mix_PlayChannel(-1, p->click, 0);
						rang--;
					}
					else if (rang == 2)
					{
						buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettings.png");
						buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlayActive.png");
						Mix_PlayChannel(-1, p->click, 0);
						rang--;
					}
					else if (rang == 1)
					{
						buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettings.png");
						buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlay.png");
						buttons[QUIT].image = IMG_Load("../img/menu/buttons/buttonQuitActive.png");
						Mix_PlayChannel(-1, p->click, 0);
						rang = 5;
					}
					else if (rang == 0)
					{
						buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlayActive.png");
						Mix_PlayChannel(-1, p->click, 0);
						rang = 1;
					}
				}
				break;
			case SDL_MOUSEMOTION:
				if (event.motion.x > buttons[PLAY].position.x && event.motion.x < buttons[PLAY].position.x + buttons[PLAY].image->w && event.motion.y > buttons[PLAY].position.y && event.motion.y < buttons[PLAY].position.y + buttons[PLAY].image->h)
				{
					buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlayActive.png");
					buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettings.png");
					buttons[CREDITS].image = IMG_Load("../img/menu/buttons/buttonCredits.png");
					buttons[BONUS].image = IMG_Load("../img/menu/buttons/buttonBonus.png");
					buttons[QUIT].image = IMG_Load("../img/menu/buttons/buttonQuit.png");
					rang = 1;
				}
				else if (event.motion.x > buttons[SETTINGS].position.x && event.motion.x < buttons[SETTINGS].position.x + buttons[SETTINGS].image->w && event.motion.y > buttons[SETTINGS].position.y && event.motion.y < buttons[SETTINGS].position.y + buttons[SETTINGS].image->h)
				{
					buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlay.png");
					buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettingsActive.png");
					buttons[CREDITS].image = IMG_Load("../img/menu/buttons/buttonCredits.png");
					buttons[BONUS].image = IMG_Load("../img/menu/buttons/buttonBonus.png");
					buttons[QUIT].image = IMG_Load("../img/menu/buttons/buttonQuit.png");
					rang = 2;
				}
				else if (event.motion.x > buttons[CREDITS].position.x && event.motion.x < buttons[CREDITS].position.x + buttons[CREDITS].image->w && event.motion.y > buttons[CREDITS].position.y && event.motion.y < buttons[CREDITS].position.y + buttons[CREDITS].image->h)
				{
					buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlay.png");
					buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettings.png");
					buttons[CREDITS].image = IMG_Load("../img/menu/buttons/buttonCreditsActive.png");
					buttons[BONUS].image = IMG_Load("../img/menu/buttons/buttonBonus.png");
					buttons[QUIT].image = IMG_Load("../img/menu/buttons/buttonQuit.png");
					rang = 3;
				}
				else if (event.motion.x > buttons[BONUS].position.x && event.motion.x < buttons[BONUS].position.x + buttons[BONUS].image->w && event.motion.y > buttons[BONUS].position.y && event.motion.y < buttons[BONUS].position.y + buttons[BONUS].image->h)
				{
					buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlay.png");
					buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettings.png");
					buttons[CREDITS].image = IMG_Load("../img/menu/buttons/buttonCredits.png");
					buttons[BONUS].image = IMG_Load("../img/menu/buttons/buttonBonusActive.png");
					buttons[QUIT].image = IMG_Load("../img/menu/buttons/buttonQuit.png");
					rang = 4;
				}
				else if (event.motion.x > buttons[QUIT].position.x && event.motion.x < buttons[QUIT].position.x + buttons[QUIT].image->w && event.motion.y > buttons[QUIT].position.y && event.motion.y < buttons[QUIT].position.y + buttons[QUIT].image->h)
				{
					buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlay.png");
					buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettings.png");
					buttons[CREDITS].image = IMG_Load("../img/menu/buttons/buttonCredits.png");
					buttons[BONUS].image = IMG_Load("../img/menu/buttons/buttonBonus.png");
					buttons[QUIT].image = IMG_Load("../img/menu/buttons/buttonQuitActive.png");
					rang = 5;
				}
				else if (event.motion.x > 500 && event.motion.x < 672 && event.motion.y > 400 && event.motion.y < 568)
				{
					SDL_ShowCursor(SDL_DISABLE);
					loop = IMG_Load("../img/menu/objects/loop.png");
					positionLoop.x = event.motion.x;
					positionLoop.y = event.motion.y;
				}
				else
				{

					buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlay.png");
					buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettings.png");
					buttons[CREDITS].image = IMG_Load("../img/menu/buttons/buttonCredits.png");
					buttons[BONUS].image = IMG_Load("../img/menu/buttons/buttonBonus.png");
					buttons[QUIT].image = IMG_Load("../img/menu/buttons/buttonQuit.png");
					note = NULL;
					loop = NULL;
					SDL_ShowCursor(SDL_ENABLE);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (verif == 0 && event.motion.x > buttons[PLAY].position.x && event.motion.x < buttons[PLAY].position.x + buttons[PLAY].image->w && event.motion.y > buttons[PLAY].position.y && event.motion.y < buttons[PLAY].position.y + buttons[PLAY].image->h)
					{
						Mix_PlayChannel(-1, p->click, 0);
						Mix_PauseMusic();
						buttons[PLAY].image = IMG_Load("../img/menu/buttons/buttonPlaySelected.png");
						*etat = GAME_LOAD;
						continuer = 0;
						verif = 1;
						Mix_ResumeMusic();
					}
					else if (event.motion.x > buttons[SETTINGS].position.x && event.motion.x < buttons[SETTINGS].position.x + buttons[SETTINGS].image->w && event.motion.y > buttons[SETTINGS].position.y && event.motion.y < buttons[SETTINGS].position.y + buttons[SETTINGS].image->h)
					{
						Mix_PlayChannel(-1, p->click, 0);
						buttons[SETTINGS].image = IMG_Load("../img/menu/buttons/buttonSettingsSelected.png");
						*etat = SETTING;
						continuer = 0;
						//settings(screen, p);
					}
					else if (event.motion.x > buttons[CREDITS].position.x && event.motion.x < buttons[CREDITS].position.x + buttons[CREDITS].image->w && event.motion.y > buttons[CREDITS].position.y && event.motion.y < buttons[CREDITS].position.y + buttons[CREDITS].image->h)
					{
						Mix_PlayChannel(-1, p->click, 0);
						buttons[CREDITS].image = IMG_Load("../img/menu/buttons/buttonCreditsSelected.png");
					}
					else if (event.motion.x > buttons[BONUS].position.x && event.motion.x < buttons[BONUS].position.x + buttons[BONUS].image->w && event.motion.y > buttons[BONUS].position.y && event.motion.y < buttons[BONUS].position.y + buttons[BONUS].image->h)
					{
						Mix_PlayChannel(-1, p->click, 0);
						buttons[BONUS].image = IMG_Load("../img/menu/buttons/buttonBonusSelected.png");
					}
					else if (event.motion.x > buttons[QUIT].position.x && event.motion.x < buttons[QUIT].position.x + buttons[QUIT].image->w && event.motion.y > buttons[QUIT].position.y && event.motion.y < buttons[QUIT].position.y + buttons[QUIT].image->h)
					{
						Mix_PlayChannel(-1, p->click, 0);
						buttons[QUIT].image = IMG_Load("../img/menu/buttons/buttonQuitSelected.png");
						continuer = 0;
						*etat = EXIT;
					}
					else if (event.motion.x > 500 && event.motion.x < 672 && event.motion.y > 400 && event.motion.y < 568)
					{
						if (note == NULL)
						{
							Mix_PlayChannel(-1, p->click, 0);
							note = IMG_Load("../img/menu/objects/note.png");
						}
						else
						{
							Mix_PlayChannel(-1, p->click, 0);
							note = NULL;
						}
					}
				}
				break;
			}
		}
		//animation
		tempsActuel = SDL_GetTicks();
		if (tempsActuel - tempsPrecedent > 80)
		{
			if (t == 50)
				coffeeLogo = IMG_Load("../img/menu/objects/coffeeLogo2.png");
			else if (t == 100)
				coffeeLogo = IMG_Load("../img/menu/objects/coffeeLogo3.png");
			else if (t == 150)
				coffeeLogo = IMG_Load("../img/menu/objects/coffeeLogo4.png");
			else if (t == 200)
			{
				coffeeLogo = IMG_Load("../img/menu/objects/coffeeLogo1.png");
				t = 0;
			}
			if (positionCoffeeLogo.y == 100 && ind == 1)
				ind = 0;
			if (positionCoffeeLogo.y == 120 && ind == 0)
				ind = 1;
			if (positionCoffeeLogo.y >= 100 && ind == 0 && positionCoffeeLogo.y <= 120)
			{
				positionCoffeeLogo.y++;
			}
			if (positionCoffeeLogo.y <= 120 && ind == 1 && positionCoffeeLogo.y >= 100)
			{
				positionCoffeeLogo.y--;
			}
			tempsPrecedent = tempsActuel;
			t++;
		}
		//fin animation

		SDL_BlitSurface(backgroundP, NULL, screen, &positionBackgroundP);
		for (choice = 0; choice < 5; choice++)
		{
			SDL_BlitSurface(buttons[choice].image, NULL, screen, &buttons[choice].position);
		}
		SDL_BlitSurface(coffeeLogo, NULL, screen, &positionCoffeeLogo);
		SDL_BlitSurface(text.text, NULL, screen, &text.position);
		SDL_BlitSurface(note, NULL, screen, &positionNote);
		SDL_BlitSurface(loop, NULL, screen, &positionLoop);
		if (i != 0 && once <= 1)
		{
			SDL_SetAlpha(black, SDL_SRCALPHA, i);
			i--;
		}
		else
		{
			SDL_SetAlpha(black, SDL_SRCALPHA, 0);
		}

		SDL_BlitSurface(black, NULL, screen, &position_black);
		SDL_Flip(screen);
	}
	SDL_FreeSurface(backgroundP);
	for (choice = 0; choice < 5; choice++)
	{
		SDL_FreeSurface(buttons[choice].image);
	}
	TTF_Quit();
	SDL_FreeSurface(loop);
}
