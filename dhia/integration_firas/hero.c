#include "hero.h"
#include "defs.h"
#include "background.h"
#include "main_functions.h"
void initialiser_hero(hero *h)
{
	h->position.x=0;
	h->position.y=GROUND_LEVEL;

	h->direction=RIGHT;
	h->movement=IDLE;

	h->sprite.image=IMG_Load("./img/hero/safwen_right.png");

	h->sprite.frame.x=0;
	h->sprite.frame.y=0;

	h->sprite.frame.w=h->sprite.image->w/5;
	h->sprite.frame.h=h->sprite.image->h/7;

	h->sprite.curframe=0;

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
void CollisionParfaite(hero *h,background b)
{	
	SDL_Color couleur_obstacle={255,255,255};
	int i=0;
	int collision=0;
	SDL_Rect pos[8];

	h->collision_UP=0;
	h->collision_DOWN=0;
	h->collision_RIGHT=-1;
	h->collision_LEFT=-2;

	pos[0].x=h->position.x;
	pos[0].y=h->position.y;
	pos[1].x=h->position.x+h->sprite.frame.w/2;
	pos[1].y=h->position.y;
	pos[2].x=h->position.x+h->sprite.frame.w;
	pos[2].y=h->position.y;

	pos[3].x=h->position.x;
	pos[3].y=h->position.y+h->sprite.frame.h/2;
	pos[4].x=h->position.x+h->sprite.frame.w;
	pos[4].y=h->position.y+h->sprite.frame.h/2;

	pos[5].x=h->position.x;
	pos[5].y=h->position.y+h->sprite.frame.h;
	pos[6].x=h->position.x+h->sprite.frame.w/2;
	pos[6].y=h->position.y+h->sprite.frame.h;
	pos[7].x=h->position.x+h->sprite.frame.w;
	pos[7].y=h->position.y+h->sprite.frame.h;

	for (i=0;i<8;i++)
	{
		couleur_obstacle=GetPixel(b.background_mask,pos[i].x,pos[i].y);
		if (couleur_obstacle.r==0 && couleur_obstacle.g==0 && couleur_obstacle.b==0)
		{
			if (i==0 || i==3 || i==5)
				h->collision_LEFT++;
			else if (i==2 || i==4)
				h->collision_RIGHT++;
			else if (i==1)
				h->collision_UP++;
			else if (i==6)
				h->collision_DOWN++;
			collision++;
		}	
	}
	if (h->collision_LEFT<=0)
		h->collision_LEFT=0;
	if (h->collision_RIGHT<=0)
		h->collision_RIGHT=0;
	if (h->collision_UP<=0)
		h->collision_UP=0;
	if (h->collision_DOWN<=0)
		h->collision_DOWN=0;

}
void afficher_hero(hero *h, SDL_Surface* screen)
{
	SDL_BlitSurface(h->sprite.image,&h->sprite.frame,screen,&h->position);
}
void animer_hero(hero *h,movement movement)
{
	static int tempsActuel=0;
	static int tempsPrecedent=0;


	switch(movement)
	{
		case IDLE:
			h->sprite.frame.y=0;
			h->sprite.maxframe=3;
			break;
		case WALK_RIGHT:
			h->sprite.frame.y=h->sprite.frame.h;
			h->sprite.maxframe=4;
			h->movement=WALK_RIGHT;
			h->direction=RIGHT;
			break;
		case WALK_LEFT:
			h->sprite.frame.y=h->sprite.frame.h;
			h->sprite.maxframe=4;
			h->movement=WALK_LEFT;
			h->direction=LEFT;
			break;
		case JUMP:
			h->sprite.frame.y=2*h->sprite.frame.h;
			h->sprite.maxframe=3;
			h->movement=JUMP;
			break;
		case PUNCH:
			h->sprite.frame.y=3*h->sprite.frame.h;
			h->sprite.maxframe=4;
			h->movement=PUNCH;
			break;
		case KICK:
			h->sprite.frame.y=4*h->sprite.frame.h;
			h->sprite.maxframe=4;
			h->movement=KICK;
			break;
		case HIT:
			h->sprite.frame.y=5*h->sprite.frame.h;
			h->sprite.maxframe=4;
			h->movement=HIT;
			break;
		case DIE:
			h->sprite.frame.y=6*h->sprite.frame.h;
			h->sprite.maxframe=3;
			h->movement=DIE;
			break;
	}

	if (h->direction==RIGHT)
		h->sprite.image=IMG_Load("./img/hero/safwen_right.png");
	if (h->direction==LEFT)
		h->sprite.image=IMG_Load("./img/hero/safwen_left.png");
		//because can changed by walking directions
	tempsActuel=SDL_GetTicks();
	if (tempsActuel-tempsPrecedent > 200)
	{
		if (h->sprite.curframe >= h->sprite.maxframe)
		{		
			h->sprite.curframe=0;
			if (h->movement!=WALK_RIGHT && h->movement!=WALK_LEFT)
				h->movement=IDLE; //to not interrupt animation (but can be interrupted with SDL_KEYUP)
		}

		h->sprite.frame.x=h->sprite.curframe*h->sprite.frame.w;
		tempsPrecedent=tempsActuel;
		h->sprite.curframe+=1;
	}
}

void free_hero(hero *h)
{
	SDL_FreeSurface(h->sprite.image);
}