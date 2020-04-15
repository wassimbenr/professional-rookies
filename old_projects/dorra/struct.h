typedef struct Gestion
{
// variable pour la fenetre
    SDL_Surface *screen;
    // le variable qui gere la boucle de jeux
    int go;


} Gestion;

typedef struct Map
{
// des surface pour les different images a utilisés
	SDL_Surface *background;
	SDL_Surface *levelCollision;
	SDL_Surface *midleground;
	SDL_Surface *forground;

	/* Coordonnées de début, lorsqu'on doit dessiner la map */
	int startX, startY;



} Map;

typedef struct Hero
{
    //Sprite du héros
	SDL_Surface *sprite;

	/* Coordonnées du héros */
	int x, y;
	/* Largeur, hauteur du sprite */
     int h, w;
	/* Variables utiles pour l'animation */
	int frameNumber, frameTimer;
// variables utiles pour le mouvement
	int etat, direction,jump;

	/* Variables utiles pour la gestion des collisions */
     int onGround, timerMort;
     float dirX, dirY;

} Hero;
