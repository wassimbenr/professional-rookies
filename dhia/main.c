#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
int main(void)
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
