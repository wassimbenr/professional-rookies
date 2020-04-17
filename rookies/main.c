#include "background.h"
#include "entite_secondaire.h"
#include "hero.h"
#include "colision.h"
#include "enigme.h"
#include "menu.h"



void main()
{
    hero safwen;
    background background;
    entite ennemie;
    enigme enigme;

    etat etat = MENU;

    SDL_Event event;

    int continuer = 1;
    int volume = 120, mute = 0, fullscreen = 0;

    SDL_Surface *screen;
    SDL_Surface *game_over = IMG_Load("./img/game_over.png");
    SDL_Rect position_game_over;
    position_game_over.x = 0;
    position_game_over.y = 0;

    initialiser_hero(&safwen, "safwen");
    initialiser_background(&background);
    initialiser_entite(&ennemie);
    initenigme(&enigme);

    SDL_Init(SDL_INIT_VIDEO);

    screen = SDL_SetVideoMode(SCREEN_WIDTH + 320, SCREEN_HEIGHT + 120, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_EnableKeyRepeat(2, 2);

    while (continuer)
    {
        if (etat == MENU)
        {
            menu(&etat, volume);
        }
        else if (etat == SETTINGS)
        {
            settings(screen, &mute, &fullscreen, &volume, &etat);
        }
        else if (etat == GAME)
        {
            afficher_background(&background, screen);
            afficher_entite(&ennemie, screen);
            afficher_hero(safwen, screen);

            CollisionParfaite(&safwen, background);

            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    {
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                        {
                        case SDLK_RIGHT:
                            safwen.position.x += 2;
                            animer_hero(&safwen, WALK_RIGHT);
                            break;
                        case SDLK_LEFT:
                            safwen.position.x -= 2;
                            animer_hero(&safwen, WALK_LEFT);
                            break;
                        case SDLK_ESCAPE:
                            etat = MENU;
                            break;
                        }
                        break;
                    case SDL_KEYUP:
                        if (safwen.state == WALK_RIGHT || safwen.state == WALK_LEFT)
                            safwen.state = IDLE;
                        break;
                    }
                }
            }

            attack_entite(&ennemie, &safwen);

            if (ennemie.posMin.x > safwen.position.x)
                deplacer_alea(&ennemie);

            animer_hero(&safwen, safwen.state);
            animer_entite(&ennemie);

            if (safwen.position.x == 900)
                etat = ENIGME;
        }
        else if (etat == ENIGME)
        {
            afficherenigme(&enigme, screen);
            enigme_math(screen,&enigme, &etat);
        }
        else if (etat == GAME_OVER)
        {
            SDL_BlitSurface(game_over, NULL, screen, &position_game_over);
            SDL_Delay(2000);
            etat = MENU;
        }
        else if (etat == EXIT)
            continuer = 0;
        SDL_Flip(screen);
    }
    free_background(&background);
    free_entite(&ennemie);
    free_hero(&safwen);
    freeenigme(&enigme);
    SDL_Quit();
}
