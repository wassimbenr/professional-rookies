#include "background.h"
#include "defs.h"
#include "structs.h"
void initialiser_background(background *b)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Prototype WASSIM", NULL);
	b->image = IMG_Load("./img/backgrounds/background1.png");
	b->background_mask = IMG_Load("./img/backgrounds/background_masque.png");
	b->posBackground.x = 0;
	b->posBackground.y = 0;
	b->posBackground_mask.x = 0;
	b->posBackground_mask.y = 0;
	b->posCamera.x = 0; //SCREEN_WIDTH / 2 ;
	b->posCamera.y = 0; // - SCREEN_HEIGHT / 2;
	b->posCamera.w = SCREEN_WIDTH;
	b->posCamera.h = SCREEN_HEIGHT;
}
void scrolling(background *b, entite *e)
{
	if (SDLK_LEFT)
		b->posCamera.x--;
	if (SDLK_RIGHT)
		b->posCamera.x++;
	if (SDLK_UP)
		b->posCamera.y--;
	if (SDLK_DOWN)
		b->posCamera.y++;

	b->posCamera.x = ( e->position.x + e->sprite.frame.w / 2) - SCREEN_WIDTH / 2;
	b->posCamera.y = ( e->position.y + e->sprite.frame.h / 2) - SCREEN_HEIGHT / 2;

	if (b->posCamera.x >= b->image->w - SCREEN_WIDTH)
		b->posCamera.x = 0;
	if (b->posCamera.x <= 0)
		b->posCamera.x = b->image->w - SCREEN_WIDTH;
}
void afficher_background(background *b, SDL_Surface *screen)
{
	SDL_BlitSurface(b->background_mask, &b->posCamera, screen, &b->posBackground_mask); //&b->posBackground_mask
	SDL_BlitSurface(b->image, &b->posCamera, screen, &b->posBackground);				//&b->posBackground
}
void free_background(background *b)
{
	SDL_FreeSurface(b->image);
	SDL_FreeSurface(b->background_mask);
}