#include "background.h"

void initialiser_background(background *b)
{
	SDL_Init(SDL_INIT_VIDEO);

	b->image=IMG_Load("./img/background/background.jpg");
	b->background_mask=IMG_Load("./img/background/backgroundMask.jpg");
	b->position_background.x=0;
	b->position_background.y=0;
	b->position_background_mask.x=0;
	b->position_background_mask.y=0;
}

void afficher_background(background *b,SDL_Surface *screen)
{
	SDL_BlitSurface(b->background_mask,NULL,screen,&b->position_background_mask);
	SDL_BlitSurface(b->image,NULL,screen,&b->position_background);
}
void free_background(background *b)
{
	SDL_FreeSurface(b->image);
	SDL_FreeSurface(b->background_mask);
}