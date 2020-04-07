#include "entite_secondaire.h"
#include "background.h"

int main(void)
{
    SDL_Surface *screen = NULL;
    SDL_Event event;
    int continuer = 1;
    background background;
    entite enemie;

    initialiser_background(&background);
    init_entite(&enemie);

    screen = SDL_SetVideoMode(background.image->w, background.image->h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    
    while (continuer)
    {
        SDL_PollEvent(&event);
        afficher_background(&background, screen);
        deplacer_alea(&enemie);
        animation(&enemie);
        afficher_entite(&enemie, screen);
        SDL_Flip(screen);
        //SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            }
        }
    }
    free_background(&background);
    free_entite(&enemie);
    SDL_Quit();
    return 0;
}