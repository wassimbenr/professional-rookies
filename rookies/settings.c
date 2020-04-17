#include "settings.h"
void settings(SDL_Surface *screen, int *mute, int *fullscreen, int *volume, etat *etat)
{

	SDL_Surface *background;
	SDL_Rect pos_backg;
	SDL_Event event;
	SDL_Surface *full = NULL, *mute_image = NULL, *back = NULL, *screen_mode = NULL, *sound = NULL, *volume_bar = NULL, *plus = NULL, *moins = NULL;
	SDL_Rect pos_mute, pos_full, pos_back, pos_sound, pos_screen, pos_vol_bar, pos_plus, pos_moins;
	Mix_Chunk *click;
	int  f = 0, m = 0, b = 0;
	TTF_Font *police = NULL;
	police = TTF_OpenFont("./img/menu/8bit.ttf", 15);
	SDL_Color couleurBlanche = {255, 255, 255};
	SDL_Color couleurRouge = {255, 0, 0};

	plus = TTF_RenderText_Blended(police, "+", couleurBlanche);
	moins = TTF_RenderText_Blended(police, "-", couleurBlanche);

	pos_backg.x = 0;
	pos_backg.y = 0;
	pos_sound.x = 200;
	pos_sound.y = 219;
	pos_mute.x = 280;
	pos_mute.y = pos_sound.y;
	pos_screen.x = 200;
	pos_screen.y = 260;
	pos_full.x = 320;
	pos_full.y = pos_screen.y - 10;
	pos_back.x = 200;
	pos_back.y = 300;
	pos_vol_bar.x = 340;
	pos_vol_bar.y = 212;
	pos_plus.x = 405;
	pos_plus.y = 220;
	pos_moins.x = 425;
	pos_moins.y = 220;
	switch (*volume)
	{
	case 0:
		*mute = 1;
		volume_bar = NULL;
		break;
	case 24:
		volume_bar = IMG_Load("./img/menu/1_bar.png");
		break;
	case 48:
		volume_bar = IMG_Load("./img/menu/2_bars.png");
		break;
	case 72:
		volume_bar = IMG_Load("./img/menu/3_bars.png");
		break;
	case 96:
		volume_bar = IMG_Load("./img/menu/4_bars.png");
		break;
	case 120:
		volume_bar = IMG_Load("./img/menu/5_bars.png");
		break;
	}
	sound = IMG_Load("./img/menu/sound.png");
	if (*mute == 0)
		mute_image = IMG_Load("./img/menu/mute.png");
	else
		mute_image = IMG_Load("./img/menu/mute_tick.png");
	screen_mode = IMG_Load("./img/menu/screen.png");
	if (*fullscreen == 0)
		full = IMG_Load("./img/menu/full.png");
	else
		full = IMG_Load("./img/menu/full_tick.png");
	back = IMG_Load("./img/menu/back.png");

	click = Mix_LoadWAV("./img/menu/click.wav");

	background = SDL_LoadBMP("./img/menu/ZEUUN.bmp");

	
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					(*etat)=MENU;
					break;
				case SDLK_LEFT:
					if (m == 1)
					{
						(*volume) -= 24;
						switch (*volume)
						{
						case 0:
							(*mute )= 1;
							volume_bar = NULL;
							break;
						case 24:
							volume_bar = IMG_Load("./img/menu/1_bar.png");
							break;
						case 48:
							volume_bar = IMG_Load("./img/menu/2_bars.png");
							break;
						case 72:
							volume_bar = IMG_Load("./img/menu/3_bars.png");
							break;
						case 96:
							volume_bar = IMG_Load("./img/menu/4_bars.png");
							break;
						case 120:
							volume_bar = IMG_Load("./img/menu/5_bars.png");
							break;
						}
					}
					break;
				case SDLK_RIGHT:
					if (m == 1)
					{
						(*volume) += 24;
						(*mute) = 0;
						switch (*volume)
						{
						case 0:
							(*mute) = 1;
							volume_bar = NULL;
							break;
						case 24:
							volume_bar = IMG_Load("./img/menu/1_bar.png");
							break;
						case 48:
							volume_bar = IMG_Load("./img/menu/2_bars.png");
							break;
						case 72:
							volume_bar = IMG_Load("./img/menu/3_bars.png");
							break;
						case 96:
							volume_bar = IMG_Load("./img/menu/4_bars.png");
							break;
						case 120:
							volume_bar = IMG_Load("./img/menu/5_bars.png");
							break;
						}
					}
					break;
				case SDLK_RETURN:
					if (b == 1)
					{
						Mix_PlayChannel(-1, click, 0);
						(*etat)=MENU;
					}
					if (f == 1 && *fullscreen == 0)
					{
						Mix_PlayChannel(-1, click, 0);
						screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
						full = IMG_Load("./img/menu/full_active_tick.png");
						//SDL_Flip(screen);
						(*fullscreen) = 1;
					}
					else if (f == 1 && *fullscreen == 1)
					{
						Mix_PlayChannel(-1, click, 0);
						screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
						full = IMG_Load("./img/menu/full_active.png");
						//SDL_Flip(screen);
						(*fullscreen) = 0;
					}
					if (m == 1 && *mute == 0)
					{
						Mix_PauseMusic();
						mute_image = IMG_Load("./img/menu/mute_active_tick.png");
						*mute = 1;
					}
					else if (m == 1 && *mute == 1)
					{
						Mix_ResumeMusic();
						mute_image = IMG_Load("./img/menu/mute_active.png");
						*mute = 0;
					}
					break;
				case SDLK_DOWN:
					if (m == 0 && f == 0 && b == 0)
					{

						Mix_PlayChannel(-1, click, 0);
						if (*mute == 0)
							mute_image = IMG_Load("./img/menu/mute_active.png");
						else
							mute_image = IMG_Load("./img/menu/mute_active_tick.png");
						if (*fullscreen == 0)
							full = IMG_Load("./img/menu/full.png");
						else
							full = IMG_Load("./img/menu/full_tick.png");
						m = 1;
						f = 0;
						b = 0;
					}
					else if (m == 1 && f == 0 && b == 0)
					{
						Mix_PlayChannel(-1, click, 0);
						if (*mute == 0)
							mute_image = IMG_Load("./img/menu/mute.png");
						else
							mute_image = IMG_Load("./img/menu/mute_tick.png");
						if (*fullscreen == 0)
							full = IMG_Load("./img/menu/full_active.png");
						else
							full = IMG_Load("./img/menu/full_active_tick.png");
						m = 0;
						f = 1;
						b = 0;
					}
					else if (m == 0 && f == 1 && b == 0)
					{
						Mix_PlayChannel(-1, click, 0);
						if (*fullscreen == 0)
							full = IMG_Load("./img/menu/full.png");
						else
							full = IMG_Load("./img/menu/full_tick.png");
						if (*mute == 0)
							mute_image = IMG_Load("./img/menu/mute.png");
						else
							mute_image = IMG_Load("./img/menu/mute_tick.png");
						back = IMG_Load("./img/menu/back_active.png");
						m = 0;
						f = 0;
						b = 1;
					}
					break;
				case SDLK_UP:
					if (m == 0 && f == 0 && b == 1)
					{
						Mix_PlayChannel(-1, click, 0);
						if (*fullscreen == 0)
							full = IMG_Load("./img/menu/full_active.png");
						else
							full = IMG_Load("./img/menu/full_active_tick.png");
						if (*mute == 0)
							mute_image = IMG_Load("./img/menu/mute.png");
						else
							mute_image = IMG_Load("./img/menu/mute_tick.png");
						back = IMG_Load("./img/menu/back.png");
						m = 0;
						f = 1;
						b = 0;
					}
					else if (m == 0 && f == 1 && b == 0)
					{
						Mix_PlayChannel(-1, click, 0);
						if (*fullscreen == 0)
							full = IMG_Load("./img/menu/full.png");
						else
							full = IMG_Load("./img/menu/full_tick.png");
						if (*mute == 0)
							mute_image = IMG_Load("./img/menu/mute_active.png");
						else
							mute_image = IMG_Load("./img/menu/mute_active_tick.png");
						back = IMG_Load("./img/menu/back.png");
						m = 1;
						f = 0;
						b = 0;
					}
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				if (event.motion.x > pos_plus.x && event.motion.x < pos_plus.x + plus->w && event.motion.y > pos_plus.y && event.motion.y < pos_plus.y + plus->h)
				{
					plus = TTF_RenderText_Blended(police, "+", couleurRouge);
					if (*mute == 0)
						mute_image = IMG_Load("./img/menu/mute.png");
					else
						mute_image = IMG_Load("./img/menu/mute_tick.png");
					if (*fullscreen == 0)
						full = IMG_Load("./img/menu/full.png");
					else
						full = IMG_Load("./img/menu/full_tick.png");
					moins = TTF_RenderText_Blended(police, "-", couleurBlanche);
				}
				else if (event.motion.x > pos_moins.x && event.motion.x < pos_moins.x + moins->w && event.motion.y > pos_moins.y && event.motion.y < pos_moins.y + moins->h)
				{
					moins = TTF_RenderText_Blended(police, "-", couleurRouge);
					if (*mute == 0)
						mute_image = IMG_Load("./img/menu/mute.png");
					else
						mute_image = IMG_Load("./img/menu/mute_tick.png");
					if (*fullscreen == 0)
						full = IMG_Load("./img/menu/full.png");
					else
						full = IMG_Load("./img/menu/full_tick.png");
					plus = TTF_RenderText_Blended(police, "+", couleurBlanche);
				}
				else if (event.motion.x > pos_mute.x && event.motion.x < pos_mute.x + mute_image->w && event.motion.y > pos_mute.y && event.motion.y < pos_mute.y + mute_image->h)
				{
					if (*mute == 0)
						mute_image = IMG_Load("./img/menu/mute_active.png");
					else
						mute_image = IMG_Load("./img/menu/mute_active_tick.png");
					if (*fullscreen == 0)
						full = IMG_Load("./img/menu/full.png");
					else
						full = IMG_Load("./img/menu/full_tick.png");
					back = IMG_Load("./img/menu/back.png");
					plus = TTF_RenderText_Blended(police, "+", couleurBlanche);
					moins = TTF_RenderText_Blended(police, "-", couleurBlanche);
				}
				else if (event.motion.x > pos_full.x && event.motion.x < pos_full.x + full->w && event.motion.y > pos_full.y && event.motion.y < pos_full.y + full->h)
				{
					if (*fullscreen == 0)
						full = IMG_Load("./img/menu/full_active.png");
					else
						full = IMG_Load("./img/menu/full_active_tick.png");
					if (*mute == 0)
						mute_image = IMG_Load("./img/menu/mute.png");
					else
						mute_image = IMG_Load("./img/menu/mute_tick.png");
					back = IMG_Load("./img/menu/back.png");
					plus = TTF_RenderText_Blended(police, "+", couleurBlanche);
					moins = TTF_RenderText_Blended(police, "-", couleurBlanche);
				}
				else if (event.motion.x > pos_back.x && event.motion.x < pos_back.x + back->w && event.motion.y > pos_back.y && event.motion.y < pos_back.y + back->h)
				{
					if (*mute == 0)
						mute_image = IMG_Load("./img/menu/mute.png");
					else
						mute_image = IMG_Load("./img/menu/mute_tick.png");
					if (*fullscreen == 0)
						full = IMG_Load("./img/menu/full.png");
					else
						full = IMG_Load("./img/menu/full_tick.png");
					back = IMG_Load("./img/menu/back_active.png");
					plus = TTF_RenderText_Blended(police, "+", couleurBlanche);
					moins = TTF_RenderText_Blended(police, "-", couleurBlanche);
				}
				else
				{
					if (*mute == 0)
						mute_image = IMG_Load("./img/menu/mute.png");
					else
						mute_image = IMG_Load("./img/menu/mute_tick.png");
					if (*fullscreen == 0)
						full = IMG_Load("./img/menu/full.png");
					else
						full = IMG_Load("./img/menu/full_tick.png");
					back = IMG_Load("./img/menu/back.png");
					plus = TTF_RenderText_Blended(police, "+", couleurBlanche);
					moins = TTF_RenderText_Blended(police, "-", couleurBlanche);
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (event.motion.x > pos_plus.x && event.motion.x < pos_plus.x + plus->w && event.motion.y > pos_plus.y && event.motion.y < pos_plus.y + plus->h)
					{
						(*volume) += 24;
						(*mute) = 0;
						switch (*volume)
						{
						case 0:
							(*mute )= 1;
							volume_bar = NULL;
							break;
						case 24:
							volume_bar = IMG_Load("./img/menu/1_bar.png");
							break;
						case 48:
							volume_bar = IMG_Load("./img/menu/2_bars.png");
							break;
						case 72:
							volume_bar = IMG_Load("./img/menu/3_bars.png");
							break;
						case 96:
							volume_bar = IMG_Load("./img/menu/4_bars.png");
							break;
						case 120:
							volume_bar = IMG_Load("./img/menu/5_bars.png");
							break;
						}
					}
					else if (event.motion.x > pos_moins.x && event.motion.x < pos_moins.x + moins->w && event.motion.y > pos_moins.y && event.motion.y < pos_moins.y + moins->h)
					{

						(*volume) -= 24;
						switch (*volume)
						{
						case 0:
							(*mute) = 1;
							volume_bar = NULL;
							break;
						case 24:
							volume_bar = IMG_Load("./img/menu/1_bar.png");
							break;
						case 48:
							volume_bar = IMG_Load("./img/menu/2_bars.png");
							break;
						case 72:
							volume_bar = IMG_Load("./img/menu/3_bars.png");
							break;
						case 96:
							volume_bar = IMG_Load("./img/menu/4_bars.png");
							break;
						case 120:
							volume_bar = IMG_Load("./img/menu/5_bars.png");
							break;
						}
					}
					else if (event.motion.x > pos_mute.x && event.motion.x < pos_mute.x + mute_image->w && event.motion.y > pos_mute.y && event.motion.y < pos_mute.y + mute_image->h)
					{
						Mix_PlayChannel(-1, click, 0);
						if (*mute == 0)
						{
							Mix_PauseMusic();
							mute_image = IMG_Load("./img/menu/mute_active_tick.png");
							(*mute) = 1;
						}
						else
						{
							Mix_ResumeMusic();
							mute_image = IMG_Load("./img/menu/mute_active.png");
							(*mute) = 0;
						}
					}
					else if (event.motion.x > pos_full.x && event.motion.x < pos_full.x + full->w && event.motion.y > pos_full.y && event.motion.y < pos_full.y + full->h)
					{
						Mix_PlayChannel(-1, click, 0);
						if (*fullscreen == 0)
						{
							screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
							full = IMG_Load("./img/menu/full_active_tick.png");
							//SDL_Flip(screen);
							(*fullscreen) = 1;
						}
						else
						{
							screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
							full = IMG_Load("./img/menu/full_active.png");
							//SDL_Flip(screen);
							(*fullscreen )= 0;
						}
					}
					else if (event.motion.x > pos_back.x && event.motion.x < pos_back.x + back->w && event.motion.y > pos_back.y && event.motion.y < pos_back.y + back->h)
					{
						Mix_PlayChannel(-1, click, 0);
						(*etat) = MENU;
					}
				}
				break;
			}
		}
		SDL_BlitSurface(background, NULL, screen, &pos_backg);
		SDL_BlitSurface(screen_mode, NULL, screen, &pos_screen);
		SDL_BlitSurface(full, NULL, screen, &pos_full);
		SDL_BlitSurface(sound, NULL, screen, &pos_sound);
		SDL_BlitSurface(mute_image, NULL, screen, &pos_mute);
		SDL_BlitSurface(back, NULL, screen, &pos_back);
		SDL_BlitSurface(volume_bar, NULL, screen, &pos_vol_bar);
		SDL_BlitSurface(plus, NULL, screen, &pos_plus);
		SDL_BlitSurface(moins, NULL, screen, &pos_moins);
		Mix_VolumeMusic(*volume);
		//SDL_Flip(screen);
	
	//SDL_FreeSurface(background);
}
