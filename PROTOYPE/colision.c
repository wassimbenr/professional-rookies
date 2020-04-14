#include "colision.h"

SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y)
{
	SDL_Color color;
	Uint32 col = 0;
	char *pPosition = (char *)pSurface->pixels;
	pPosition += (pSurface->pitch * y);
	pPosition += (pSurface->format->BytesPerPixel * x);
	memcpy(&col, pPosition, pSurface->format->BytesPerPixel);
	SDL_GetRGB(col, pSurface->format, &color.r, &color.g, &color.b);
	return (color);
}
void CollisionParfaite(hero *h, background b)
{
	SDL_Color couleur_obstacle = {255, 255, 255};
	int i = 0;
	int collision = 0;
	SDL_Rect pos[8];

	h->collision_UP = -1;
	h->collision_DOWN = -1;
	h->collision_RIGHT = -1;
	h->collision_LEFT = -1;

	pos[0].x = h->position.x;
	pos[0].y = h->position.y;
	pos[1].x = h->position.x + h->sprite.frame.w / 3.9;
	pos[1].y = h->position.y;
	pos[2].x = h->position.x + h->sprite.frame.w / 2;
	pos[2].y = h->position.y;

	pos[3].x = h->position.x;
	pos[3].y = h->position.y + h->sprite.frame.h / 2;
	pos[4].x = h->position.x + h->sprite.frame.w / 2;
	pos[4].y = h->position.y + h->sprite.frame.h / 2;

	pos[5].x = h->position.x;
	pos[5].y = h->position.y + h->sprite.frame.h;
	pos[6].x = h->position.x + h->sprite.frame.w / 3.9;
	pos[6].y = h->position.y + h->sprite.frame.h;
	pos[7].x = h->position.x + h->sprite.frame.w / 2;
	pos[7].y = h->position.y + h->sprite.frame.h;

	for (i = 0; i < 8; i++)
	{
		couleur_obstacle = GetPixel(b.background_mask, pos[i].x, pos[i].y);
		if (couleur_obstacle.r == 0 && couleur_obstacle.g == 0 && couleur_obstacle.b == 0)
		{
			if (i == 0)
			{
				h->collision_LEFT++;
				h->collision_UP++;
			}
			if (i == 1)
			{
				h->collision_UP++;
			}
			if (i == 2)
			{
				h->collision_RIGHT++;
				h->collision_UP++;
			}
			if (i == 3)
			{
				h->collision_LEFT++;
			}
			if (i == 4)
			{
				h->collision_RIGHT++;
			}
			if (i == 5)
			{
				h->collision_LEFT++;
				h->collision_DOWN++;
			}
			if (i == 6)
			{
				h->collision_DOWN++;
			}
			if (i == 7)
			{
				h->collision_RIGHT++;
				h->collision_DOWN++;
			}
		}
	}
	if (h->collision_LEFT <= 0)
		h->collision_LEFT = 0;
	else
		h->collision_LEFT = 1;
	if (h->collision_RIGHT <= 0)
		h->collision_RIGHT = 0;
	else
		h->collision_RIGHT = 1;
	if (h->collision_UP <= 0)
		h->collision_UP = 0;
	else
		h->collision_UP;
	if (h->collision_DOWN <= 0)
		h->collision_DOWN = 0;
	else
		h->collision_DOWN = 1;
}
int Colision_bb(hero *h, entite *e)
{
	if ((h->position.x + h->position.w / 2 < e->position.x) || (h->position.x > e->position.x + e->position.w / 2) || (h->position.y + h->position.h < e->position.y) || (h->position.y > e->position.y + e->position.h))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void attack_entite(entite *e, hero *h)
{
	printf("position: %d\n", e->posMin.x <= h->position.x);
	printf("collision: %d\n", Colision_bb(h, e));
	if (Colision_bb(h, e) && (h->state!=KICK ||h->state!=PUNCH))
	{
		h->state = DAMAGE;
		//e->state_entite=ATTACK_entite;
	}
		
	else if (Colision_bb(h, e) && (h->state!=KICK ||h->state!=PUNCH))
		e->state_entite=DIE_entite;

	if (e->posMin.x <= h->position.x)
	{

		if (e->position.x > h->position.x)
		{
			e->direction_entite = 0;
			e->position.x -= 2;
		}
		else if (e->position.x < h->position.x)
		{
			e->direction_entite = 1;
			e->position.x += 2;
		}
	}
}