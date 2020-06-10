/**
 * @file enigme_math.c
 */
#include "enigme.h"
#include "hero.h"

void enigme_math(SDL_Surface *screen, enigme *E, hero *h)
{

    SDL_Event event;
    int Econtinue = 1;
    initenigme(E);
    
    while (Econtinue)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                Econtinue = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    Econtinue = 0;
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
                        h->score_hero.valeur_score += 20;
                        Econtinue = 0;
                    }
                    else
                    {
                        h->score_hero.valeur_score -= 20;
                        Econtinue = 0;
                    }
                    break;
                }
            }
            afficherenigme(E, screen);
            SDL_Flip(screen);
            if (Econtinue == 0)
                SDL_Delay(300);
        }
    }

    
}
