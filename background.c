#include "background.h"

void initialiser_background(background *b)
{
	b->image = IMG_Load("./img/background/background.jpg");
	b->background_mask = IMG_Load("./img/background/backgroundMask.jpg");
	b->position_background.x = 0;
	b->position_background.y = 0;
	b->position_background_mask.x = 0;
	b->position_background_mask.y = 0;
	b->posCamera.x = 0; //b->posCamera.x = ( h->position.x + h->sprite.frame.w / 2) - SCREEN_WIDTH / 4
	b->posCamera.y = 0; // - SCREEN_HEIGHT / 2;
	b->posCamera.w = b->image->w;
	b->posCamera.h = b->image->h;
}

void scrolling(background *b, SDL_Event event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_LEFT:
	{
		b->posCamera.x -= 4;
		if (b->posCamera.x <= 0)
			b->posCamera.x = 0;
		break;
	}
	case SDLK_RIGHT:
	{
		b->posCamera.x += 4;
		if (b->posCamera.x + SCREEN_WIDTH >= b->image->w )
			b->posCamera.x = b->image->w - SCREEN_WIDTH;
		break;
	}
	}
}
void afficher_background(background *b, SDL_Surface *screen)
{

	SDL_BlitSurface(b->background_mask, &b->posCamera, screen, &b->position_background_mask); //&b->position_background_mask
	SDL_BlitSurface(b->image, &b->posCamera, screen, &b->position_background);				  //&b->position_background
}
void free_background(background *b)
{
	SDL_FreeSurface(b->image);
	SDL_FreeSurface(b->background_mask);
}