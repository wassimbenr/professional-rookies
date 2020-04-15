#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include "functions.h"



void FireAnimation (SDL_Surface *ecran)
{
    SDL_Surface *tab[300];
    SDL_Rect positionFond;

    positionFond.x = 0;
    positionFond.y = 0;


    int j=299,k=1;
    char frr[100];
    for (j=0; j<298; j++)
    {
        sprintf(frr,"frames/(%d).bmp",j+1);
        tab[j]=SDL_LoadBMP(frr);
    }




SDL_Event event;

    while (k!=0 && j>=0) {
  SDL_BlitSurface(tab[j],NULL,ecran, &positionFond);
  SDL_Flip(ecran);
  SDL_Delay(50);
  j--;
  SDL_PollEvent(&event);
  if (event.key.keysym.sym == SDLK_RETURN) {
    k=0;
  }
}


}



void Intro (SDL_Surface *ecran)
{
    SDL_Surface *tab[1500];
    SDL_Rect positionFond;

    positionFond.x = 0;
    positionFond.y = 0;


    int j=1498,k=1;
    char frr[100];
    for (j=0; j<1498; j++)
    {
        sprintf(frr,"valhala/(%d).png",j+1);
        tab[j]=IMG_Load(frr);

    
        SDL_BlitSurface(tab[j],NULL,ecran, &positionFond);
        SDL_Flip(ecran);
        SDL_Delay(6);
    }


}



