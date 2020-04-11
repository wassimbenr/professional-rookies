#include "entite_secondaire.h"
#include "background.h"
#include "defs.h"

int main(void)
{
    SDL_Surface *screen = NULL;
    SDL_Event event;
    int continuer = 1;
    background background;
    entite enemie;

    initialiser_background(&background);
    init_entite(&enemie);

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //background.image->h

    while (continuer)
    {
        SDL_PollEvent(&event);
        /*if (collisionParfaite(background.background_mask, enemie.sprite.frame, enemie.posEntite) != 1)
        {
            enemie.posEntite.x += 4;
            enemie.Direction = 1;
            animation_entite(&enemie);
        }*/
        //SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            }
        }
        scrolling(&background);
        afficher_background(&background, screen);
        deplacer_alea(&enemie);
        animation_entite(&enemie);
        afficher_entite(&enemie, screen);
        SDL_Flip(screen);
    }
    free_background(&background);
    free_entite(&enemie);
    SDL_Quit();
    return 0;
}