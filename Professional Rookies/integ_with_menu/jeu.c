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
	int verif=0;

	initialiser_hero(&safwen, "safwen");
	initialiser_background(&background);
	initialiser_entite(&enemie);
	printf("%d %d",safwen.position.x,safwen.position.y);
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_EnableKeyRepeat(2, 2);

	//ecran = SDL_SetVideoMode(SCREEN_WIDTH+320, SCREEN_HEIGHT+120, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	while (Jcontinuer)
	{

		CollisionParfaite(&safwen, background);

		while (SDL_PollEvent(&event))
		{
			deplacer_hero(&safwen, event);
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				Jcontinuer = 0;
				break;
			}
		}
		if (safwen.position.x >= 666 && verif == 0)
		{
			enigme_math(ecran);
			verif = 1;
		}
		//attack_entite(&enemie,&safwen);


		deplacer_hero(&safwen, event); //gravity and acceleration
		animer_hero(&safwen, safwen.state);
		deplacer_alea(&enemie);
		animer_entite(&enemie);
		afficher_background(&background, ecran);
		afficher_entite(&enemie, ecran);
		afficher_hero(safwen, ecran);
		SDL_Flip(ecran);
	}

	free_background(&background);
	free_entite(&enemie);
	free_hero(&safwen);
	SDL_Quit();


}