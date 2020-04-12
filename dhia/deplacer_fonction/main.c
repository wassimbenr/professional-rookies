#include "background.h"

int main()
{
	SDL_Event event;
	SDL_Surface *screen = NULL;
	int continuer = 1;
	hero safwen, omar;
	background background;

	initialiser_background(&background);
	initialiser_hero(&safwen, "safwen_right");

	screen = SDL_SetVideoMode(background.image->w, background.image->h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	SDL_EnableKeyRepeat(10, 10);

	while (continuer)
	{
		CollisionParfaite(&safwen, background);
		deplacer_hero(&safwen);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_RIGHT)
				{
					if ((!safwen.collision_DOWN) && (!safwen.test))
					{
						safwen.position.y += 7;
						safwen.tanguiza = 1;
					}
					else if (safwen.collision_DOWN)
						safwen.tanguiza = 0;
					break;
				}
				if (event.button.button == SDL_BUTTON_LEFT)
					safwen.acceleration = 0;
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_UP)
				{
					if ((!safwen.collision_DOWN) && (!safwen.test))
					{
						safwen.position.y += 7;
						safwen.tanguiza = 1;
					}
					else if (safwen.collision_DOWN)
						safwen.tanguiza = 0;
					break;
				}
				if (event.key.keysym.sym == SDLK_RIGHT || (event.key.keysym.sym == SDLK_LEFT))
				{
					safwen.acceleration = 0;
				}
				if (safwen.movement == WALK_RIGHT || safwen.movement == WALK_LEFT)
					safwen.movement = IDLE;
				break;
			}
		}

		animer_hero(&safwen, safwen.movement);
		afficher_background(&background, screen);
		afficher_hero(&safwen, screen);

		SDL_Flip(screen);
	}
	free_background(&background);
	free_hero(&safwen);
	SDL_Quit();
	return 0;
}