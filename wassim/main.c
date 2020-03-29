#include "entite_secondaire.h"
int main(void)
{
    SDL_Surface *screen = NULL;
    SDL_Surface *background = NULL;
    SDL_Rect positionBackground;
    SDL_Rect positionscreen;
    SDL_WM_SetCaption("wassim", NULL);
    background = IMG_Load("img/backgrounds/full-bg.png");
    screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    positionBackground.x = 00;
    positionBackground.y = 0;
    positionscreen.x = 0;
    positionscreen.y = 800;
    positionscreen.w = 800;
    positionscreen.h = 600;
    SDL_Color couleur = {0, 0, 0};
    SDL_Event event;
    int continuer = 1;
    if (!screen)
    {
        fprintf(stderr, "Impossible de charger le mode video: %s\n", SDL_GetError());
        printf("Window not created\n");
        exit(EXIT_FAILURE);
    }
    if (!background)
    {
        printf("Unable to Load Image%s\n", SDL_GetError());
        return 1;
    }

    entite enemie;
    init_entite(&enemie);



    SDL_EnableKeyRepeat(5, 5);
    while (continuer)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            }
        }
        SDL_BlitSurface(background, &positionscreen, screen, &positionBackground);
        
        afficher_entite(&enemie,screen);
        SDL_Flip(screen);
    }
    SDL_FreeSurface(background);
    SDL_Quit();
    return 0;
}