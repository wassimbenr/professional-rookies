#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "defs.h"
#include "structs.h"
#include "jeu.h"
#include "settings.h"
int menu(etat *etat)
{
	SDL_Surface *screen = NULL;
	SDL_Surface *backgroundP = NULL;
	SDL_Surface *buttonPlay = NULL, *buttonSettings = NULL, *buttonCredits = NULL, *buttonQuit = NULL, *buttonBonus = NULL, *note = NULL, *loop = NULL;
	SDL_Surface *coffeeLogo;
	SDL_Rect positionCoffeeLogo;
	SDL_Rect positionBackgroundP;
	SDL_Rect positionPlay, positionSettings, positionCredits, positionBonus, positionQuit, positionNote, positionLoop;
	Mix_Music *music;
	Mix_Chunk *click;
	SDL_Rect positionText, positionClic;
	SDL_Color couleurBlanche = {255, 255, 255};
	TTF_Font *police = NULL;
	SDL_Surface *texte = NULL;
	SDL_Event event;
	int continuer = 1;
	int u = 0, fs = 0;
	int rang = 0;
	int volume = 120;
	int tempsActuel = 0, tempsPrecedent = 0;
	int t = 0, ind = 1;

	int verif = 0;

	SDL_WM_SetCaption("--- Menu Principal --- ", NULL);
	if (TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	//Son Continu
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		printf("%s", Mix_GetError());
	}
	music = Mix_LoadMUS("./img/menu/game_menu_music.wav");
	click = Mix_LoadWAV("./img/menu/click.wav");
	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(volume);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("unable to initialize SDL : %s\n", SDL_GetError());
		return 1;
	}
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (screen == NULL)
	{
		printf("unable to set video mode : %s\n", SDL_GetError());
		return 1;
	}
	backgroundP = SDL_LoadBMP("./img/menu/backgroundP.bmp");
	if (backgroundP == NULL)
	{
		printf("unable to set load bitmap : %s\n", SDL_GetError());
		return 1;
	}
	buttonPlay = IMG_Load("./img/menu/buttonPlay.png");
	buttonSettings = IMG_Load("./img/menu/buttonSettings.png");
	buttonCredits = IMG_Load("./img/menu/buttonCredits.png");
	buttonBonus = IMG_Load("./img/menu/buttonBonus.png");
	buttonQuit = IMG_Load("./img/menu/buttonQuit.png");
	coffeeLogo = IMG_Load("./img/menu/coffeeLogo1.png");
	loop = IMG_Load("./img/menu/loop.png");
	if (buttonPlay == NULL || buttonSettings == NULL || buttonBonus == NULL || buttonCredits == NULL || buttonQuit == NULL)
	{
		printf("unable to set load png : %s\n", SDL_GetError());
		return 1;
	}

	police = TTF_OpenFont("./img/menu/angelina.TTF", 15);
	texte = TTF_RenderText_Blended(police, "© 2020 All rights reserved, Professional Rookies", couleurBlanche);
	positionBackgroundP.x = 0;
	positionBackgroundP.y = 0;

	positionPlay.x = 227;
	positionPlay.y = 219;
	positionSettings.x = 227;
	positionSettings.y = 244;
	positionCredits.x = 227;
	positionCredits.y = 269;
	positionBonus.x = 227;
	positionBonus.y = 294;
	positionQuit.x = 229;
	positionQuit.y = 319;
	positionText.x = screen->w - texte->w - 10;
	positionText.y = 580;
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
						Mix_PlayChannel(-1, click, 0);
						Mix_PauseMusic();
						//etat=GAME;
						jeu(screen);
						verif = 1;
						Mix_ResumeMusic();
					}
					if (rang == 2)
					{
						Mix_PlayChannel(-1, click, 0);
						buttonSettings = IMG_Load("./img/menu/buttonSettingsSelected.png");
						settings(screen, &u, &fs, &volume);
					}
					if (rang == 5)
					{
						Mix_PlayChannel(-1, click, 0);
						buttonQuit = IMG_Load("./img/menu/buttonQuitSelected.png");
						continuer = 0;
						*etat=EXIT;
					}
					break;
				case SDLK_DOWN:
					if (rang == 0)
					{
						buttonPlay = IMG_Load("./img/menu/buttonPlayActive.png");
						Mix_PlayChannel(-1, click, 0);
						rang++;
					}
					else if (rang == 1)
					{
						buttonPlay = IMG_Load("./img/menu/buttonPlay.png");
						buttonSettings = IMG_Load("./img/menu/buttonSettingsActive.png");
						Mix_PlayChannel(-1, click, 0);
						rang++;
					}
					else if (rang == 2)
					{
						buttonSettings = IMG_Load("./img/menu/buttonSettings.png");
						buttonCredits = IMG_Load("./img/menu/buttonCreditsActive.png");
						Mix_PlayChannel(-1, click, 0);
						rang++;
					}
					else if (rang == 3)
					{
						buttonBonus = IMG_Load("./img/menu/buttonBonusActive.png");
						buttonCredits = IMG_Load("./img/menu/buttonCredits.png");
						Mix_PlayChannel(-1, click, 0);
						rang++;
					}
					else if (rang == 4)
					{
						buttonBonus = IMG_Load("./img/menu/buttonBonus.png");
						buttonQuit = IMG_Load("./img/menu/buttonQuitActive.png");
						Mix_PlayChannel(-1, click, 0);
						rang++;
					}
					else if (rang == 5)
					{
						buttonPlay = IMG_Load("./img/menu/buttonPlayActive.png");
						buttonQuit = IMG_Load("./img/menu/buttonQuit.png");
						Mix_PlayChannel(-1, click, 0);
						rang = 1;
					}
					break;
				case SDLK_UP:
					if (rang == 5)
					{
						buttonQuit = IMG_Load("./img/menu/buttonQuit.png");
						buttonBonus = IMG_Load("./img/menu/buttonBonusActive.png");
						Mix_PlayChannel(-1, click, 0);
						rang--;
					}
					else if (rang == 4)
					{
						buttonBonus = IMG_Load("./img/menu/buttonBonus.png");
						buttonCredits = IMG_Load("./img/menu/buttonCreditsActive.png");
						Mix_PlayChannel(-1, click, 0);
						rang--;
					}
					else if (rang == 3)
					{
						buttonCredits = IMG_Load("./img/menu/buttonCredits.png");
						buttonSettings = IMG_Load("./img/menu/buttonSettingsActive.png");
						Mix_PlayChannel(-1, click, 0);
						rang--;
					}
					else if (rang == 2)
					{
						buttonSettings = IMG_Load("./img/menu/buttonSettings.png");
						buttonPlay = IMG_Load("./img/menu/buttonPlayActive.png");
						Mix_PlayChannel(-1, click, 0);
						rang--;
					}
					else if (rang == 1)
					{
						buttonSettings = IMG_Load("./img/menu/buttonSettings.png");
						buttonPlay = IMG_Load("./img/menu/buttonPlay.png");
						buttonQuit = IMG_Load("./img/menu/buttonQuitActive.png");
						Mix_PlayChannel(-1, click, 0);
						rang = 5;
					}
					else if (rang == 0)
					{
						buttonPlay = IMG_Load("./img/menu/buttonPlayActive.png");
						Mix_PlayChannel(-1, click, 0);
						rang = 1;
					}
				}
				break;
			case SDL_MOUSEMOTION:
				if (event.motion.x > positionPlay.x && event.motion.x < positionPlay.x + buttonPlay->w && event.motion.y > positionPlay.y && event.motion.y < positionPlay.y + buttonPlay->h)
				{
					buttonPlay = IMG_Load("./img/menu/buttonPlayActive.png");
					buttonSettings = IMG_Load("./img/menu/buttonSettings.png");
					buttonCredits = IMG_Load("./img/menu/buttonCredits.png");
					buttonBonus = IMG_Load("./img/menu/buttonBonus.png");
					buttonQuit = IMG_Load("./img/menu/buttonQuit.png");
					rang = 1;
				}
				else if (event.motion.x > positionSettings.x && event.motion.x < positionSettings.x + buttonSettings->w && event.motion.y > positionSettings.y && event.motion.y < positionSettings.y + buttonSettings->h)
				{
					buttonPlay = IMG_Load("./img/menu/buttonPlay.png");
					buttonSettings = IMG_Load("./img/menu/buttonSettingsActive.png");
					buttonCredits = IMG_Load("./img/menu/buttonCredits.png");
					buttonBonus = IMG_Load("./img/menu/buttonBonus.png");
					buttonQuit = IMG_Load("./img/menu/buttonQuit.png");
					rang = 2;
				}
				else if (event.motion.x > positionCredits.x && event.motion.x < positionCredits.x + buttonCredits->w && event.motion.y > positionCredits.y && event.motion.y < positionCredits.y + buttonCredits->h)
				{
					buttonPlay = IMG_Load("./img/menu/buttonPlay.png");
					buttonSettings = IMG_Load("./img/menu/buttonSettings.png");
					buttonCredits = IMG_Load("./img/menu/buttonCreditsActive.png");
					buttonBonus = IMG_Load("./img/menu/buttonBonus.png");
					buttonQuit = IMG_Load("./img/menu/buttonQuit.png");
					rang = 3;
				}
				else if (event.motion.x > positionBonus.x && event.motion.x < positionBonus.x + buttonBonus->w && event.motion.y > positionBonus.y && event.motion.y < positionBonus.y + buttonBonus->h)
				{
					buttonPlay = IMG_Load("./img/menu/buttonPlay.png");
					buttonSettings = IMG_Load("./img/menu/buttonSettings.png");
					buttonCredits = IMG_Load("./img/menu/buttonCredits.png");
					buttonBonus = IMG_Load("./img/menu/buttonBonusActive.png");
					buttonQuit = IMG_Load("./img/menu/buttonQuit.png");
					rang = 4;
				}
				else if (event.motion.x > positionQuit.x && event.motion.x < positionQuit.x + buttonQuit->w && event.motion.y > positionQuit.y && event.motion.y < positionQuit.y + buttonQuit->h)
				{
					buttonPlay = IMG_Load("./img/menu/buttonPlay.png");
					buttonSettings = IMG_Load("./img/menu/buttonSettings.png");
					buttonCredits = IMG_Load("./img/menu/buttonCredits.png");
					buttonBonus = IMG_Load("./img/menu/buttonBonus.png");
					buttonQuit = IMG_Load("./img/menu/buttonQuitActive.png");
					rang = 5;
				}
				else if (event.motion.x > 500 && event.motion.x < 672 && event.motion.y > 400 && event.motion.y < 568)
				{
					SDL_ShowCursor(SDL_DISABLE);
					loop = IMG_Load("./img/menu/loop.png");
					positionLoop.x = event.motion.x;
					positionLoop.y = event.motion.y;
				}
				else
				{

					buttonPlay = IMG_Load("./img/menu/buttonPlay.png");
					buttonSettings = IMG_Load("./img/menu/buttonSettings.png");
					buttonCredits = IMG_Load("./img/menu/buttonCredits.png");
					buttonBonus = IMG_Load("./img/menu/buttonBonus.png");
					buttonQuit = IMG_Load("./img/menu/buttonQuit.png");
					note = NULL;
					loop = NULL;
					SDL_ShowCursor(SDL_ENABLE);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (verif == 0 && event.motion.x > positionPlay.x && event.motion.x < positionPlay.x + buttonPlay->w && event.motion.y > positionPlay.y && event.motion.y < positionPlay.y + buttonPlay->h)
					{
						Mix_PlayChannel(-1, click, 0);
						Mix_PauseMusic();
						buttonPlay = IMG_Load("./img/menu/buttonPlaySelected.png");
						jeu(screen);
						verif = 1;
						Mix_ResumeMusic();
					}
					else if (event.motion.x > positionSettings.x && event.motion.x < positionSettings.x + buttonSettings->w && event.motion.y > positionSettings.y && event.motion.y < positionSettings.y + buttonSettings->h)
					{
						Mix_PlayChannel(-1, click, 0);
						buttonSettings = IMG_Load("./img/menu/buttonSettingsSelected.png");
						settings(screen, &u, &fs, &volume);
					}
					else if (event.motion.x > positionCredits.x && event.motion.x < positionCredits.x + buttonCredits->w && event.motion.y > positionCredits.y && event.motion.y < positionCredits.y + buttonCredits->h)
					{
						Mix_PlayChannel(-1, click, 0);
						buttonCredits = IMG_Load("./img/menu/buttonCreditsSelected.png");
					}
					else if (event.motion.x > positionBonus.x && event.motion.x < positionBonus.x + buttonBonus->w && event.motion.y > positionBonus.y && event.motion.y < positionBonus.y + buttonBonus->h)
					{
						Mix_PlayChannel(-1, click, 0);
						buttonBonus = IMG_Load("./img/menu/buttonBonusSelected.png");
					}
					else if (event.motion.x > positionQuit.x && event.motion.x < positionQuit.x + buttonQuit->w && event.motion.y > positionQuit.y && event.motion.y < positionQuit.y + buttonQuit->h)
					{
						Mix_PlayChannel(-1, click, 0);
						buttonQuit = IMG_Load("./img/menu/buttonQuitSelected.png");
						continuer = 0;
						*etat=EXIT;
					}
					else if (event.motion.x > 500 && event.motion.x < 672 && event.motion.y > 400 && event.motion.y < 568)
					{
						if (note == NULL)
						{
							Mix_PlayChannel(-1, click, 0);
							note = IMG_Load("./img/menu/note.png");
						}
						else
						{
							Mix_PlayChannel(-1, click, 0);
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
				coffeeLogo = IMG_Load("./img/menu/coffeeLogo2.png");
			else if (t == 100)
				coffeeLogo = IMG_Load("./img/menu/coffeeLogo3.png");
			else if (t == 150)
				coffeeLogo = IMG_Load("./img/menu/coffeeLogo4.png");
			else if (t == 200)
			{
				coffeeLogo = IMG_Load("./img/menu/coffeeLogo1.png");
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
		SDL_BlitSurface(buttonPlay, NULL, screen, &positionPlay);
		SDL_BlitSurface(buttonSettings, NULL, screen, &positionSettings);
		SDL_BlitSurface(buttonBonus, NULL, screen, &positionBonus);
		SDL_BlitSurface(buttonCredits, NULL, screen, &positionCredits);
		SDL_BlitSurface(buttonQuit, NULL, screen, &positionQuit);
		SDL_BlitSurface(coffeeLogo, NULL, screen, &positionCoffeeLogo);
		SDL_BlitSurface(texte, NULL, screen, &positionText);
		SDL_BlitSurface(note, NULL, screen, &positionNote);
		SDL_BlitSurface(loop, NULL, screen, &positionLoop);
		SDL_Flip(screen);
	}
	SDL_FreeSurface(backgroundP);
	SDL_FreeSurface(buttonPlay);
	SDL_FreeSurface(buttonCredits);
	SDL_FreeSurface(buttonSettings);
	SDL_FreeSurface(buttonBonus);
	SDL_FreeSurface(buttonQuit);
	Mix_FreeMusic(music);
	Mix_FreeChunk(click);
	TTF_CloseFont(police);
	TTF_Quit();
	SDL_FreeSurface(texte);
	SDL_FreeSurface(loop);
	SDL_Quit();
	return 0;
}
