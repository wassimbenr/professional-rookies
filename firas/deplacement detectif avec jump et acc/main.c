#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"

int main(int argc, char *argv[])
{

	SDL_Surface *ecran = NULL, *imageDeFond = NULL, *detective = NULL;
	Mix_Music *music;
	SDL_Event event;
	int continuer = 1;
	int gravity = 3;
	int tanguiza = 0;
	int timeStepMs = 32;
	int timeLastMs, timeAccumulatedMs, timeDeltaMs, timeCurrentMs = 0;
	int test;
	float accel = 0;

	SDL_Rect positionecran, positionDetect;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		printf("%s", Mix_GetError());
	}
	music = Mix_LoadMUS("music.mp3");
	Mix_PlayMusic(music, -1);

	positionecran.x = 0;

	positionecran.y = 0;

	positionDetect.x = 0;

	positionDetect.y = 220;

	SDL_Init(SDL_INIT_VIDEO);

	ecran = SDL_SetVideoMode(600, 400, 32, SDL_HWSURFACE);

	SDL_WM_SetCaption("Chargement d'images en SDL", NULL);

	imageDeFond = IMG_Load("background.bmp");

	detective = IMG_Load("detective.png");
	SDL_SetColorKey(detective, SDL_SRCCOLORKEY, SDL_MapRGB(detective->format, 255, 255, 255));

	SDL_EnableKeyRepeat(2, 2);
	while (continuer)
	{
		timeLastMs = timeCurrentMs;
		timeCurrentMs = SDL_GetTicks();
		timeDeltaMs = timeCurrentMs - timeLastMs;
		timeAccumulatedMs += timeDeltaMs;

		while (timeAccumulatedMs >= timeStepMs)
		{
			test = 0;
			Uint8 *keystates = SDL_GetKeyState(NULL);
			if (keystates[SDLK_UP] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)))
			{

				if (positionDetect.y > 150 && tanguiza == 0)
				{
					positionDetect.y -= 7;
				}
				else if (positionDetect.y == 150 || (tanguiza == 1 && positionDetect.y < 220))
				{
					positionDetect.y += 7;
					tanguiza = 1;
					test = 1;
				}
			}
			if (keystates[SDLK_RIGHT] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && (event.motion.x > positionDetect.x)))
			{
				if (positionDetect.y < 220)
				{
					positionDetect.x += 4 + accel;
					if (positionDetect.x >= 600)
						positionDetect.x = 0;
				}
				else
				{
					positionDetect.x += 5 + accel;
					if (accel < 5)
						accel += 0.1;
					if (positionDetect.x >= 600)
						positionDetect.x = 0;
				}
			}
			if (keystates[SDLK_LEFT] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && (event.motion.x < positionDetect.x)))
			{
				if (positionDetect.y < 220)
				{
					positionDetect.x -= 4 + accel;
					if (accel < 5)
						accel += 0.1;
					if (positionDetect.x < 0)
						positionDetect.x = 0;
				}
				else
				{
					positionDetect.x -= 5 + accel;
					if (accel < 5)
						accel += 0.1;
					if (positionDetect.x < 0)
						positionDetect.x = 0;
				}
			}
			if (!test && tanguiza == 1 && positionDetect.y < 220)
				positionDetect.y += 7;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_RIGHT)
					{
						if ((positionDetect.y < 220) && (!test))
						{
							positionDetect.y += 7;
							tanguiza = 1;
						}
						else if (positionDetect.y == 220)
							tanguiza = 0;
						break;
					}
					if (event.button.button == SDL_BUTTON_LEFT)
						accel = 0;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
						continuer = 0;
					break;
				case SDL_KEYUP:
					if (event.key.keysym.sym == SDLK_UP)
					{
						if ((positionDetect.y < 220) && (!test))
						{
							positionDetect.y += 7;
							tanguiza = 1;
						}
						else if (positionDetect.y == 220)
							tanguiza = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_RIGHT || (event.key.keysym.sym == SDLK_LEFT))
						accel = 0;
					break;
				}
			}
			timeAccumulatedMs -= timeStepMs;
		}
		SDL_BlitSurface(imageDeFond, NULL, ecran, &positionecran);
		SDL_BlitSurface(detective, NULL, ecran, &positionDetect);
		SDL_Flip(ecran);
	}

	SDL_FreeSurface(imageDeFond);
	SDL_FreeSurface(detective);
	Mix_FreeMusic(music);

	SDL_Quit();

	return EXIT_SUCCESS;
}
