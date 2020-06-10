#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "hero.h"
#define NB_TEST 12
#define NB_WORD 10
#define MAX_LEN 12
#define DICTIONARY "QuizWord.txt"


int enigme_pendu(SDL_Surface *screen, hero *h);