#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#ifdef WIN32
#pragma comment(lib,"sdl.lib")
#pragma comment(lib,"sdlmain.lib")
#endif

#define STAT_SOL 0
#define STAT_AIR 1


void HP (SDL_Surface * imageHP[])
{
imageHP[0]=IMG_Load("HP/(1).png");
imageHP[1]=IMG_Load("HP/(2).png");
imageHP[2]=IMG_Load("HP/(3).png");
imageHP[3]=IMG_Load("HP/(4).png");
imageHP[4]=IMG_Load("HP/(5).png");
imageHP[5]=IMG_Load("HP/(6).png");
imageHP[6]=IMG_Load("HP/(7).png");
imageHP[7]=IMG_Load("HP/(8).png");
imageHP[8]=IMG_Load("HP/(9).png");
imageHP[9]=IMG_Load("HP/(10).png");
imageHP[10]=IMG_Load("HP/(11).png");
imageHP[11]=IMG_Load("HP/(12).png");
imageHP[12]=IMG_Load("HP/(13).png");
imageHP[13]=IMG_Load("HP/(14).png");
imageHP[14]=IMG_Load("HP/(15).png");
imageHP[15]=IMG_Load("HP/(16).png");
imageHP[16]=IMG_Load("HP/(17).png");
imageHP[17]=IMG_Load("HP/(18).png");
imageHP[18]=IMG_Load("HP/(19).png");
imageHP[19]=IMG_Load("HP/(20).png");
imageHP[20]=IMG_Load("HP/(21).png");
imageHP[21]=IMG_Load("HP/(22).png");
imageHP[22]=IMG_Load("HP/(23).png");
imageHP[23]=IMG_Load("HP/(24).png");
imageHP[24]=IMG_Load("HP/(25).png");
imageHP[25]=IMG_Load("HP/(26).png");
imageHP[26]=IMG_Load("HP/(27).png");
imageHP[27]=IMG_Load("HP/(28).png");
imageHP[28]=IMG_Load("HP/(29).png");
imageHP[29]=IMG_Load("HP/(30).png");
imageHP[30]=IMG_Load("HP/(31).png");
imageHP[31]=IMG_Load("HP/(32).png");
imageHP[32]=IMG_Load("HP/(33).png");
imageHP[33]=IMG_Load("HP/(34).png");
imageHP[34]=IMG_Load("HP/(35).png");
imageHP[35]=IMG_Load("HP/(36).png");
imageHP[36]=IMG_Load("HP/(37).png");
imageHP[37]=IMG_Load("HP/(38).png");
imageHP[38]=IMG_Load("HP/(39).png");
imageHP[39]=IMG_Load("HP/(40).png");
imageHP[40]=IMG_Load("HP/(41).png");
imageHP[41]=IMG_Load("HP/(42).png");
imageHP[42]=IMG_Load("HP/(43).png");
imageHP[43]=IMG_Load("HP/(44).png");
imageHP[44]=IMG_Load("HP/(45).png");
imageHP[45]=IMG_Load("HP/(46).png");
imageHP[46]=IMG_Load("HP/(47).png");
imageHP[47]=IMG_Load("HP/(48).png");
imageHP[48]=IMG_Load("HP/(49).png");
imageHP[49]=IMG_Load("HP/(50).png");
}
typedef struct
{
	int status;
	SDL_Rect positionmilieu;
	float vx,vy;
} Sprite;

typedef struct
{
int curframe,curframey ,maxframe;
} frame;

typedef struct 
{
	frame Sprite;
	int maxdistance,mindistance;
	SDL_Surface* imageEnnemie,imageEnnemieAttack;
	SDL_Rect positionmilieu,positionperso;	
}ennemie;

void InitEnnemie (ennemie e[])
{ e[0].imageEnnemie=IMG_Load("PERSO/ennemie1.png");

e[0].positionperso.x=0;
e[0].positionperso.y=0;
e[0].positionperso.h=60;
e[0].positionperso.w=50;

e[0].positionmilieu.x=850;
e[0].positionmilieu.y=342;

e[0].Sprite.curframe=0;
e[0].Sprite.curframey=0;
e[0].Sprite.maxframe=13;

e[0].maxdistance=1150;
e[0].mindistance=850;
}

