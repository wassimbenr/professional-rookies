
#include "map.h"

SDL_Color GetPixel(SDL_Surface *Background, int x, int y)
{
        SDL_Color color, white={0,0,0};
        Uint32 col = 0;
        //Determine position

        if (x<8000 && y<600)
        {
                char *pixelPosition = (char*)Background->pixels;
                //Offset by Y
                pixelPosition += (Background->pitch * y);
                //Offset by X
                pixelPosition += (Background->format->BytesPerPixel * x);
                //Copy pixel data
                memcpy(&col, pixelPosition, Background->format->BytesPerPixel);
                //Convert to color
                SDL_GetRGB(col, Background->format, &color.r, &color.g, &color.b);

                return (color);
        }
        else
                return (white);

}

void mapCollision(Hero *entity)
{
    // x pour les positions x , y pour les positions y , g pour dire gauche , d pour dire droite
        int i, xg, xd, yg, yd,test;
        // les pixer qu'on va  avoir sur eux nos test
        SDL_Color PixelToCompare1,PixelToCompare2;

        // on lock la surface de collusion pour tester les pixe

        SDL_LockSurface(map.levelCollision);



        //On va calculer ici les coins de notre sprite à gauche et à droite pour voir quelle pixel on touche

        xg = entity->x + entity->dirX;
        xd = entity->x + entity->dirX + entity->w;

      //le meme pour les y

        yg = yd = entity->y + entity->h / 2;



        //De là, on va tester les mouvements initiés dans updatePlayer grâce aux vecteurs
        //dirX et dirY, tout en testant avant qu'on se situe bien dans les limites de l'écran.

        if (xg >0 && xd < MAX_X && yg >= 0 && yd < MAX_Y)
        {
                //Si on a un mouvement à droite

                if (entity->dirX > 0)
                {

                        //On vérifie si les pixels recouvertes sont noir
                        PixelToCompare1= GetPixel(map.levelCollision,xd,yg);
                        PixelToCompare1= GetPixel(map.levelCollision,xd,yd);
                        test = ((PixelToCompare1.r == 0) && (PixelToCompare1.b == 0) && (PixelToCompare1.g == 0)) && ((PixelToCompare2.r == 0) && (PixelToCompare2.b == 0) && (PixelToCompare2.g == 0));
                        if (test)
                        {
                                // Si c'est le cas, on place le joueur aussi près que possible
                                // de ces tiles, en mettant à jour ses coordonnées. Enfin, on réinitialise
                                //son vecteur déplacement (dirX).

                                entity->x -=   entity->dirX;



                                entity->dirX = 0;

                        }

                }

                //Même chose à gauche

                else if (entity->dirX < 0)
                {
                        PixelToCompare1= GetPixel(map.levelCollision,xg,yg);
                        PixelToCompare1= GetPixel(map.levelCollision,xg,yd);
                        test = ((PixelToCompare1.r == 0) && (PixelToCompare1.b == 0) && (PixelToCompare1.g == 0)) && ((PixelToCompare2.r == 0) && (PixelToCompare2.b == 0) && (PixelToCompare2.g == 0));

                        if (test)
                        {

                                entity->x -= entity->dirX;

                                entity->dirX = 0;
                        }


                }

        }








        xg = (entity->x);
        xd = entity->x + entity->w /2;

        yg = (entity->y + entity->dirY);
        yd = (entity->y + entity->dirY + entity->h);

        if (xg >= 0 && xd < MAX_X && yg >= 0 && yd < MAX_Y)
        {
                if (entity->dirY > 0)
                {
                        PixelToCompare1= GetPixel(map.levelCollision,xd,yd);
                        PixelToCompare1= GetPixel(map.levelCollision,xg,yd);
                        test = ((PixelToCompare1.r == 0) && (PixelToCompare1.b == 0) && (PixelToCompare1.g == 0)) && ((PixelToCompare2.r == 0) && (PixelToCompare2.b == 0) && (PixelToCompare2.g == 0));

                        /* Déplacement en bas */
                        if (test)
                        {
                                //Si la pixel est noir, on y colle le joueur et
                                //on le déclare sur le sol (onGround).
                                entity->y = yd;
                                entity->y -= entity->h+0.5;

                                entity->dirY = 0;

                                entity->onGround = 1;
                        }

                }

                else if (entity->dirY < 0)
                {

                        /* Déplacement vers le haut */

                        PixelToCompare1= GetPixel(map.levelCollision,xd,yg);
                        PixelToCompare1= GetPixel(map.levelCollision,xg,yg);
                        test = ((PixelToCompare1.r == 0) && (PixelToCompare1.b == 0) && (PixelToCompare1.g == 0)) &&((PixelToCompare2.r == 0) && (PixelToCompare2.b == 0) && (PixelToCompare2.g == 0));

                        if (test)
                        {

                                entity->y = (yg + 1);

                                entity->dirY = 0;


                        }

                }
        }



        /* Maintenant, on applique les vecteurs de mouvement */
        entity->x += entity->dirX;
        entity->y += entity->dirY;

        //Et on contraint son déplacement aux limites de l'écran, comme avant.
        if (entity->x < 0)
        {
                entity->x = 0;
        }

        else if (entity->x + entity->w >= MAX_X)
        {
                entity->x = MAX_X - entity->w - 1;
        }

        //Maintenant, s'il sort de l'écran par le bas (chute dans un trou sans fond), on lance le timer
        //qui gère sa mort et sa réinitialisation
        if (entity->y > MAX_Y)
        {
                entity->timerMort = 60;
        }
        // et enfin on unlock la surface de collision
       SDL_UnlockSurface(map.levelCollision);
}

void centerScrollingOnPlayer(void)
{
// ici on va bliter la background tout depant de l'emplacement de notre charactere (en cas ou on a un seul charactere jouable au meme temps) donc la map va prendre la position de notre hero - la largeur de notre ecran pour qu'elle soit centrer
        map.startX = player.x - (SCREEN_WIDTH / 2);

// Maintenant si le character est juste au debut de la map on veux pas avoir une espace vide donc on fixe la map a 0 jusqu'a il arrive a une position x = SCREEN_WIDTH/2
        if (map.startX < 0)
        {
                map.startX = 0;
        }

// et s'il arrive al la derniere partie de la map on veux pas avoir une partie vide alors donc on blite juste la largeur de notre map - le largeur de notre ecran et on la fix !
        else if (map.startX + SCREEN_WIDTH >= MAX_X)
        {
                map.startX = MAX_X - SCREEN_WIDTH;
        }


}
