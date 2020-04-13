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
	b->posCamera.x = 0; //SCREEN_WIDTH / 2 ;
	b->posCamera.y = 0; // - SCREEN_HEIGHT / 2;
	b->posCamera.w = SCREEN_WIDTH;
	b->posCamera.h = SCREEN_HEIGHT;
}

void afficher_background(background *b, SDL_Surface *screen)
{
	SDL_BlitSurface(b->background_mask, &b->posCamera, screen, &b->position_background_mask); //&b->position_background_mask
	SDL_BlitSurface(b->image, &b->posCamera, screen, &b->position_background);				//&b->position_background
}
void free_background(background *b)
{
	SDL_FreeSurface(b->image);
	SDL_FreeSurface(b->background_mask);
}

SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y)
{
	SDL_Color color;
	Uint32 col=0;
	char* pPosition=(char* ) pSurface->pixels;
	pPosition+= (pSurface->pitch * y);
	pPosition+= (pSurface->format->BytesPerPixel *x);
	memcpy(&col ,pPosition ,pSurface->format->BytesPerPixel);
	SDL_GetRGB(col,pSurface->format, &color.r, &color.g, &color.b);
	return (color);
}