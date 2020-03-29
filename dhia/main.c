/*#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"*/

#include "defs.h"
#include "hero.h"
#include "background.h"

int main()
{
	SDL_Surface *screen=NULL;
	SDL_Event event;
	int continuer=1;
	hero kirby;
	background background;
	
	initialiser_background(&background);
	initialiser_hero(&kirby);
	
	screen=SDL_SetVideoMode(background.image->w,background.image->h,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

	SDL_EnableKeyRepeat(10,10);	
	while(continuer)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					continuer=0;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							continuer=0;
							break;
					}
					break;
			}
			deplacer_hero(&kirby,event,background.background_mask);
		}
		if (CollisionParfaite(background.background_mask,kirby.sprite.frame,kirby.position_hero)!=-2 && kirby.direction!=2 && kirby.position_hero.y!=NIVEAU_SOL)
				kirby.position_hero.y+=5;
		animer_hero(&kirby);

		afficher_background(&background,screen);
		afficher_hero(&kirby,screen);

		SDL_Flip(screen);
	}
	free_background(&background);
	free_hero(&kirby);
	SDL_Quit();
	return 0;
}