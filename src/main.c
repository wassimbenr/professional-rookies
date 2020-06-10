/**
 * @file main.c
 */
#include "background.h"
#include "entite_secondaire.h"
#include "hero.h"
#include "collision.h"
#include "enigme.h"
#include "menu.h"
#include "structs.h"
#include "defs.h"
#include "multiplayer.h"

void main(int argc, char *argv[])
{
    SDL_Surface *tab[341];
    SDL_Surface *story[799];
    etat etat = MENU;

    load_intro(tab);
    load_story_intro(story);

    //load_intro(tab);

    int continuer = 1;

    SDL_Surface *screen;

    hero safwen, safwen2;
    background background, background1, background2;
    parameter parameter;
    dialogue d;

    initialiser_parameters(&parameter);

    character c;

    SDL_Event event;

    SDL_Init(SDL_INIT_EVERYTHING);

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    while (continuer)
    {
        switch (etat)
        {
        case INTRO:
            play_intro(tab, screen, &etat, &parameter);
            break;
        case STORY_INTRO:
            play_story_intro(screen, &etat, &parameter, story);
            break;
        case MENU:
            menu(screen, &etat, &parameter);
            break;
        case GAME:
            jeu(screen, &etat, &safwen, &parameter, c, background, d);
            break;
        case MULTIPLAYER:
            multiplayer(screen, &etat, &parameter, c);
            break;
        case SETTING:
            settings(screen, &parameter, &etat);
            break;
        case GAME_OVER:
            game_over(screen, &etat, &parameter, &safwen);
            break;
        case CHARACTER:
            character_choice(&safwen, &etat, screen, &parameter, &c);
            break;
        case GAME_LOAD:
            game_load(&safwen, &background, &etat, screen, &parameter, &c, &d);
            break;
        case CHEAT:
            cheat(screen, &etat, parameter);
            break;
        case CREDS:
            play_credits(screen, &etat, &parameter);
            break;
        case EXIT:
            continuer = 0;
            break;
        }
    }
    Mix_FreeMusic(parameter.music);
    Mix_FreeChunk(parameter.click);
    SDL_FreeSurface(screen);
    SDL_Quit();
}
