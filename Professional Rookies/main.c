#include "background.h"
#include "entite_secondaire.h"
#include "hero.h"
#include "background.h"
#include "colision.h"
#include "defs.h"

int main(int argc, char *argv[])
{
	hero safwen;
	background background;
	entite enemie;
	SDL_Surface *ecran = NULL;

	int continuer = 1;

	initialiser_hero(&safwen, "safwen");
	initialiser_background(&background);
	initialiser_entite(&enemie);

	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Rect positionecran;

	

	SDL_EnableKeyRepeat(2, 2);

	ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	while (continuer)
	{

		CollisionParfaite(&safwen, background);


		while (SDL_PollEvent(&event))
		{
			deplacer_hero(&safwen,event);
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					continuer=0;
					break;
			}

		}
		deplacer_hero(&safwen,event); //gravity and acceleration
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

	return EXIT_SUCCESS;
}