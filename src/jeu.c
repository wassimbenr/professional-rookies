#include "background.h"
#include "entite_secondaire.h"
#include "hero.h"
#include "collision.h"
#include "defs.h"
#include "enigme.h"
#include "structs.h"
#include "menu.h"

void jeu(SDL_Surface *ecran, etat *etat, hero safwen, parameter *p, character c, background background)
{
	SDL_Event event;
	int Jcontinuer = 1;
	int verif = 0;

	entite enemie;
	enigme enigme_m;
	power_up coin_1, coin_2;
	platforme platforme;
	text instruction_1, instruction_2, game_over_txt;

	initialiser_background(&background);
	initialiser_entite(&enemie);
	initenigme(&enigme_m);
	initialiser_pu(&coin_1, 1065, 1460);
	initialiser_pu(&coin_2, 1696, 1400);
	initialiser_platforme(&platforme, 1180, 1400);
	initialiser_text(&instruction_1, "Press the arrow keys to move around", 488, 1360, 30);
	initialiser_text(&instruction_2, "Press x to punch and c to kick", 1400, 1300, 30);
	initialiser_text(&game_over_txt, "GAME OVER", SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2, 90);

	p->music = Mix_LoadMUS("../sfx/alter-ego.mp3");
	if (!p->mute)
		Mix_PlayMusic(p->music, -1);
	else
		Mix_PauseMusic();
	if (p->fullscreen)
		SDL_WM_ToggleFullScreen(ecran);

	while (Jcontinuer)
	{

		deplacer_hero(&safwen, &background, &Jcontinuer, c, platforme);
		CollisionParfaite(&safwen, background, platforme);

		save_game(safwen, background, c);

		if (abs(safwen.position.x - enemie.position.x) <= 250 && abs(safwen.position.y - enemie.position.y) >= 0 && abs(safwen.position.y - enemie.position.y) <= 50)
			attack_entite(&enemie, &safwen);
		else
			deplacer_alea(&enemie);

		if (coin_1.sprite.image != NULL && safwen.position.x >= coin_1.position.x && safwen.position.x <= coin_1.position.x + coin_1.sprite.frame.w && safwen.position.y >= coin_1.position.y && safwen.position.y <= coin_1.position.y + coin_1.sprite.frame.h)
		{
			safwen.score_hero.valeur_score += 20;
			Mix_PlayChannel(-1, coin_1.click, 0);
			coin_1.sprite.image = NULL;
		}

		if (coin_2.sprite.image != NULL && safwen.position.x >= coin_2.position.x && safwen.position.x <= coin_2.position.x + coin_2.sprite.frame.w && safwen.position.y >= coin_2.position.y && safwen.position.y <= coin_2.position.y + coin_2.sprite.frame.h)
		{
			safwen.score_hero.valeur_score += 20;
			Mix_PlayChannel(-1, coin_1.click, 0);
			coin_2.sprite.image = NULL;
		}

		animer_entite(&enemie);
		animer_hero(&safwen, safwen.state, c);
		animer_pu(&coin_1, &coin_2);
		animer_platforme(&platforme);

		afficher_background(&background, ecran);
		afficher_platforme(platforme, background, ecran);
		afficher_pu(coin_1, ecran, background);
		afficher_pu(coin_2, ecran, background);
		afficher_entite(&enemie, ecran, background);
		afficher_text(instruction_1, background, ecran);
		afficher_text(instruction_2, background, ecran);

		if (Jcontinuer == 0 && safwen.vie_hero.nb_vie != 0)
			(*etat) = EXIT;
		if (safwen.vie_hero.nb_vie == 0 || safwen.position.y >= 2600)
		{
			animer_hero(&safwen, DIE, c);
			SDL_BlitSurface(game_over_txt.text, NULL, ecran, &game_over_txt.position);

			if (safwen.state != DIE)
			{
				safwen.sprite.image = NULL;
				SDL_Delay(2000);
				(*etat) = GAME_OVER;
				Jcontinuer = 0;
			}
		}
		afficher_hero(safwen, ecran, background);
		SDL_Flip(ecran);

		printf("%d\t%d\n", safwen.vie_hero.nb_vie, safwen.score_hero.valeur_score);
		printf("camera x: \t%d \n", background.posCamera.x);
		printf("safwen:%d.%d\t%d\tomar:%d.%d\n", safwen.position.x, safwen.position.y, collision(&enemie, &safwen), enemie.position.x, enemie.position.y);
		printf("%d%d%d%d\n", safwen.collision_UP, safwen.collision_DOWN, safwen.collision_RIGHT, safwen.collision_LEFT);
		printf("diff: %d\n", abs(safwen.position.x - enemie.position.x));
	}
	free_background(&background);
	free_entite(&enemie);
	freeenigme(&enigme_m);
	free_hero(&safwen);
	free_pu(&coin_1);
	free_pu(&coin_2);
	TTF_CloseFont(instruction_2.font);
	SDL_FreeSurface(instruction_2.text);
	SDL_FreeSurface(game_over_txt.text);
}