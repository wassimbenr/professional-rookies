#include "background.h"
#include "hero.h"


int main(int argc, char *argv[])
{
	entite safwen;
	background background;

	SDL_Surface *ecran = NULL;

	int continuer = 1;

	initialiser_hero(&safwen, "safwen");
	initialiser_background(&background);

	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Rect positionecran;

	

	SDL_EnableKeyRepeat(2, 2);

	ecran = SDL_SetVideoMode(background.image->w, background.image->h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

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
		afficher_background(background, ecran);
		afficher_hero(safwen, ecran);
		SDL_Flip(ecran);
	}

	free_background(&background);
	free_hero(&safwen);
	SDL_Quit();

	return EXIT_SUCCESS;
}