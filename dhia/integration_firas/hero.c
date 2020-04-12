#include "hero.h"
#include "defs.h"

void initialiser_hero(hero *h,char name[20])
{
	char image_load[30]="";
	h->position.x=0;
	h->position.y=GROUND_LEVEL;

	h->direction=RIGHT;
	h->movement=IDLE;

	strcpy(image_load,"./img/hero/");
	strcat(image_load,name);
	strcat(image_load,".png");
	h->sprite.image=IMG_Load(image_load);

	h->sprite.frame.x=0;
	h->sprite.frame.y=0;

	h->sprite.frame.w=h->sprite.image->w/5;
	h->sprite.frame.h=h->sprite.image->h/7;

	h->sprite.curframe=0;

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