void Evolue_ennemie(ennemie e[])
{

    if (e[0].positionmilieu.x<e[0].maxdistance && e[0].Sprite.curframey==0)
        {
         			e[0].Sprite.curframe++;
	 				e[0].positionmilieu.x++;
         if (e[0].Sprite.curframe>e[0].Sprite.maxframe)
            { e[0].Sprite.curframe=0;
            
            }
		 e[0].positionperso.x=e[0].Sprite.curframe * e[0].positionperso.w;
         e[0].positionperso.y=e[0].Sprite.curframey * e[0].positionperso.h;
         		
         		if (e[0].positionmilieu.x==e[0].maxdistance)
         	{
         		e[0].Sprite.curframey=1;
         	}
        }
 if (e[0].positionmilieu.x>e[0].mindistance && e[0].Sprite.curframey==1)
         		{

         			e[0].Sprite.curframe++;
         			e[0].positionmilieu.x--;
	 	
         if (e[0].Sprite.curframe>e[0].Sprite.maxframe)
            { e[0].Sprite.curframe=0;
            
            }
		 e[0].positionperso.x=e[0].Sprite.curframe * e[0].positionperso.w;
         e[0].positionperso.y=e[0].Sprite.curframey * e[0].positionperso.h;
         		

         		if (e[0].positionmilieu.x==e[0].mindistance)
         	{
        		e[0].Sprite.curframey=0;
         	}
      }

}

void Render_Ennemie(ennemie e[],SDL_Surface* screen)
{
	SDL_BlitSurface(e[0].imageEnnemie,&e[0].positionperso, screen, &e[0].positionmilieu);
}


void InitSprite(Sprite* Sp)
{
	Sp->positionmilieu.x = 100.0f;
	Sp->positionmilieu.y = 250.0f;
	Sp->status = STAT_SOL;
	Sp->vx = Sp->vy = 0.0f;
}
void InitFrame (frame* f)
{
 f->curframe=0;
 f->curframey=0;
 f->maxframe=10;
}

void InitFond (SDL_Rect *positionFond)
{
	 positionFond->x = 0;
    positionFond->y = 0;
    positionFond->h =600;
    positionFond->w =800;
}
void InitPerso(SDL_Rect * positionperso)
{

    positionperso->x=0;
    positionperso->y=0;
    positionperso->h=60;
    positionperso->w=50;

}

SDL_Color GetColor(SDL_Surface* imageDeFondBlanc,int x,int y)
{
	SDL_Color color;
	Uint32 col=0;
	char* positionperso=(char*)imageDeFondBlanc->pixels;
	positionperso+=(imageDeFondBlanc->pitch*y);
	positionperso+=(imageDeFondBlanc->format->BytesPerPixel*x);
	memcpy(&col,positionperso,imageDeFondBlanc->format->BytesPerPixel);
	SDL_GetRGB(col,imageDeFondBlanc->format,&color.r,&color.g,&color.b);
	printf("%d %d %d \n",color.r,color.g,color.b );
	return (color) ;
}



void Render(Sprite* Sp,SDL_Surface* screen,SDL_Surface* imageDePerso,SDL_Rect positionperso)
{	
	SDL_BlitSurface(imageDePerso,&positionperso, screen, &Sp->positionmilieu);
	
}
void Render_attack(Sprite* Sp,SDL_Surface* screen,SDL_Surface* imageDePersoAttack,SDL_Rect positionperso)
{

	SDL_BlitSurface(imageDePersoAttack,&positionperso, screen, &Sp->positionmilieu);
}


void Saute(Sprite* Sp,float impulsion)
{
	Sp->vy = -impulsion;
	Sp->status = STAT_AIR;
}

void ControleSol(Sprite* Sp)
{
	if (Sp->positionmilieu.y>250.0f)
	{
		Sp->positionmilieu.y = 250.0f;
		if (Sp->vy>0)
			Sp->vy = 0.0f;
		Sp->status = STAT_SOL;
	}
}

void Gravite(Sprite* Sp,float factgravite,float factsautmaintenu,Uint8* keys)
{
	if (Sp->status == STAT_AIR && keys[SDLK_SPACE])
		factgravite/=factsautmaintenu;
	Sp->vy += factgravite;
}

void Gravite_souris(Sprite* Sp,float factgravite,float factsautmaintenu,int ms_y)
{
	if (Sp->status == STAT_AIR && ms_y<Sp->positionmilieu.y+60)
		factgravite/=factsautmaintenu;
	Sp->vy += factgravite;
}


