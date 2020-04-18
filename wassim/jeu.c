#include "background.h"
#include "entite_secondaire.h"
#include "hero.h"
#include "colision.h"
#include "defs.h"
#include "enigme.h"

void jeu(SDL_Surface *ecran)//etat 
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
	int nb = 0;
	while (Jcontinuer)
	{
		CollisionParfaite(&safwen, background);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				Jcontinuer = 0;
				//etat = EXIT;
				break;
			case SDL_KEYDOWN:
				//scrolling(&background, event);
				//deplacer_hero(&safwen, event);
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					Jcontinuer = 0;
					break;
				}
				break;
			}
			//deplacer_hero(&safwen, event);
		}
		if (safwen.position.x >= 706 && verif == 0)
		{
			enigme_math(ecran);
			verif = 1;
		}
		deplacer_hero(&safwen, event);
		//deplacer_alea(&enemie);
		//input_ennemi(&enemie, safwen.position);
		//animer_hero(&safwen, safwen.state);

		afficher_background(&background, ecran);
		//afficher_entite(&enemie, ecran);
		afficher_hero(safwen, ecran);

		SDL_Flip(ecran);

		printf("safwen: %d %d\n", safwen.position.x, safwen.position.x);
		printf("omar: %d %d\n", enemie.position.x, enemie.position.y);
	}
	free_background(&background);
	//free_entite(&enemie);
	free_hero(&safwen);
	SDL_Quit();
}