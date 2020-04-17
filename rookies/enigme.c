#include "enigme.h"

void enigme_math(SDL_Surface *screen,enigme *E,etat *etat)
{

 

    SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                (*etat)= GAME;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    (*etat)= GAME;
                    break;
                case SDLK_DOWN:
                    if (E->rangR == 0)
                    {

                        E->rangR = 2;
                    }
                    else if (E->rangR == 1)
                    {

                        E->rangR = 3;
                    }
                    else if (E->rangR == 2)
                    {

                        E->rangR = 0;
                    }
                    else if (E->rangR == 3)
                    {

                        E->rangR = 1;
                    }
                    break;

                case SDLK_UP:
                    if (E->rangR == 0)
                    {

                        E->rangR = 2;
                    }
                    else if (E->rangR == 1)
                    {

                        E->rangR = 3;
                    }
                    else if (E->rangR == 2)
                    {

                        E->rangR = 0;
                    }
                    else if (E->rangR == 3)
                    {

                        E->rangR = 1;
                    }
                    break;

                case SDLK_LEFT:
                    if (E->rangR == 0)
                    {

                        E->rangR = 1;
                    }
                    else if (E->rangR == 1)
                    {

                        E->rangR = 0;
                    }
                    else if (E->rangR == 2)
                    {

                        E->rangR = 3;
                    }
                    else if (E->rangR == 3)
                    {

                        E->rangR = 2;
                    }
                    break;
                case SDLK_RIGHT:
                    if (E->rangR == 0)
                    {

                        E->rangR = 1;
                    }
                    else if (E->rangR == 1)
                    {

                        E->rangR = 0;
                    }
                    if (E->rangR == 2)
                    {

                        E->rangR = 3;
                    }
                    else if (E->rangR == 3)
                    {

                        E->rangR = 2;
                    }
                    break;

                case SDLK_m:
                    resolutionenigme(E, screen);
                    if (E->resolution == 1)
                    {
                        (*etat) = GAME;
                    }
                    else
                    { 
                        (*etat) = GAME;
                    }
                    break;
                }
            }
            
            //SDL_BlitSurface(Final, NULL, screen, &E->positionFinal);
            //SDL_Flip(screen);
            if ((*etat) == GAME)
                SDL_Delay(300);
        }
    
    //freeenigme(&E);
    //SDL_EnableKeyRepeat(2, 2);
}
