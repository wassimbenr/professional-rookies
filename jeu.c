#include "background.h"
#include "entite_secondaire.h"
#include "hero.h"
#include "colision.h"
#include "defs.h"
#include "enigme.h"
#include "structs.h"
void jeu(SDL_Surface *ecran, etat *etat) //etat
{
	hero safwen;
	background background;
	entite enemie;
	enigme enigme_m;

	int Jcontinuer = 1;
	int verif = 0;

	initialiser_hero(&safwen, "safwen");
	initialiser_background(&background);
	initialiser_entite(&enemie);
	initenigme(&enigme_m);
	SDL_Event event;

	
	int nb = 0;
	while (Jcontinuer)
	{
		deplacer_hero(&safwen, &background, &Jcontinuer);
		if (safwen.position.y == 380 && safwen.position.x >= 670 && verif == 0)
		{
			enigme_math(ecran, &enigme_m);
			if (enigme_m.resolution == 1)
				safwen.score_hero.valeur_score += 50;
			else
				safwen.score_hero.valeur_score -= 50;
			verif = 1;
		}
		printf("%d\t%d\n", safwen.vie_hero.nb_vie, safwen.score_hero.valeur_score);
		//deplacer_alea(&enemie);
		//if (enemie.posMin.x > safwen.position.x)

		CollisionParfaite(&safwen, background);

		attack_entite(&enemie, &safwen);
		//input_ennemi(&enemie, &safwen);
		animer_entite(&enemie);
		animer_hero(&safwen, safwen.state);
		afficher_background(&background, ecran);
		afficher_entite(&enemie, ecran);
		afficher_hero(safwen, ecran);
		SDL_Flip(ecran);
		printf("camera x: \t%d \n", background.posCamera.x);
		printf("safwen:%d.%d\t%d\tomar:%d.%d\n", safwen.position.x, safwen.position.y, collision(&enemie, &safwen), enemie.position.x, enemie.position.y);
		if (Jcontinuer == 0 && safwen.vie_hero.nb_vie != 0)
			(*etat) = EXIT;
		if (safwen.vie_hero.nb_vie == 0)
		{
			(*etat) = GAME_OVER;
			Jcontinuer = 0;
		}
	}
	free_background(&background);
	free_entite(&enemie);
	freeenigme(&enigme_m);
	free_hero(&safwen);
}