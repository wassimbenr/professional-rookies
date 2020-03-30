#include "defs.h"
#include "hero.h"
#include "background.h"
#include "main_functions.h"

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
					printf("%d\n",kirby.position_hero.y);
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
		//GRAVITY
		//printf("%d\n%d\n%d\n",CollisionParfaite(background.background_mask,kirby.sprite.frame,kirby.position_hero),kirby.direction,kirby.position_hero.y);
		if (CollisionParfaite(background.background_mask,kirby.sprite.frame,kirby.position_hero)!=-2 && kirby.direction!=2 && kirby.position_hero.y!=NIVEAU_SOL)
				kirby.position_hero.y+=1; //doit etre un multiple de la difference to avoid seg fault (depasse NIVEAU_SOL)
		//position y must be stored (if hero steps on platform. So it can e used for jump limit)
		// add if (not in 0 level) then make it so
		//has to cancel out the jump limit value


		//SINGLE PRESS
		if (CollisionParfaite(background.background_mask,kirby.sprite.frame,kirby.position_hero)!=2 && kirby.direction==2/*&& t==16*/)
		{	
			if (kirby.position_hero.y!=NIVEAU_SOL-60)
				kirby.position_hero.y-=1; //doit ne pas depasser
			//h->direction=2;
		}
		if (kirby.position_hero.y==NIVEAU_SOL-60 || kirby.position_hero.y==468) //second condition adjusted to current valeu displayed but has to be equal tp ground_level+60
			kirby.direction=0;

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