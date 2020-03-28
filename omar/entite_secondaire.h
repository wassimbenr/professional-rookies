# ifndef entite_secondaire.h
# définir entite_secondaire.h

# inclut  < SDL / SDL.h >
# inclure  " SDL / SDL_image.h "

typedef struct FRAME
{
	int i;	
	int j;	
}FRAME;




struct Entite
{ 
        SDL_Rect posMax;
        SDL_Rect posMin;
        SDL_Surface * sprite_secondaire;
	SDL_Rect positionEntite;
        SDL_Rect posScreen ;
        SDL_Rect posSprite ;
	int Direction;
	
};
typedef  struct Entite entite;
void init_entite(entite *E);
void deplacer_alea(entite *E);
void animation (entite *E);
void display_ennemi(Ennemi E, SDL_Surface* screen);
void freeEnnemi(entite *E);










#endif
