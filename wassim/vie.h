# ifndef vie_H
# définir  vie_H

# inclut  < SDL / SDL.h >
# include  < SDL / SDL_ttf.h 
# include  < SDL / SDL_image.h 
typedef struct VIE
{
SDL_Surface *coeurs=NULL;
SDL_Rect pos_coeurs;
int vies;
}vie;
struct SCORE
{
SDL_Rect positionText;
char txt [ 20 ];
TTF_Font *police = NULL;
SDL_Color couleurTxt;
int val_score;
}score;

 
