#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"


/* Taille de la fenêtre / résolution en plein écran */
#define SCREEN_WIDTH 640// 640
#define SCREEN_HEIGHT 480//480

/* Valeur RGB pour la transparence (canal alpha) */
#define TRANS_R 255
#define TRANS_G 0
#define TRANS_B 255

#define JUMP_HEIGHT 140
#define GROUND_LEVEL 465
#define VERTICAL_MOVEMENT 7