void Evolue(Sprite* Sp,Uint8* keys,SDL_Rect *positionFond,SDL_Rect *positionperso,frame *f)
{
	int i;

	  SDL_EnableKeyRepeat(10, 10);
	float lateralspeed = 0.5f;
	float airlateralspeedfacteur = 0.5f;
	float maxhspeed = 5.0f;
	float adherance = 1.5f;
	float impulsion = 6.0f;
	float factgravite = 0.5f;
	float factsautmaintenu = 3.0f;
// controle lateral
	if (Sp->status == STAT_AIR) // (*2)
		lateralspeed*= airlateralspeedfacteur;
	if (keys[SDLK_LEFT]) // (*1)
		{Sp->vx-=lateralspeed;
		  f->curframey=1;
	 	  f->curframe++;
	 	
         if (f->curframe>f->maxframe)
            { f->curframe=0;
            
            }
         positionperso->x=f->curframe * positionperso->w;
         positionperso->y=f->curframey * positionperso->h;
    	}
	if (keys[SDLK_RIGHT])
		{Sp->vx+=lateralspeed;
			f->curframey=0;
	
		f->curframe++;
        if (f->curframe>f->maxframe)
           { f->curframe=0;
            
            }
         positionperso->x= f->curframe * positionperso->w;
         positionperso->y=f->curframey * positionperso->h;
     	}
	if (Sp->status == STAT_SOL && !keys[SDLK_LEFT] && !keys[SDLK_RIGHT]) // (*3)
		Sp->vx/=adherance;
// limite vitesse
	if (Sp->vx>maxhspeed) // (*4)
		Sp->vx = maxhspeed;
	if (Sp->vx<-maxhspeed)
		Sp->vx = -maxhspeed;
// saut
	if (keys[SDLK_SPACE] && Sp->status == STAT_SOL)
		Saute(Sp,impulsion);
	Gravite(Sp,factgravite,factsautmaintenu,keys);
	ControleSol(Sp);
	if(keys[SDLK_c])
		{if (f->curframey==0)	
			{  f->curframe++;
	 	
         if (f->curframe>f->maxframe)
            { f->curframe=0;
            
            }
         positionperso->x=f->curframe * positionperso->w;
         positionperso->y=f->curframey * positionperso->h;
    	

			}

		if (f->curframey==1)	
				{  f->curframe++;
	 	
         if (f->curframe>f->maxframe)
            { f->curframe=0;
            
            }
         positionperso->x=f->curframe * positionperso->w;
         positionperso->y=f->curframey * positionperso->h;


			}
		 positionperso->x= f->curframe * positionperso->w;
         positionperso->y=f->curframey * positionperso->h;
		}
// application du vecteur à la position.

	if(Sp->vx>0)
		{if (Sp->positionmilieu.x>=516 && positionFond->x<=7200)
		
			positionFond->x += Sp->vx;
		
	else if (Sp->positionmilieu.x<=750) 
		Sp->positionmilieu.x += Sp->vx;
		}
	else if(Sp->vx<0)
		{if (Sp->positionmilieu.x<=258 && positionFond->x>=0)
		
			positionFond->x += Sp->vx;
		
	else if (Sp->positionmilieu.x>=50)  
		Sp->positionmilieu.x += Sp->vx;
		}
	Sp->positionmilieu.y += Sp->vy;

}
void collision(SDL_Surface* imageDeFondBlanc,Sprite* Sp,SDL_Surface* screen,SDL_Rect positionperso)
{
SDL_Color color;
int x,y;
do{
x=Sp->positionmilieu.x+positionperso.w/2;
y=Sp->positionmilieu.y+positionperso.h+1;
color=GetColor(imageDeFondBlanc,x,y);
if(color.r!=255 || color.g!=255 || color.b!=255)
Sp->positionmilieu.y++;
}while(color.r!=255 && color.g!=255 && color.b!=255);
printf("%d\n",Sp->positionmilieu.y);
}


