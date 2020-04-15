#include <SDL/SDL.h>

#include "ennemi.h"

#include <SDL/SDL_image.h>
void  loadEnnemiImages(Ennemi * A)
{
	
	A->image = IMG_Load("PERSO/ennemie1.png");

	
}


void initEnnemi(Ennemi* E)
{	loadEnnemiImages(E);
	E->positionAbsolue.x = 700;
	E->positionAbsolue.y = 357;
	E->positionAbsolue.w = 0;
	E->positionAbsolue.h = 0;
	E->positionAnimation.x = 0;
	E->positionAnimation.y = 0;
	E->positionAnimation.w = 50;
	E->positionAnimation.h = 60;
	E->STATE=WAITING;
	E->positionInitial=1940;
}


void blitEnnemi(Ennemi *E, SDL_Surface* screen,SDL_Rect positionFond)
{	if ( positionFond.x<E->positionInitial && positionFond.x+800>E->positionInitial)
	{
		E->positionAbsolue.x=E->positionInitial-positionFond.x;
		
		SDL_BlitSurface(E->image, &E->positionAnimation, screen, &E->positionAbsolue);
	}
}
void AnnimateEnnemi(Ennemi *E)
{
        E->positionAnimation.x += 60;
	E->positionAnimation.x = E->positionAnimation.x % (60 * 12);	
        E->positionAnimation.y = 0;
        SDL_Delay(100);
}
void MoveEnnemi(Ennemi *E,SDL_Rect positionperso)
{
        if (E->positionAbsolue.x- positionperso.x <0)
            E->positionInitial++;
        else if (E->positionAbsolue.x- positionperso.x>0)
        	E->positionInitial--;
}
	
void freeEnnemi(Ennemi *E)
{
	SDL_FreeSurface(E->image);
}

void UpdateEnnemi(Ennemi *E ,SDL_Rect positionperso)
{
	switch(E->STATE){
		case WAITING :
			//AnnimateEnnemi(E);
			 
			break;
		case FOLLOWING://AnnimateEnnemi(E);
			MoveEnnemi(E,positionperso);
			break;
		case ATTACKING: initEnnemi(E);
		//AnnimateEnnemi(E);
		break;
	}
}

int  collision(Ennemi *E , SDL_Rect positionperso)
{
if(positionperso.x > E->positionAbsolue.x && positionperso.x < E->positionAbsolue.x +E->positionAbsolue.w)
return 0;
if(positionperso.x +positionperso.w> E->positionAbsolue.x && positionperso.x +positionperso.w < E->positionAbsolue.x + E->positionAbsolue.w)
return 0;
if(positionperso.y > E->positionAbsolue.y && positionperso.y < E->positionAbsolue.y +E->positionAbsolue.h)
return 0;
if(positionperso.y +positionperso.h> E->positionAbsolue.y && positionperso.y +positionperso.h < E->positionAbsolue.y + E->positionAbsolue.h)
return 0;


return 1;
}

void input_ennemi(Ennemi *E , SDL_Rect positionperso)
{int x;
x=collision(E,positionperso);
//printf("%d\n",x);
switch(E-> STATE)
	{ case WAITING :
		if(E->positionAbsolue.x - positionperso.x<1000)
			E->STATE=FOLLOWING;
		printf("%d\n",E->positionAbsolue.x - positionperso.x);
		UpdateEnnemi(E,positionperso);
		break;
		case FOLLOWING:
		if (E->positionAbsolue.x - positionperso.x>1000)
		{
			E->STATE=WAITING;
		}
		else if(x==0)
			E->STATE=ATTACKING;
		UpdateEnnemi(E,positionperso);
		break;
	case  ATTACKING:
		if(E->positionAbsolue.x - positionperso.x!=0)
			E->STATE=FOLLOWING;
		UpdateEnnemi(E,positionperso);
		break;




	}



}
