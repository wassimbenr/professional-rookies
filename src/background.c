#include "background.h"

void initialiser_background(background *b)
{
	b->image = IMG_Load("../img/background/x2.jpg");
	b->background_mask = IMG_Load("../img/background/x2_mask.jpg");

	b->posCamera.x = 400;
	b->posCamera.y = 900;
	b->posCamera.w = SCREEN_WIDTH;
	b->posCamera.h = SCREEN_HEIGHT;

	b->position_background_mask.x = 400;
	b->position_background_mask.y = 900;
	b->position_background_mask.w = SCREEN_WIDTH;
	b->position_background_mask.h = SCREEN_HEIGHT;

	//optimized image loading
	b->image = SDL_DisplayFormat(b->image);
	//b->background_mask = SDL_DisplayFormat(b->background_mask);

	
}

void afficher_background(background *b, SDL_Surface *screen)
{

	SDL_BlitSurface(b->background_mask, &b->position_background_mask, screen, NULL);
	SDL_BlitSurface(b->image, &b->posCamera, screen, NULL);
}
void free_background(background *b)
{
	SDL_FreeSurface(b->image);
	SDL_FreeSurface(b->background_mask);
}

void initialiser_platforme(platforme *p,int x,int y)
{
	p->image = IMG_Load("../img/background/platform.png");
	p->position.x = x;
	p->position.y = y;
}

void animer_platforme(platforme *p)
{
	static int tempsActuel=0;
	static int tempsPrecedent=0;
	static int sens=1;

	tempsActuel = SDL_GetTicks();
		if (tempsActuel - tempsPrecedent > 10)
		{
			p->position.x += 1*sens;
			tempsPrecedent = tempsActuel;
		}
		if (p->position.x >=1380)
			sens=-1;
		if (p->position.x<=1180)
			sens=1;
}

void afficher_platforme(platforme p,background b,SDL_Surface *ecran)
{
	SDL_Rect pos;
	pos.x=p.position.x-b.posCamera.x;
	pos.y=p.position.y-b.posCamera.y;
	SDL_BlitSurface(p.image,NULL,ecran,&pos);
}

void initialiser_text(text *i,char message[40],int x,int y,int size)
{
	TTF_Init();
	i->color.r=255;
	i->color.g=255;
	i->color.b=255;
	i->font=TTF_OpenFont("../fonts/chalk_2.ttf", size);
	i->text=TTF_RenderText_Blended(i->font, message, i->color);
	i->position.x=x;
	i->position.y=y;
}
void afficher_text(text i,background b,SDL_Surface *ecran)
{
	SDL_Rect pos;
	pos.x=i.position.x-b.posCamera.x;
	pos.y=i.position.y-b.posCamera.y;
	SDL_BlitSurface(i.text, NULL, ecran, &pos);
}