//souris
void Evolue_souris(Sprite* Sp,int ms_x,int ms_y,SDL_Rect *positionFond,SDL_Rect *positionperso,frame *f)
{
	

	 SDL_EnableKeyRepeat(10, 10);
	float lateralspeed = 0.5f;
	float airlateralspeedfacteur = 0.5f;
	float maxhspeed = 5.0f;
	float adherance = 1.5f;
	float impulsion = 6.0f;
	float factgravite = 0.5f;
	float factsautmaintenu = 3.0f;
// controle lateral
	if (Sp->status == STAT_AIR) // (*2)
		lateralspeed*= airlateralspeedfacteur;
	if (ms_x<Sp->positionmilieu.x) // (*1)
		{Sp->vx-=lateralspeed;
		  f->curframey=1;
	 	  f->curframe++;
	 	
         if (f->curframe>f->maxframe)
            { f->curframe=0;
            
            }
         positionperso->x=f->curframe * positionperso->w;
         positionperso->y=f->curframey * positionperso->h;
    	}
	if (ms_x>positionperso->w+Sp->positionmilieu.x)
		{Sp->vx+=lateralspeed;
			f->curframey=0;
	
		f->curframe++;
        if (f->curframe>f->maxframe)
           { f->curframe=0;
            
            }
         positionperso->x= f->curframe * positionperso->w;
         positionperso->y=f->curframey * positionperso->h;
     	}
	if (Sp->status == STAT_SOL && ms_x>Sp->positionmilieu.x && ms_x<positionperso->w+Sp->positionmilieu.x ) // (*3)
		Sp->vx/=adherance;
// limite vitesse
	if (Sp->vx>maxhspeed) // (*4)
		Sp->vx = maxhspeed;
	if (Sp->vx<-maxhspeed)
		Sp->vx = -maxhspeed;
// saut
	if (ms_y<225 && Sp->status == STAT_SOL)
		Saute(Sp,impulsion);
	Gravite_souris(Sp,factgravite,factsautmaintenu,ms_y);
	ControleSol(Sp);

// application du vecteur à la position.

	if(Sp->vx>0)
		{if (Sp->positionmilieu.x>=516 && positionFond->x<=7200)
		
			positionFond->x += Sp->vx;
		
	else if (Sp->positionmilieu.x<=750) 
		Sp->positionmilieu.x += Sp->vx;
		}
	else if(Sp->vx<0)
		{if (Sp->positionmilieu.x<=258 && positionFond->x>=0)
		
			positionFond->x += Sp->vx;
		
	else if (Sp->positionmilieu.x>=50)  
		Sp->positionmilieu.x += Sp->vx;
		}
	Sp->positionmilieu.y += Sp->vy;

}
//HP
void HP_Barre (Uint8* keys,SDL_Surface* screen,SDL_Surface * imageHP[],int *x)
{int i;

if ( keys[SDLK_x])
{                for ( i = *x; i <(*x)+10 ; i++)
                {
                    SDL_BlitSurface(imageHP[i],NULL,screen,NULL);
                    SDL_Delay(50);
                    SDL_Flip(screen);
                    

                }
                 (*x)+=10;
                  
}
}

void recommence (int *x,Sprite *Sp, SDL_Rect *positionFond)
{if ((*x)>=50)
	{ (*x)=0;
		InitFond(positionFond);
		InitSprite(Sp);
	}

}

int main(int argc,char** argv)
{
	frame f;
	SDL_Surface* screen,*imageDePerso=NULL,*imageDePersoAttack=NULL,*imageDeFond=NULL,*imageDeFondBlanc=NULL,*imageHP[50];
	imageDeFond = IMG_Load("LVL1.png");
	imageDePerso = IMG_Load("sprite2.png");
	imageDePersoAttack=IMG_Load("sprite2.1.png");
	imageDeFondBlanc=IMG_Load("LVL1B.png");
	ennemie e[6];

	InitEnnemie(e);
	HP(imageHP);

	SDL_Rect positionFond , positionperso;
InitFond(&positionFond);
InitPerso(&positionperso);
  

 int continuer = 1,x=0,ms_x,ms_y;
    SDL_Event event;
	int numkeys;
	Uint8 * keys,ms;
	Sprite S;
	Uint32 timer,elapsed;
	SDL_Init(SDL_INIT_VIDEO);
	screen=SDL_SetVideoMode(800,600,32,SDL_SWSURFACE|SDL_DOUBLEBUF);
	
	InitSprite(&S);

	InitFrame(&f);
	
	do 
	{	 SDL_BlitSurface(imageDeFondBlanc,&positionFond, screen, NULL);
	 	SDL_BlitSurface(imageDeFond,&positionFond, screen, NULL);
		SDL_BlitSurface(imageHP[x],NULL,screen,NULL);
		timer = SDL_GetTicks();
	
		
		 SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;}
SDL_PumpEvents();
		keys = SDL_GetKeyState(&numkeys);
		ms=SDL_GetMouseState(&ms_x,&ms_y);
		Evolue(&S,keys,&positionFond,&positionperso,&f);
		Evolue_ennemie(e);
		//Evolue_souris(&S,ms_x,ms_y,&positionFond,&positionperso,&f);
		// collision(imageDeFondBlanc,&S, screen, positionperso);
		if (keys[SDLK_c])
			Render_attack(&S,screen,imageDePersoAttack,positionperso);
		else

			Render(&S,screen,imageDePerso,positionperso);
		Render_Ennemie(e,screen);
		HP_Barre(keys,screen,imageHP,&x);
		recommence(&x,&S,&positionFond);
		SDL_Flip(screen);
		elapsed = SDL_GetTicks() - timer;
		if (elapsed<20)
			SDL_Delay(20-elapsed);
	} while (!keys[SDLK_ESCAPE] && continuer);
	SDL_Quit();
	return 0;
}
