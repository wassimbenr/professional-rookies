#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
int main(void)
{
    SDL_Surface *screen = NULL;
    SDL_Surface *background = NULL;
    SDL_Rect positionBackground;
    SDL_Rect positionText;
    SDL_WM_SetCaption("Test", NULL);
    screen = SDL_SetVideoMode(480, 360, 32, SDL_HWSURFACE);
    background = IMG_Load("img/backgrounds/piano.png"); // f hot l background f dossier img/background
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    TTF_Font *police = NULL;
    SDL_Surface *texte = NULL;
    positionBackground.x = 0;
    positionBackground.y = 0;
    SDL_Color couleur = {0, 0, 0};
    SDL_Event event;
    int continuer = 1;
    police = TTF_OpenFont("fonts/angelina.TTF", 15);
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
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_d:
                {
                    texte = TTF_RenderText_Blended(police, "Do", couleur);
                    positionText.x = 32;
                    positionText.y = 262;
                    break;
                }
                case SDLK_r:
                {
                    texte = TTF_RenderText_Blended(police, "Re", couleur);
                    positionText.x = 87;
                    positionText.y = 262;
                    break;
                }
                }
            }
        }
        SDL_BlitSurface(background, NULL, screen, &positionBackground);
        SDL_BlitSurface(texte, NULL, screen, &positionText);
        SDL_Flip(screen);
    }
    SDL_FreeSurface(background);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_FreeSurface(texte);
    SDL_Quit();
    return 0;
}
