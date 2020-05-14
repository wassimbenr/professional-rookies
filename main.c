
#include "background.h"
#include "entite_secondaire.h"
#include "hero.h"
#include "colision.h"
#include "enigme.h"
#include "menu.h"
#include "structs.h"
#include "defs.h"
//#include "settings.h"

void main()
{
    etat etat = MENU;

    int continuer = 1;
    int mute = 0, fullscreen = 0;

    SDL_Surface *screen;

    SDL_Surface *game_over = IMG_Load("./img/game_over.jpg");
    SDL_Rect position_game_over;
    position_game_over.x = 0;
    position_game_over.y = 0;
    position_game_over.w = SCREEN_WIDTH;
    position_game_over.h = SCREEN_HEIGHT;

    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    while (continuer)
    {
        switch (etat)
        {
        case MENU:
            menu(screen, &etat);
            break;
        case GAME:
            jeu(screen, &etat);
            break;
        case SETTINGS:
            //settings(screen, &mute, &fullscreen, &volume, &etat);
            break;
        case GAME_OVER:
            SDL_BlitSurface(game_over, NULL, screen, &position_game_over);
            SDL_Flip(screen);
            SDL_Delay(2000);
            etat = GAME;
            // scanf if y alors menu , sinon etat = exit
            break;
        case EXIT:
            continuer = 0;
            break;
        }
    }
    SDL_Quit();
}
