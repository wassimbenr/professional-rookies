#include "background.h"

void initialiser_background(background *b)
{
	SDL_Init(SDL_INIT_VIDEO);

	b->image=IMG_Load("./img/background/background.jpg");
	b->background_mask=IMG_Load("./img/background/backgroundMask.jpg");
	b->position_background.x=0;
	b->position_background.y=-0;
	b->position_background_mask.x=0;
	b->position_background_mask.y=0;
	b->posCamera.x = 0; //SCREEN_WIDTH / 2 ;
	b->posCamera.y = 0; // - SCREEN_HEIGHT / 2;
	b->posCamera.w = SCREEN_WIDTH;
	b->posCamera.h = SCREEN_HEIGHT;
}

void scrolling(background *b, hero *h, SDL_Event event)
{
	while (SDL_PollEvent(&event))
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				b->posCamera.x--;
				break;
			case SDLK_RIGHT:
				b->posCamera.x++;
				break;
			case SDLK_UP:
				b->posCamera.y--;
				break;
			case SDLK_DOWN:
				b->posCamera.y++;
				break;
			}
		}
	//b->posCamera.x = ( h->position.x + h->sprite.frame.w / 2) - SCREEN_WIDTH / 4;
	//b->posCamera.y = ( h->position.y + h->sprite.frame.h / 2) - SCREEN_HEIGHT / 2;
/*
	if (b->posCamera.x >= b->image->w - SCREEN_WIDTH)
		b->posCamera.x = 0;
	if (b->posCamera.x <= 0)
		b->posCamera.x = b->image->w - SCREEN_WIDTH;*/
}
void afficher_background(background *b, SDL_Surface *screen)
{
	SDL_BlitSurface(b->background_mask, &b->posCamera, screen, &b->position_background_mask); //&b->position_background_mask
	SDL_BlitSurface(b->image,  &b->posCamera, screen, &b->position_background);				//&b->position_background
}
void free_background(background *b)
{
	SDL_FreeSurface(b->image);
	SDL_FreeSurface(b->background_mask);
}