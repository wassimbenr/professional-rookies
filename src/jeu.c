/**
 * @file jeu.c
 */
#include "jeu.h"

#define NB_PLATFORMES 13
#define NB_PLATFORMES_HORIZ 2
#define NB_COINS 5
#define NB_HEARTS 1
#define NB_INSTRUCTIONS 6
#define NB_ENNEMIES 2

void jeu(SDL_Surface *ecran, etat *etat, hero *safwen, parameter *p, character c, background background, dialogue dial)
{
	SDL_Event event;
	int Jcontinuer = 1;
	int verif = 0;

	int tempsActuel = 0;
	int tempsPrecedent = 0;
	int mini = 1;
	int idk = 1;

	int tempsActuel2 = 0;
	int tempsPrecedent2 = 0;

	SDL_Rect pos_rel;

	entite ennemies[NB_ENNEMIES];
	platforme platformes[NB_PLATFORMES];
	platforme platformes_horiz[NB_PLATFORMES_HORIZ];
	text game_over_txt;
	dialogue dialogue = dial;
	text instructions[NB_INSTRUCTIONS];
	power_up coins[NB_COINS];
	heart hearts[NB_HEARTS];
	timer timer, pan_timer;
	minimap minimap;
	portal portal;
	boss boss;
	init_boss(&boss, 9500, 570);

	mat e, c1, c2;
	init_mats(&e, &c1, &c2);

	int plat_coll;
	int plat_coll_horiz;

	SDL_Surface *black = NULL;

	int portal_number = 0;

	SDL_Rect position_black;
	position_black.x = 0;
	position_black.y = 0;

	initialiser_dialogue(&dialogue, ecran, c);
	initialiser_background(&background, *p);
	initialiser_ennemies(ennemies, NB_ENNEMIES);
	initialiser_minimap(&minimap, background, *safwen);

	initialiser_portal(&portal);

	initialiser_plats(platformes, NB_PLATFORMES);
	initialiser_plats_horiz(platformes_horiz, NB_PLATFORMES_HORIZ);

	initialiser_instructions(instructions, NB_INSTRUCTIONS);
	initialiser_coins(coins, NB_COINS);
	initialiser_hearts(hearts, NB_HEARTS);

	initialiser_text(&game_over_txt, "", SCREEN_WIDTH_GAME / 2 - 250, SCREEN_HEIGHT_GAME / 2, 90);

	p->music = Mix_LoadMUS("../sfx/alter-ego.mp3");

	ecran = SDL_SetVideoMode(SCREEN_WIDTH_GAME, SCREEN_HEIGHT_GAME, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);

	if (!p->mute)
		Mix_PlayMusic(p->music, -1);
	else
		Mix_PauseMusic();
	if (p->fullscreen)
	{
		SDL_WM_ToggleFullScreen(ecran);
	}

	int passage_boucle = 0;
	int once = 0;
	int once_enigme_math = 0;
	int once_enigme_pendu = 0;
	int once_enigme_AI = 0;

	int i;
	int saving = 0;
	int pan = 0;
	SDL_Surface *save_screen = NULL;
	SDL_Rect pos_save_screen;
	pos_save_screen.x = 280;
	pos_save_screen.y = 280;

	SDL_Surface *enigme_frames_1[10];

	enigme_frames_1[0] = IMG_Load("../img/enigme/icon/1.png");
	enigme_frames_1[1] = IMG_Load("../img/enigme/icon/2.png");
	enigme_frames_1[2] = IMG_Load("../img/enigme/icon/3.png");
	enigme_frames_1[3] = IMG_Load("../img/enigme/icon/4.png");
	enigme_frames_1[4] = IMG_Load("../img/enigme/icon/5.png");
	enigme_frames_1[5] = IMG_Load("../img/enigme/icon/6.png");
	enigme_frames_1[6] = IMG_Load("../img/enigme/icon/7.png");
	enigme_frames_1[7] = IMG_Load("../img/enigme/icon/8.png");
	enigme_frames_1[8] = IMG_Load("../img/enigme/icon/9.png");
	enigme_frames_1[9] = IMG_Load("../img/enigme/icon/10.png");

	SDL_Surface *enigme_frames_2[10];

	enigme_frames_2[0] = IMG_Load("../img/enigme/icon/1.png");
	enigme_frames_2[1] = IMG_Load("../img/enigme/icon/2.png");
	enigme_frames_2[2] = IMG_Load("../img/enigme/icon/3.png");
	enigme_frames_2[3] = IMG_Load("../img/enigme/icon/4.png");
	enigme_frames_2[4] = IMG_Load("../img/enigme/icon/5.png");
	enigme_frames_2[5] = IMG_Load("../img/enigme/icon/6.png");
	enigme_frames_2[6] = IMG_Load("../img/enigme/icon/7.png");
	enigme_frames_2[7] = IMG_Load("../img/enigme/icon/8.png");
	enigme_frames_2[8] = IMG_Load("../img/enigme/icon/9.png");
	enigme_frames_2[9] = IMG_Load("../img/enigme/icon/10.png");

	SDL_Surface *enigme_frames_3[10];

	enigme_frames_3[0] = IMG_Load("../img/enigme/icon/1.png");
	enigme_frames_3[1] = IMG_Load("../img/enigme/icon/2.png");
	enigme_frames_3[2] = IMG_Load("../img/enigme/icon/3.png");
	enigme_frames_3[3] = IMG_Load("../img/enigme/icon/4.png");
	enigme_frames_3[4] = IMG_Load("../img/enigme/icon/5.png");
	enigme_frames_3[5] = IMG_Load("../img/enigme/icon/6.png");
	enigme_frames_3[6] = IMG_Load("../img/enigme/icon/7.png");
	enigme_frames_3[7] = IMG_Load("../img/enigme/icon/8.png");
	enigme_frames_3[8] = IMG_Load("../img/enigme/icon/9.png");
	enigme_frames_3[9] = IMG_Load("../img/enigme/icon/10.png");

	int now = 0;
	int then = 0;

	SDL_Rect pos_enigme1, pos_enigme2, pos_enigme3;

	pos_enigme1.x = 1000;
	pos_enigme1.y = 1500;

	pos_enigme2.x = 1050;
	pos_enigme2.y = 985;

	pos_enigme3.x = 3030;
	pos_enigme3.y = 445;

	text save_text;
	initialiser_text(&save_text, "", 315, 320, 10);
	save_text.color.r = 0;
	save_text.color.g = 0;
	save_text.color.b = 0;

	int en_frame = 0;
	int once_p = 0;

	int once_p2 = 0;
	int pan2 = 0;

	enigme enigMath;

	SDL_Rect posss1, posss2, posss3;

	while (Jcontinuer)
	{
		printf("BOSS: %d\n", boss.vie_boss.nb_vie);
		if (safwen->position.x >= 1850 && safwen->position.x <= 1950 && safwen->collision_DOWN && !once_p)
		{
			pan = 1;
			once_p = 1;
		}
		if (safwen->position.x >= 7729 && safwen->position.y <= 560 && safwen->collision_DOWN && !once_p2)
		{
			pan2 = 1;
			once_p2 = 1;
		}
		printf("CAMERA: (%d,%d)\n", background.posCamera.x, background.posCamera.y);
		if (pan2)
		{
			camera_pan(&background, *safwen, 9400, 250, &pan2, 5);
		}
		if (pan)
			camera_pan(&background, *safwen, 1900, 1300, &pan, 5);
		if (!pan && !pan2)
			deplacer_hero(safwen, &background, &Jcontinuer, c, platformes, &saving, NB_PLATFORMES, &mini);

		CollisionParfaite(safwen, background);
		animer_boss(&boss);

		if (safwen->position.x >= 1000 && safwen->position.x <= 1200 && safwen->position.y <= 1570 && !once_enigme_math)
		{
			enigme_math(ecran, &enigMath, safwen);
			once_enigme_math = 1;
			ecran = SDL_SetVideoMode(SCREEN_WIDTH_GAME, SCREEN_HEIGHT_GAME, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
		}

		//enigme Pendu
		if (safwen->position.x <= 1100 && safwen->position.x >= 900 && safwen->position.y <= 1055 && !once_enigme_pendu)
		{
			enigme_pendu(ecran, safwen);
			once_enigme_pendu = 1;
			ecran = SDL_SetVideoMode(SCREEN_WIDTH_GAME, SCREEN_HEIGHT_GAME, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
		}

		//AI
		if (safwen->position.x >= 3030 && safwen->position.x <= 3130 && safwen->position.y <= 515 && !once_enigme_AI)
		{
			AI_enigme(ecran, safwen);
			once_enigme_AI = 1;
		}

		plat_coll = collision_platforme(safwen, platformes, NB_PLATFORMES);

		for (i = 0; i < NB_PLATFORMES; i++)
		{
			tempsActuel = SDL_GetTicks();
			if (safwen->collision_DOWN_PLAT && safwen->state == IDLE)
			{
				if (tempsActuel - tempsPrecedent > 10)
				{
					safwen->position.x += 1 * platformes[plat_coll].sens;
					tempsPrecedent = tempsActuel;
				}
			}
		}

		if (abs(safwen->position.x - boss.position.x) < 400)
			attack_boss(&boss, safwen);
		else
		{
			deplacer_alea_boss(&boss);
		}

		printf("SAF VIE: %d\n", safwen->vie_hero.nb_vie);

		//portal
		if (safwen->position.x >= 5500 && safwen->position.x <= 5840 && safwen->position.y >= 1070 && safwen->position.y <= 1120)
		{
			safwen->position.x += 750;
			safwen->position.y += 600;
		}
		//save
		if (saving == 0)
		{

			save_screen = NULL;
			black = NULL;
			once = 0;
			save_text.text = TTF_RenderText_Blended(save_text.font, "", save_text.color);
		}
		else
		{
			if (!once)
			{
				save_screen = IMG_Load("../img/menu/objects/text_field.png");
				black = IMG_Load("../img/black.jpg");
				SDL_SetAlpha(black, SDL_SRCALPHA, 120);
				save_text.text = TTF_RenderText_Blended(save_text.font, "Press y to confirm and q to quit", save_text.color);
				once = 1;
			}

			if (saving == 2)
			{
				save_game(*safwen, background, c, dialogue);
				printf("SAVED\n");
				saving = 0;
				once = 0;
			}
		}

		for (i = 0; i < NB_ENNEMIES; i++)
		{
			if (abs(safwen->position.x - ennemies[i].position.x) <= 250 && abs(safwen->position.y - ennemies[i].position.y) >= 0 && abs(safwen->position.y - ennemies[i].position.y) <= 50)
				attack_entite(&ennemies[i], safwen);
			else
				deplacer_alea(&ennemies[i]);
		}

		coins_interaction(coins, NB_COINS, safwen);
		hearts_interaction(hearts, NB_HEARTS, safwen);

		playing_dialogue(&dialogue, *safwen, ecran, timer);

		animer_ennemies(ennemies, NB_ENNEMIES);
		animer_hero(safwen, safwen->state, c);
		animer_coins(coins, NB_COINS);
		animer_hearts(hearts, NB_HEARTS);
		animer_platformes(platformes, NB_PLATFORMES);
		animer_portal(&portal);
		animer_mat(&e, &c1, &c2);
		collision_mat(safwen, e, c1, c2);

		afficher_background(&background, ecran);
		afficher_platformes(platformes, background, ecran, NB_PLATFORMES);
		afficher_boss(&boss, ecran, background, *safwen);

		afficher_coins(coins, NB_COINS, background, ecran);
		afficher_hearts(hearts, NB_HEARTS, background, ecran);
		afficher_ennemies(ennemies, NB_ENNEMIES, ecran, background);
		afficher_mat(e, c1, c2, background, ecran);

		now = SDL_GetTicks();
		if (now - then > 40)
		{

			en_frame++;

			then = now;
		}

		if (en_frame == 8)
			en_frame = 0;

		posss1.x = pos_enigme1.x - background.posCamera.x;
		posss1.y = pos_enigme1.y - background.posCamera.y;
		posss2.x = pos_enigme2.x - background.posCamera.x;
		posss2.y = pos_enigme2.y - background.posCamera.y;
		posss3.x = pos_enigme3.x - background.posCamera.x;
		posss3.y = pos_enigme3.y - background.posCamera.y;
		if (once_enigme_math != 1)
			SDL_BlitSurface(enigme_frames_1[en_frame], NULL, ecran, &posss1);
		if (once_enigme_pendu != 1)
			SDL_BlitSurface(enigme_frames_2[en_frame], NULL, ecran, &posss2);
		if (once_enigme_AI != 1)
			SDL_BlitSurface(enigme_frames_3[en_frame], NULL, ecran, &posss3);

		afficher_instructions(instructions, NB_INSTRUCTIONS, background, ecran);

		if (Jcontinuer == 0 && safwen->vie_hero.nb_vie != 0)
			(*etat) = EXIT;

		if (safwen->vie_hero.nb_vie == 0 || abs(safwen->position.y + safwen->sprite.image->h - background.image->h - background.posCamera.h) < 170)
		{
			animer_hero(safwen, DIE, c);
			passage_boucle++;
			black = IMG_Load("../img/black.jpg");
			SDL_SetAlpha(black, SDL_SRCALPHA, 120);
			game_over_txt.text = TTF_RenderText_Blended(game_over_txt.font, "GAME OVER", game_over_txt.color);

			if (passage_boucle == 15)
			{
				safwen->sprite.image = NULL;
				SDL_Delay(2000);
				(*etat) = GAME_OVER;
				Jcontinuer = 0;
				dialogue.talking = 0;
			}
		}
		afficher_hero(*safwen, ecran, background);
		afficher_portal(portal, background, *safwen, ecran);

		afficher_dialogue(dialogue, ecran);
		show_time(&timer, ecran);
		SDL_BlitSurface(black, NULL, ecran, &position_black);
		SDL_BlitSurface(save_screen, NULL, ecran, &pos_save_screen);
		SDL_BlitSurface(save_text.text, NULL, ecran, &save_text.position);
		SDL_BlitSurface(game_over_txt.text, NULL, ecran, &game_over_txt.position);

		if (mini == 1 && idk != 1)
		{
			minimap.image = IMG_Load("../img/background/test2.jpg");
			minimap.hero = IMG_Load("../img/background/rouge.png");
			idk = 1;

			minimap.pos_image.x = (SCREEN_WIDTH_GAME / 2) - (minimap.image->w / 2);
			minimap.pos_image.y = 0;

			minimap.pos_hero.x = (SCREEN_WIDTH_GAME / 2) - (minimap.image->w / 2) + safwen->position.x / 12.5;
		}
		if (mini == -1 && idk != 2)
		{
			minimap.image = IMG_Load("../img/background/test1.jpg");
			idk = 2;
			minimap.pos_image.x = 0;
			minimap.pos_image.y = 0;
		}

		afficher_minimap(&minimap, *safwen, ecran, mini);
		SDL_Flip(ecran);

		printf("safwen: (%d;%d)\n", safwen->position.x, safwen->position.y);
		//if (safwen->position.x >= 9979 && safwen->position.y <= 570)
		if (boss.vie_boss.nb_vie == 0)
		{
			//boss.sprite_entite.image = NULL;
			*etat = CREDS;
			Jcontinuer = 0;
		}
	}
	free_hero(safwen);
	free_background(&background);
	free_ennemies(ennemies, NB_ENNEMIES);
	free_pu(coins, NB_COINS);
	free_hearts(hearts, NB_HEARTS);
	free_instructions(instructions, NB_INSTRUCTIONS);
	free_dialogue(&dialogue);
	free_platformes(platformes, NB_PLATFORMES);
	free_platformes(platformes_horiz, NB_PLATFORMES_HORIZ);
	free_minimap(&minimap);
	free_portal(&portal);
	SDL_FreeSurface(boss.sprite_entite.image);
}