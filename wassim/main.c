#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
int main(void)
{
    SDL_Surface *screen = NULL;
    SDL_Surface *background = NULL;
    SDL_Event event;
    SDL_Rect positionBackground;
    SDL_Rect positionscreen;

    screen = SDL_SetVideoMode(200, 160, 32, SDL_HWSURFACE);
    background = IMG_Load("img/backgrounds/piano.png"); // f hot l background f dossier img/background
    positionBackground.x = 0;
    positionBackground.y = 0;

    positionscreen.x=100;
    positionscreen.y=100;
    positionscreen.w=200;
    positionscreen.h=160;

    SDL_Init(SDL_INIT_VIDEO);

    
    int continuer = 1;


    //SDL_EnableKeyRepeat(5, 5);
    while (continuer)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_d:
                {
                    positionscreen.y-=20;
                    break;
                }
                case SDLK_r:
                {
                    
                    break;
                }
                }
            }
        }
        SDL_BlitSurface(background, &positionscreen, screen, &positionBackground);
  
        SDL_Flip(screen);
    }
    /*SDL_FreeSurface(background);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_FreeSurface(texte);*/
    SDL_Quit();
    return 0;
}
