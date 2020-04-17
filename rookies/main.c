#include "background.h"
#include "entite_secondaire.h"
#include "hero.h"
#include "colision.h"
#include "enigme.h"


typedef enum etat
{
    MENU,
    SETTINGS,
    GAME,
    ENIGME,
    GAME_OVER,
}etat;

void main ()
{
    hero safwen;
    background background;
    entite ennemie;
    enigme enigme_math;

    Etat=MENU;

    SDL_Event event;

    int continuer=1;
    SDL_Surface *ecran;

    initialiser_hero(&safwen, "safwen");
	initialiser_background(&background);
	initialiser_entite(&enemie);

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(SCREEN_WIDTH+320, SCREEN_HEIGHT+120, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_EnableKeyRepeat(2, 2);

    while (continuer)
    {
         if (etat==MENU)
         {
            menu();
         }
         else if (etat==SETTINGS)
         {
             settings();
         }
         else if (etat==GAME)
         {

         }
         else if (etat==ENIGME)
         {
            

            if ()
                etat=GAME;
         }
         else if (etat==GAME_OVER)
         {
             blit gameover image;
             etat=menu;
         }
    }


}

Void main()
// Initialisation des ressources
Initialise_entity
Initialise_Perso
Initialise_back
Initialise_enigma
etat= « Menu »
Tant que (continuer)
Si etat= « menu »
// display + input + update menu
Sinon Si etat= « settings »
// display + input + update settings
Sinon Si etat= « game »
Blit_back
Blit_Perso
Blit_entity
RunTime_Game
// Input &amp; Update
Si événement = touche droite
Perso.direction ← 0
Sinon
Si événement = touche gauche
Perso.direction ←1
Sinon Perso.direction ←-1
Fin si
Fin si
Si évènement=déplacement souris
Deplacer_Perso_Souris
Fin si
Si Perso.direction dans {0,1}
Si Perso.pos.x&lt;(screen-&gt;w/2)
Move_Perso
Sinon
Scrolling
Animate_Perso
Fin Si
MoveAl_Entity
Animate_Entity
Fin si
Si (collision :Bounding Box ou Perfect Pixel)
etat= « enigme »
Fin si

Sinon si etat= « enigme »
reponse=0
Blit_Enigma
Gen_Enigma (statique ou dynamique)
Si (temps écoulé&lt; duré enigme)
Si ( Resolve_Enigma==1) //bonne réponse
reponse=1
Sinon reponse=-1  //mauvaise réponse
Fin si
Sinon reponse=-1 
Fin si
Si( reponse !=0)
Update_ScoreVie
Si ((Perso.nbre_vie == 0) ou (Perso.score &lt;0))
etat= « game over »
Fin Si
etat= « game »
reponse=0
Fin si
Sinon Si etat=  « game over »
Blit_gameover
etat=  « menu »
FIN SI

Flip
Fin tant que
//libération des ressources
Free…
FIN