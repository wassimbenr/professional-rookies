#include "background.h"
#include "entite_secondaire.h"
#include "hero.h"
#include "colision.h"
#include "defs.h"
#include "enigme.h"

void jeu(SDL_Surface *ecran)
{
	hero safwen;
	background background;
	entite enemie;

	int Jcontinuer = 1;
	int verif = 0;

	initialiser_hero(&safwen, "safwen");
	initialiser_background(&background);
	initialiser_entite(&enemie);

	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_EnableKeyRepeat(2, 2);

	ecran = SDL_SetVideoMode(SCREEN_WIDTH+320, SCREEN_HEIGHT+120, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	while (Jcontinuer)
	{

		CollisionParfaite(&safwen, background);

		while (SDL_PollEvent(&event))
		{
			
			switch (event.type)
			{
			case SDL_KEYDOWN:
				
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					Jcontinuer = 0;
					break;
				case SDLK_d:
					animer_hero(&safwen,PUNCH);
					break;
				case SDLK_s:
					animer_hero(&safwen,KICK);
					break;
				}
				break;
			case SDL_KEYUP:
				if (safwen.state == WALK_RIGHT || safwen.state == WALK_LEFT)
					safwen.state = IDLE;
				break;
			}
			deplacer_hero(&safwen, event);
		}
		if (safwen.position.y==381 && safwen.position.x>=830 && verif ==0)
		{
			enigme_math(ecran);
			verif =1;
		}

		deplacer_hero(&safwen, event); //gravity and acceleration

		if (enemie.posMin.x > safwen.position.x)
			deplacer_alea(&enemie);

		attack_entite(&enemie, &safwen);

		animer_hero(&safwen, safwen.state);

		animer_entite(&enemie);
		afficher_background(&background, ecran);
		afficher_entite(&enemie, ecran);
		afficher_hero(safwen, ecran);
		SDL_Flip(ecran);

		//printf("safwen: %d %d\n", safwen.position.x, safwen.position.y);
		//printf("omar: %d %d\n", enemie.position.x, enemie.position.y);
	}

	free_background(&background);
	free_entite(&enemie);
	free_hero(&safwen);
	SDL_Quit();
}