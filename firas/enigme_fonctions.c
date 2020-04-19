#include "enigme.h"

void initenigme(enigme *E)
{
    E->background = IMG_Load("./img/enigme/bgenigme.jpg");
    E->ansewr1 = IMG_Load("./img/enigme/text1.png");
    E->ansewr2 = IMG_Load("./img/enigme/text2.png");
    E->ansewr3 = IMG_Load("./img/enigme/text3.png");
    E->ansewr4 = IMG_Load("./img/enigme/correct.png");
    E->bgansewr = IMG_Load("./img/enigme/ansewr1.jpg");
    E->bghover = IMG_Load("./img/enigme/ansewr2.jpg");
    E->Question = IMG_Load("./img/enigme/question.png");
    E->Yes = IMG_Load("./img/enigme/yes.png");
    E->No = IMG_Load("./img/enigme/no.png");

    E->positionBackground.x = 0;
    E->positionBackground.y = 0;
    E->positionQ.x = 50;
    E->positionQ.y = 50;
    E->positionAnsewr1.x = 100;
    E->positionAnsewr1.y = 200;
    E->positionAnsewr2.x = 450;
    E->positionAnsewr2.y = 200;
    E->positionAnsewr3.x = 100;
    E->positionAnsewr3.y = 400;
    E->positionAnsewr4.x = 450;
    E->positionAnsewr4.y = 400;
    E->positionFinal.x = 100;
    E->positionFinal.y = 100;

    E->rangR = 0;
    E->resolution = -1;
}

void afficherenigme(enigme *E, SDL_Surface *screen)
{
    SDL_BlitSurface(E->background, NULL, screen, &E->positionBackground);
    SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr1);
    SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr2);
    SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr3);
    SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr4);
    SDL_BlitSurface(E->Question, NULL, screen, &E->positionQ);
    SDL_BlitSurface(E->ansewr1, NULL, screen, &E->positionAnsewr1);
    SDL_BlitSurface(E->ansewr2, NULL, screen, &E->positionAnsewr2);
    SDL_BlitSurface(E->ansewr3, NULL, screen, &E->positionAnsewr3);
    SDL_BlitSurface(E->ansewr4, NULL, screen, &E->positionAnsewr4);
    switch (E->rangR)
    {
    case 0:
        SDL_BlitSurface(E->bghover, NULL, screen, &E->positionAnsewr1);
        SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr2);
        SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr3);
        SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr4);
        SDL_BlitSurface(E->ansewr1, NULL, screen, &E->positionAnsewr1);
        SDL_BlitSurface(E->ansewr2, NULL, screen, &E->positionAnsewr2);
        SDL_BlitSurface(E->ansewr3, NULL, screen, &E->positionAnsewr3);
        SDL_BlitSurface(E->ansewr4, NULL, screen, &E->positionAnsewr4);
        break;
    case 1:
        SDL_BlitSurface(E->bghover, NULL, screen, &E->positionAnsewr2);
        SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr1);
        SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr3);
        SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr4);
        SDL_BlitSurface(E->ansewr1, NULL, screen, &E->positionAnsewr1);
        SDL_BlitSurface(E->ansewr2, NULL, screen, &E->positionAnsewr2);
        SDL_BlitSurface(E->ansewr3, NULL, screen, &E->positionAnsewr3);
        SDL_BlitSurface(E->ansewr4, NULL, screen, &E->positionAnsewr4);
        break;
    case 2:
        SDL_BlitSurface(E->bghover, NULL, screen, &E->positionAnsewr3);
        SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr1);
        SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr2);
        SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr4);
        SDL_BlitSurface(E->ansewr1, NULL, screen, &E->positionAnsewr1);
        SDL_BlitSurface(E->ansewr2, NULL, screen, &E->positionAnsewr2);
        SDL_BlitSurface(E->ansewr3, NULL, screen, &E->positionAnsewr3);
        SDL_BlitSurface(E->ansewr4, NULL, screen, &E->positionAnsewr4);
        break;
    case 3:
        SDL_BlitSurface(E->bghover, NULL, screen, &E->positionAnsewr4);
        SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr1);
        SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr2);
        SDL_BlitSurface(E->bgansewr, NULL, screen, &E->positionAnsewr3);
        SDL_BlitSurface(E->ansewr1, NULL, screen, &E->positionAnsewr1);
        SDL_BlitSurface(E->ansewr2, NULL, screen, &E->positionAnsewr2);
        SDL_BlitSurface(E->ansewr3, NULL, screen, &E->positionAnsewr3);
        SDL_BlitSurface(E->ansewr4, NULL, screen, &E->positionAnsewr4);
        break;
    }
    if (E->resolution == 1)
        SDL_BlitSurface(E->Yes, NULL, screen, &E->positionFinal);
    else if (E->resolution == 0)
        {
            SDL_BlitSurface(E->No, NULL, screen, &E->positionFinal);
        }
}

void freeenigme(enigme *E)
{
    SDL_FreeSurface(E->background);
    SDL_FreeSurface(E->bgansewr);
    SDL_FreeSurface(E->bghover);
    SDL_FreeSurface(E->ansewr1);
    SDL_FreeSurface(E->ansewr2);
    SDL_FreeSurface(E->ansewr3);
    SDL_FreeSurface(E->ansewr4);
    SDL_FreeSurface(E->Yes);
    SDL_FreeSurface(E->No);
}

void resolutionenigme(enigme *E, SDL_Surface *screen)
{
    if (E->rangR == 3)
    {
        E->resolution = 1;
    }
    else
    {
        E->resolution = 0;
    }
}

/*void gestiontemps(enigme E, SDL_Surface screen)
{
}*/

/*int generation_auto_enig(enigme E, int randenig)
{
    srand(time(NULL));
    randenig = rand() % 11;
    return randenig;
}*/
