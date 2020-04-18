#include "background.h"
#include "entite_secondaire.h"
#include "hero.h"
#include "colision.h"
#include "defs.h"
#include "enigme.h"

void jeu(SDL_Surface *ecran) //etat
{
	hero safwen;
	background background;//, cam
	entite enemie;
	enigme enigme_m;

	int Jcontinuer = 1;
	int verif = 0;

	initialiser_hero(&safwen, "safwen");
	initialiser_background(&background);
	//initialiser_background(&cam);
	initialiser_entite(&enemie);
	initenigme(&enigme_m);
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
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					Jcontinuer = 0;
					break;
				}
				break;
			}
		}
		if (safwen.position.y == 381 && safwen.position.x >= 830 && verif == 0)
		{
			enigme_math(ecran, &enigme_m);
			if (enigme_m.resolution == 1)
				safwen.score_hero.valeur_score += 50;
			else
				safwen.score_hero.valeur_score -= 50;
			verif = 1;
		}
		scrolling(&background,&safwen,event);
		deplacer_hero(&safwen, event);
		
		animer_hero(&safwen, safwen.state);
		//deplacer_alea(&enemie);
		//input_ennemi(&enemie, safwen.position);

		afficher_background(&background, ecran);
		//cameraXY(&cam, ecran);

		//afficher_entite(&enemie, ecran);
		afficher_hero(safwen, ecran);
		SDL_Flip(ecran);

		printf("camera x: \t%d \n", background.posCamera.x);
		printf("safwen: %d\t%d\n", safwen.position.x, safwen.position.x);
		printf("omar: %d\t%d\n", enemie.position.x, enemie.position.y);
	}
	free_background(&background);
	//free_background(&cam);
	//free_entite(&enemie);
	free_hero(&safwen);
	freeenigme(&enigme_m);
	SDL_Quit();
}