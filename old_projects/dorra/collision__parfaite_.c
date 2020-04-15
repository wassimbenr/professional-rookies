// i won't be explaining this here as it's already done on the previous uploads so if you want a commented one go check the previous files i sent on the mail and you'll find a commented version of this file !

SDL_Color GetPixel(SDL_Surface *Background, int x, int y)
{

    SDL_Color color, white= {0,0,0};
    Uint32 col = 0;
    if (x<8000 && y<600)
    {

        char *pixelPosition = (char*)Background->pixels;
        pixelPosition += (Background->pitch * y);
        pixelPosition += (Background->format->BytesPerPixel * x);
        memcpy(&col, pixelPosition, Background->format->BytesPerPixel);
        SDL_GetRGB(col, Background->format, &color.r, &color.g, &color.b);
        return (color);

    }

    else

        return (white);

}


void mapCollision(Hero *entity)
{

    int i, xg, xd, yg, yd,test;
    SDL_Color PixelToCompare1,PixelToCompare2;
    SDL_LockSurface(map.levelCollision);
    xg = entity->x + entity->dirX;
    xd = entity->x + entity->dirX + entity->w;
    yg = yd = entity->y + entity->h / 2;
    if (xg >0 && xd < MAX_X && yg >= 0 && yd < MAX_Y)
    {

        if (entity->dirX > 0)
        {

            PixelToCompare1= GetPixel(map.levelCollision,xd,yg);
            PixelToCompare1= GetPixel(map.levelCollision,xd,yd);
            test = ((PixelToCompare1.r == 0) && (PixelToCompare1.b == 0) && (PixelToCompare1.g == 0)) && ((PixelToCompare2.r == 0) && (PixelToCompare2.b == 0) && (PixelToCompare2.g == 0));
            if (test)
            {

                entity->x -=   entity->dirX;
                entity->dirX = 0;

            }
        }

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

    xg = (entity->x)+entity->w /2;
    xd = entity->x + entity->w /2 ;
    yg = (entity->y + entity->dirY);
    yd = (entity->y + entity->dirY + entity->h);
    if (xg >= 0 && xd < MAX_X && yg >= 0 && yd < MAX_Y)
    {

        if (entity->dirY > 0)
        {

            PixelToCompare1= GetPixel(map.levelCollision,xd,yd);
            PixelToCompare1= GetPixel(map.levelCollision,xg,yd);
            test = ((PixelToCompare1.r == 0) && (PixelToCompare1.b == 0) && (PixelToCompare1.g == 0)) && ((PixelToCompare2.r == 0) && (PixelToCompare2.b == 0) && (PixelToCompare2.g == 0));
            if (test)
            {

                entity->y = yd;
                entity->y -= entity->h+2;
                entity->dirY = 0;
                entity->onGround = 1;

            }
        }

        else if (entity->dirY < 0)
        {

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

    entity->x += entity->dirX;
    entity->y += entity->dirY;
    if (entity->x < 0)
    {

        entity->x = 0;

    }
    else if (entity->x + entity->w >= MAX_X)
    {

        entity->x = MAX_X - entity->w - 1;

    }
    if (entity->y > MAX_Y)
    {

        entity->timerMort = 18;

    }
    SDL_UnlockSurface(map.levelCollision);
}
