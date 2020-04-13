#include "entite_secondaire.h"
#include "background.h"
#include "hero.h"
#include "defs.h"
#include "colision.h"
int main(void)
{
    SDL_Surface *screen = NULL;
    SDL_Event event;
    int continuer = 1;
    background background;
    entite safwen, enemie;

    initialiser_hero(&safwen);
    initialiser_background(&background);
    init_entite(&enemie);

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //background.image->h

    SDL_EnableKeyRepeat(10, 10);

    while (continuer)
    {
        collisionParfaite(&safwen, background);
        printf("%d%d%d%d\n", safwen.collision_UP, safwen.collision_DOWN, safwen.collision_RIGHT, safwen.collision_DOWN);
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
                case SDLK_ESCAPE:
                    continuer = 0;
                    break;
                case SDLK_RIGHT:
                    if (!safwen.collision_RIGHT)
                    {
                        safwen.position.x += 4;
                        safwen.direction = RIGHT;
                        animer_hero(&safwen, WALK);
                        background.posCamera.x+= 4;
                    }
                    break;
                case SDLK_LEFT:
                    if (!safwen.collision_LEFT)
                    {
                        safwen.position.x -= 4;
                        safwen.direction = LEFT;
                        background.posCamera.x-=4;
                        animer_hero(&safwen, WALK);
                    }
                case SDLK_DOWN:
                    if (!safwen.collision_DOWN)
                    {
                        safwen.position.y += 4;
                        background.posCamera.y+= 4;
                    }
                    break;
                case SDLK_UP:
                    if (!safwen.collision_UP)
                    {
                        safwen.position.y -= 4;
                        background.posCamera.y-= 4;
                    }
                    break;

                case SDLK_d:
                    animer_hero(&safwen, PUNCH);
                    break;
                case SDLK_s:
                    animer_hero(&safwen, KICK);
                    break;
                case SDLK_q:
                    animer_hero(&safwen, DAMAGE);
                    break;
                case SDLK_x:
                    animer_hero(&safwen, DIE);
                    break;
                }
                break;
            case SDL_KEYUP:
                if (safwen.state == WALK) //states with interruptable animations
                    safwen.state = IDLE;
                break;
            }
        }
        //scrolling(&background,&safwen);
        afficher_background(&background, screen);
        animer_hero(&safwen, safwen.state);
        deplacer_alea(&enemie);
        animation_entite(&enemie);
        afficher_hero(&safwen, screen);
        afficher_entite(&enemie, screen);
        SDL_Flip(screen);
    }
    free_background(&background);
    free_entite(&enemie);
    free_hero(&safwen);
    SDL_Quit();
    return 0;
}