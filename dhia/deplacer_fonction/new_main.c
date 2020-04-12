#include "defs.h"
#include "hero.h"
#include "background.h"
#include "main_functions.h"

int main()
{
	SDL_Surface *screen=NULL;
	SDL_Event event;
	int continuer=1;
	hero safwen,omar;
	background background;

	
	initialiser_background(&background);
	initialiser_hero(&safwen,"safwen_right");
	
	screen=SDL_SetVideoMode(background.image->w,background.image->h,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

	SDL_EnableKeyRepeat(10,10);	

	while(continuer)
	{
        deplacer_hero(&safwen,background);
		
		/*while(SDL_PollEvent(&event))
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
						case SDLK_RIGHT:
							if (CollisionParfaite(background.background_mask,safwen.sprite.frame,safwen.position)!=1)
							{
								safwen.position.x+=4;
								safwen.direction=RIGHT;
								animer_hero(&safwen,WALK); 
							} 
							break;
						case SDLK_LEFT:
							safwen.position.x-=4;
							safwen.direction=LEFT;
							animer_hero(&safwen,WALK);

							break;
						case SDLK_UP:
							animer_hero(&safwen,JUMP);
							break;
						case SDLK_d:
							animer_hero(&safwen,PUNCH);
							break;
						case SDLK_s:
							animer_hero(&safwen,KICK);
							break;
						case SDLK_q:
							animer_hero(&safwen,HIT);
							break;
						case SDLK_x:
							animer_hero(&safwen,DIE);
							break;
					}
					break;
				case SDL_KEYUP: 
					if(safwen.movement==WALK)  //movements with interruptable animations
						safwen.movement=IDLE;
					break;
			}
		}*/
		
		animer_hero(&safwen,safwen.movement);
		afficher_background(&background,screen);
		afficher_hero(&safwen,screen);

		SDL_Flip(screen);
	}
	free_background(&background);
	free_hero(&safwen);
	SDL_Quit();
	return 0;

}