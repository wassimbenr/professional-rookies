#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"

#include "hero.h"
#include "background.h"
#include "defs.h"
#include "main_functions.h" 

int main(int argc, char *argv[])
{
	hero safwen;
	background background;

	SDL_Surface *ecran = NULL;

	SDL_Event event;

	initialiser_hero(&safwen);
	initialiser_background(&background);

	int continuer = 1;
	int gravity = 3;
	int tanguiza = 0;
	int timeStepMs = 20;
	int timeLastMs, timeAccumulatedMs, timeDeltaMs, timeCurrentMs = 0;
	int test;
	float accel = 0;

	SDL_Rect positionecran, positionDetect;

	positionDetect.x = safwen.position.x;
	positionDetect.y = safwen.position.y;

	

	SDL_Init(SDL_INIT_VIDEO);

	ecran = SDL_SetVideoMode(background.image->w, background.image->h, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

	SDL_EnableKeyRepeat(2, 2);

	while (continuer)
	{
		safwen.position.x = positionDetect.x;
		safwen.position.y = positionDetect.y;

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

				if (positionDetect.y > GROUND_LEVEL-JUMP_HEIGHT && tanguiza == 0)
				{
					animer_hero(&safwen,JUMP);
					positionDetect.y -= 7;
				}
				else if (positionDetect.y == GROUND_LEVEL-JUMP_HEIGHT || (tanguiza == 1 && CollisionParfaite(background.background_mask,safwen.sprite.frame,safwen.position)!=-2))
				{
					animer_hero(&safwen,JUMP);
					positionDetect.y += 7;
					tanguiza = 1;
					test = 1;
				}
			}
			if (keystates[SDLK_RIGHT] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && (event.motion.x > positionDetect.x)))
			{
				if (CollisionParfaite(background.background_mask,safwen.sprite.frame,safwen.position)!=-2)
				{
					positionDetect.x += 4 + accel;
					if (positionDetect.x >= background.image->w-safwen.sprite.frame.w)
						positionDetect.x = background.image->w-safwen.sprite.frame.w;
				}
				else
				{
					positionDetect.x += 5 + accel;
					safwen.direction = RIGHT;
					animer_hero(&safwen, WALK);
					if (accel < 5)
						accel += 0.1;
					if (positionDetect.x >= background.image->w-safwen.sprite.frame.w)
						positionDetect.x = background.image->w-safwen.sprite.frame.w;
				}
			}
			if (keystates[SDLK_LEFT] || (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && (event.motion.x < positionDetect.x)))
			{
				if (CollisionParfaite(background.background_mask,safwen.sprite.frame,safwen.position)!=-2)
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
					safwen.direction = LEFT;
					animer_hero(&safwen, WALK);
					if (accel < 5)
						accel += 0.1;
					if (positionDetect.x < 0)
						positionDetect.x = 0;
				}
			}
			if (!test && tanguiza == 1 && CollisionParfaite(background.background_mask,safwen.sprite.frame,safwen.position)!=-2)
				positionDetect.y += 7;
			else if (CollisionParfaite(background.background_mask,safwen.sprite.frame,safwen.position)==-2)
				tanguiza = 0;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_RIGHT)
					{
						if ((CollisionParfaite(background.background_mask,safwen.sprite.frame,safwen.position)!=-2) && (!test))
						{
							positionDetect.y += 7;
							tanguiza = 1;
						}
						else if (CollisionParfaite(background.background_mask,safwen.sprite.frame,safwen.position)==-2)
							tanguiza = 0;
						break;
					}
					if (event.button.button == SDL_BUTTON_LEFT)
						accel = 0;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							continuer=0;
							break;
						case SDLK_d:
							animer_hero(&safwen,PUNCH);
							break;
						case SDLK_s:
							animer_hero(&safwen,KICK);
							break;
						case SDLK_q:
							animer_hero(&safwen,HIT);
							break;
						case SDLK_x:
							animer_hero(&safwen,DIE);
							break;
					}
					break;
				case SDL_KEYUP:
					if (event.key.keysym.sym == SDLK_UP)
					{
						if ((CollisionParfaite(background.background_mask,safwen.sprite.frame,safwen.position)!=-2) && (!test))
						{
							positionDetect.y += 7;
							tanguiza = 1;
						}
						else if (CollisionParfaite(background.background_mask,safwen.sprite.frame,safwen.position)==-2)
							tanguiza = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_RIGHT || (event.key.keysym.sym == SDLK_LEFT))
					{
						accel = 0;
					}
					if (safwen.movement==WALK)
						safwen.movement=IDLE;
					break;
				}
			}
			timeAccumulatedMs -= timeStepMs;
			/*printf("%d\n",CollisionParfaite(background.background_mask,safwen.sprite.frame,safwen.position));
			if  (CollisionParfaite(background.background_mask,safwen.sprite.frame,safwen.position)!=-2)
				positionDetect.y+=1;
			else
			{
				printf("%d %d\n",safwen.position.y,positionDetect.y);
				continuer=0;
			}*/
			
		}
		animer_hero(&safwen,safwen.movement);
		afficher_background(&background, ecran);
		afficher_hero(&safwen, ecran);
		SDL_Flip(ecran);
	}

	free_background(&background);
	free_hero(&safwen);

	SDL_Quit();

	return EXIT_SUCCESS;
}
