#include "background.h"
#include "entite_secondaire.h"
#include "hero.h"
#include "colision.h"
#include "enigme.h"
#include "menu.h"
#include "structs.h"
#include "defs.h"

void main()
{
    etat etat = MENU;

    int continuer = 1;

    SDL_Surface *screen;

    hero safwen;
    background background;
    parameter parameter;

    character c;

    SDL_Event event;

    initialiser_parameters(&parameter);

    SDL_Init(SDL_INIT_EVERYTHING);

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    while (continuer)
    {
        switch (etat)
        {
        case MENU:
            menu(screen, &etat, &parameter);
            break;
        case GAME:
            jeu(screen, &etat, safwen, &parameter, c,background);
            break;
        case SETTINGS:
            settings(screen, &parameter, &etat);
            break;
        case GAME_OVER:
            game_over(screen, &etat, &parameter);
            break;
        case CHARACTER:
            character_choice(&safwen, &etat, screen, &parameter, &c);
            break;
        case GAME_LOAD:
            game_load(&safwen, &background, &etat, screen, &parameter, &c);
            break;
        case EXIT:
            continuer = 0;
            break;
        }
    }
    Mix_FreeMusic(parameter.music);
    Mix_FreeChunk(parameter.click);
    SDL_Quit();
}
