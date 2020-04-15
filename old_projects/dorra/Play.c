#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "functions.h"
#ifdef WIN32
#pragma comment(lib,"sdl.lib")
#pragma comment(lib,"sdlmain.lib")
#endif

#define STAT_SOL 0
#define STAT_AIR 1


void HP (int player,SDL_Surface * imageHP[])
{
    int fr;
    char imgname[100];
	if(player==2)
    for (fr=0; fr<50; fr++)
    {
        sprintf(imgname,"HP2/(%d).png",fr+1);
        imageHP[fr]=IMG_Load(imgname);
    }
else if(player==1)
    for (fr=0; fr<50; fr++)
    {
        sprintf(imgname,"HP1/(%d).png",fr+1);
        imageHP[fr]=IMG_Load(imgname);
	}
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
    SDL_Color color, white= {0,0,0};
    Uint32 col=0;
    if (x<8000 && y<600)
    {
        char* positionperso=(char*)imageDeFondBlanc->pixels;
        positionperso+=(imageDeFondBlanc->pitch*y);
        positionperso+=(imageDeFondBlanc->format->BytesPerPixel*x);
        memcpy(&col,positionperso,imageDeFondBlanc->format->BytesPerPixel);
        SDL_GetRGB(col,imageDeFondBlanc->format,&color.r,&color.g,&color.b);
        
        return (color) ;
    }
    else return(white);
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



void mapCollision(Sprite *Sp,SDL_Surface *imageDeFondBlanc,SDL_Rect *positionperso,SDL_Rect *positionFond)
{
    // x pour les positions x , y pour les positions y , g pour dire gauche , d pour dire droite
    int  xg, xd, yg, yd,test;
    // les pixer qu'on va  avoir sur eux nos test
    SDL_Color PixelToCompare1,PixelToCompare2;
    // on lock la surface de collusion pour tester les pixe

    SDL_LockSurface(imageDeFondBlanc);



    //On va calculer ici les coins de notre sprite à gauche et à droite pour voir quelle pixel on touche

    xg =Sp->positionmilieu.x+positionFond->x+Sp->vx;
    xd =Sp->positionmilieu.x+positionFond->x+Sp->vx + positionperso->w;

    //le meme pour les y

    yd = yg =Sp->positionmilieu.y+positionperso->h/2;




    //De là, on va tester les mouvements initiés dans updatePlayer grâce aux vecteurs
    //dirX et dirY, tout en testant avant qu'on se situe bien dans les limites de l'écran.

    if (xg >0 && xd < 8000 && yg >= 0 && yd < 600)
    {
        //Si on a un mouvement à droite

        if ( Sp->vx> 0)
        {

            //On vérifie si les pixels recouvertes sont noir
            PixelToCompare1= GetColor(imageDeFondBlanc,xd,yg);
            PixelToCompare2= GetColor(imageDeFondBlanc,xd,yd);
            test = ((PixelToCompare1.r == 0) && (PixelToCompare1.b == 0) && (PixelToCompare1.g == 0)) && ((PixelToCompare2.r == 0) && (PixelToCompare2.b == 0) && (PixelToCompare2.g == 0));
            if (!test)
            {
                // Si c'est le cas, on place le joueur aussi près que possible
                // de ces tiles, en mettant à jour ses coordonnées. Enfin, on réinitialise
                //son vecteur déplacement (dirX).

                Sp->positionmilieu.x-=  Sp->vx;



                Sp->vx = 0;

            }

        }

        //Même chose à gauche

        else if (Sp->vx < 0)
        {
            PixelToCompare1= GetColor(imageDeFondBlanc,xg,yg);
            PixelToCompare2= GetColor(imageDeFondBlanc,xg,yd);
            test = ((PixelToCompare1.r == 0) && (PixelToCompare1.b == 0) && (PixelToCompare1.g == 0)) && ((PixelToCompare2.r == 0) && (PixelToCompare2.b == 0) && (PixelToCompare2.g == 0));

            if (!test)
            {

                Sp->positionmilieu.x-=  Sp->vx;



                Sp->vx = 0;

            }


        }

    }








    xg = (Sp->positionmilieu.x+positionFond->x);
    xd = Sp->positionmilieu.x +positionFond->x +positionperso->w/2;

    yg = (Sp->positionmilieu.y+ Sp->vy);
    yd = (Sp->positionmilieu.y + Sp->vy + positionperso->h);

    if (xg >= 0 && xd < 8008 && yg >= 0 && yd < 600)
    {
        if ( Sp->vy > 0)
        {
            PixelToCompare1= GetColor(imageDeFondBlanc,xd,yd);
            PixelToCompare2= GetColor(imageDeFondBlanc,xg,yd);
            test = ((PixelToCompare1.r == 0) && (PixelToCompare1.b == 0) && (PixelToCompare1.g == 0)) && ((PixelToCompare2.r == 0) && (PixelToCompare2.b == 0) && (PixelToCompare2.g == 0));

            /* Déplacement en bas */
            if (!test)
            {
                //Si la pixel est noir, on y colle le joueur et
                //on le déclare sur le sol (onGround).
                Sp->positionmilieu.y = yd;
                Sp->positionmilieu.y -= positionperso->h+0.5;
                Sp->vy= 0;

                Sp->onGround = 1;
                Sp->status = STAT_SOL;
            }

        }


    }



    if(Sp->vx>0)
    {
        if (Sp->positionmilieu.x>=516 && positionFond->x<=7200)

            positionFond->x += Sp->vx;

        else if (Sp->positionmilieu.x<=750)
            Sp->positionmilieu.x += Sp->vx;
    }
    else if(Sp->vx<0)
    {
        if (Sp->positionmilieu.x<=258 && positionFond->x>=0)

            positionFond->x += Sp->vx;

        else if (Sp->positionmilieu.x>=50)
            Sp->positionmilieu.x += Sp->vx;
    }
    Sp->positionmilieu.y += Sp->vy;
    if (Sp->positionmilieu.y>=600)
    {
        InitFond(positionFond);
        InitSprite(Sp);
    }


    SDL_UnlockSurface(imageDeFondBlanc);

}
//aaaaaaaaaa
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


void Evolue(Sprite* Sp,Uint8* keys,SDL_Rect *positionFond,SDL_Rect *positionperso,frame *f,SDL_Surface* imageDeFondBlanc)
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
    {
        Sp->vx-=lateralspeed;
        f->curframey=1;
        f->curframe++;

        if (f->curframe>f->maxframe)
        {
            f->curframe=0;

        }
        positionperso->x=f->curframe * positionperso->w;
        positionperso->y=f->curframey * positionperso->h;
    }
    if (keys[SDLK_RIGHT])
    {
        Sp->vx+=lateralspeed;
        f->curframey=0;

        f->curframe++;
        if (f->curframe>f->maxframe)
        {
            f->curframe=0;

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
    mapCollision(Sp,imageDeFondBlanc,positionperso,positionFond);

    {
        /* if(keys[SDLK_c])
        {
           if (f->curframey==0)
           {
               f->curframe++;

               if (f->curframe>f->maxframe)
               {
                   f->curframe=0;

               }
               positionperso->x=f->curframe * positionperso->w;
               positionperso->y=f->curframey * positionperso->h;


           }

           if (f->curframey==1)
           {
               f->curframe++;

               if (f->curframe>f->maxframe)
               {
                   f->curframe=0;

               }
               positionperso->x=f->curframe * positionperso->w;
               positionperso->y=f->curframey * positionperso->h;


           }
           positionperso->x= f->curframe * positionperso->w;
           positionperso->y=f->curframey * positionperso->h;

        }*/
// application du vecteur à la position.

        /*  if(Sp->vx>0)
          {
              if (Sp->positionmilieu.x>=516 && positionFond->x<=7200)

                  positionFond->x += Sp->vx;

              else if (Sp->positionmilieu.x<=750)
                  Sp->positionmilieu.x += Sp->vx;
          }
          else if(Sp->vx<0)
          {
              if (Sp->positionmilieu.x<=258 && positionFond->x>=0)

                  positionFond->x += Sp->vx;

              else if (Sp->positionmilieu.x>=50)
                  Sp->positionmilieu.x += Sp->vx;
          }
          Sp->positionmilieu.y += Sp->vy;*/


    }
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
    {
        Sp->vx-=lateralspeed;
        f->curframey=1;
        f->curframe++;

        if (f->curframe>f->maxframe)
        {
            f->curframe=0;

        }
        positionperso->x=f->curframe * positionperso->w;
        positionperso->y=f->curframey * positionperso->h;
    }
    if (ms_x>positionperso->w+Sp->positionmilieu.x)
    {
        Sp->vx+=lateralspeed;
        f->curframey=0;

        f->curframe++;
        if (f->curframe>f->maxframe)
        {
            f->curframe=0;

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
    {
        if (Sp->positionmilieu.x>=516 && positionFond->x<=7200)

            positionFond->x += Sp->vx;

        else if (Sp->positionmilieu.x<=750)
            Sp->positionmilieu.x += Sp->vx;
    }
    else if(Sp->vx<0)
    {
        if (Sp->positionmilieu.x<=258 && positionFond->x>=0)

            positionFond->x += Sp->vx;

        else if (Sp->positionmilieu.x>=50)
            Sp->positionmilieu.x += Sp->vx;
    }
    Sp->positionmilieu.y += Sp->vy;

}
//HP
void HP_Barre (Uint8* keys,SDL_Surface* screen,SDL_Surface * imageHP[],int *x)
{
    int i;

    if ( keys[SDLK_x])
    {
        for ( i = *x; i <(*x)+10 ; i++)
        {
            SDL_BlitSurface(imageHP[i],NULL,screen,NULL);
            SDL_Delay(50);
            SDL_Flip(screen);


        }
        (*x)+=10;

    }
}

void recommence (int *x,Sprite *Sp, SDL_Rect *positionFond)
{
    if ((*x)>=50)
    {
        (*x)=0;
        InitFond(positionFond);
        InitSprite(Sp);
    }

}

void play(int player,SDL_Surface *screen)
{   int LEVEL=3;
    frame f;
    SDL_Surface *imageDePerso=NULL,*imageDePersoAttack=NULL,*imageDeFond=NULL,*imageDeFondBlanc=NULL,*imageHP[50];
   
    switch (player)
    {
        case (1):
    imageDePerso = IMG_Load("sprite.png");
    imageDePersoAttack=IMG_Load("sprite2.1.png");
    break;

    case (2):
    imageDePerso = IMG_Load("sprite2.png");
    imageDePersoAttack=IMG_Load("sprite2.1.png");
    break;
    }

    
    switch (LEVEL)
        {case (1):  imageDeFond = IMG_Load("LVL1.png");
        imageDeFondBlanc=IMG_Load("LVL1B.png");
        break;
        case (2):  imageDeFond = IMG_Load("LVL2.png");
        imageDeFondBlanc=IMG_Load("LVL2B.png");
        break;
        case (3):  imageDeFond = IMG_Load("LVL3.png");
        imageDeFondBlanc=IMG_Load("LVL3B.png");
        break;
        }

    
    HP(player,imageHP);

    SDL_Rect positionFond, positionperso;
    InitFond(&positionFond);
    InitPerso(&positionperso);


    int continuer = 1,x=0,ms_x,ms_y;
    SDL_Event event;
    int numkeys;
    Uint8 * keys,ms;
    Sprite S;
    Uint32 timer,elapsed;

    Ennemi E;
    initEnnemi(&E);
    InitSprite(&S);

    InitFrame(&f);

    do
    { 

        SDL_BlitSurface(imageDeFondBlanc,&positionFond, screen, NULL);
        //SDL_BlitSurface(imageDeFond,&positionFond, screen, NULL);
    
        SDL_BlitSurface(imageHP[x],NULL,screen,NULL);
        timer = SDL_GetTicks();


        SDL_PollEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        }
        SDL_PumpEvents();
        keys = SDL_GetKeyState(&numkeys);
        //ms=SDL_GetMouseState(&ms_x,&ms_y);
        Evolue(&S,keys,&positionFond,&positionperso,&f,imageDeFondBlanc);
    
        //Evolue_souris(&S,ms_x,ms_y,&positionFond,&positionperso,&f);
        
        if (keys[SDLK_c])
            Render_attack(&S,screen,imageDePersoAttack,positionperso);
        else

            Render(&S,screen,imageDePerso,positionperso);
        input_ennemi(&E , positionperso);
        blitEnnemi(&E,screen,positionFond);
        HP_Barre(keys,screen,imageHP,&x);
        recommence(&x,&S,&positionFond);
        SDL_Flip(screen);
        elapsed = SDL_GetTicks() - timer;
        if (elapsed<20)
            SDL_Delay(20-elapsed);
    }
    while (!keys[SDLK_ESCAPE] && continuer);
    SDL_Quit();
}
