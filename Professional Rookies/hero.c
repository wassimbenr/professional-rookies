#include "hero.h"
#include "defs.h"
#include "background.h"
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
int CollisionParfaite(SDL_Surface* backgroundMask, SDL_Rect frame, SDL_Rect position)
{	
	SDL_Color couleur_obstacle={255,255,255};
	int i=0;
	int collision=0;
	SDL_Rect pos[8];

	pos[0].x=position.x;
	pos[0].y=position.y;
	pos[1].x=position.x+frame.w/2;
	pos[1].y=position.y;
	pos[2].x=position.x+frame.w;
	pos[2].y=position.y;

	pos[3].x=position.x;
	pos[3].y=position.y+frame.h/2;
	pos[4].x=position.x+frame.w;
	pos[4].y=position.y+frame.h/2;

	pos[5].x=position.x;
	pos[5].y=position.y+frame.h;
	pos[6].x=position.x+frame.w/2;
	pos[6].y=position.y+frame.h;
	pos[7].x=position.x+frame.w;
	pos[7].y=position.y+frame.h;

	while (i<8 && collision==0)
	{
		couleur_obstacle=GetPixel(backgroundMask,pos[i].x,pos[i].y);
		if (couleur_obstacle.r==0 && couleur_obstacle.g==0 && couleur_obstacle.b==0)
			collision=1;
		i++;
	}
	if (collision!=0)
	{
		if (i==0 || i==3 || i==5)
			collision=-1;
		else if (i==2 || i==4)
			collision=1;
		else if (i==1)
			collision=2;
		else
			collision=-2;
	}
	return collision;
}
void afficher_hero(hero *h, SDL_Surface* screen)
{
	SDL_BlitSurface(h->sprite.image,&h->sprite.frame,screen,&h->position);
}
void animer_hero(hero *h,movement movement)
{
	static int tempsActuel=0;
	static int tempsPrecedent=0;

	if (h->direction==RIGHT)
		h->sprite.image=IMG_Load("./img/hero/safwen_right.png");
	if (h->direction==LEFT)
		h->sprite.image=IMG_Load("./img/hero/safwen_left.png");

	switch(movement)
	{
		case IDLE:
			h->sprite.frame.y=0;
			h->sprite.maxframe=3;
			break;
		case WALK:
			h->sprite.frame.y=h->sprite.frame.h;
			h->sprite.maxframe=4;
			h->movement=WALK;
			break;
		case JUMP:
			h->sprite.frame.y=2*h->sprite.frame.h;
			h->sprite.maxframe=2;
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
	tempsActuel=SDL_GetTicks();
	if (tempsActuel-tempsPrecedent > 200)
	{
		if (h->sprite.curframe >= h->sprite.maxframe)
		{		
			h->sprite.curframe=0;
			if (h->movement!=WALK)
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