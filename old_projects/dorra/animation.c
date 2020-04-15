
/*for animation those function can be used for any other animation with just some tweeks.
 you just need a well organized sprite sheet with the same with between each frame so you don't parts of the next frame on the current one

for the height from a personal experience it's better to have sprite sheets for the same entity with the same height so you don't have issues with the collision and for a better view over all
explaining how things work here :

the frametimer controls the time between each frame while the animation is going

the framenumber will control which frame should be displayed on each lap of the game loop

so the first function will take care of these two variables so the next functions know wich frame it should draw at our screen .

for the next function it will have two variables to take care of , which are SDL_Rects : dest and src , dest for destination and src for source!

SDL_Rect dest : this one will take care of where we're going to draw our frame so it all depends on how you move your character and you background (middle ground depends on how you're taking care of your map drawing)
here i am having both the position of my character and map always chaging of course it depends on the position of the character and other stuff but basically that little substruction there will draw either the character
 on the center of weidth of the screen or on the first half if the character didn't reach the first half of the screen widht or the last half of the screen if he reaches the last half of the map !
 it's better explained on the scrolling file that i sent before !

 now moving the SDL_rect src : this one will take the one frame that it needs to draw depending on the frame number we get from the first function so for example if the frame number is 0 the src.x = 0*player.w (which is the width of a single frame)=0
 so we will start cutting from x = 0 till we reach player.w so like that we will cut the first frame and you can apply that for any frame and the length of the sprite sheet here doesn't matter it will work on any length of a sprite sheet you load

 later we will give the hand to our dear function SDL_BlitSurface which will take care of drawing that frame on our screen with those two variable As parameters !  
 */
void drawanimatedplayer(void)
{

    if (player.frameTimer <= 0)
    {

        player.frameTimer = TIME_BETWEEN_2_FRAMES;
        player.frameNumber++;
        if(player.frameNumber >= player.sprite->w / player.w)
        {

            player.frameNumber = 0;

        }
    }

    else
    {

        player.frameTimer--;

    }

    drawplayer();

}


void drawplayer()
{

    SDL_Rect dest;

    dest.x = player.x - map.startX;
    dest.y = player.y - map.startY;
    dest.w = player.w;
    dest.h = player.h;

    SDL_Rect src;

    src.x = player.frameNumber * player.w;
    src.y = 0;
    src.w = player.w;
    src.h = player.h;

    SDL_BlitSurface(player.sprite, &src, jeu.screen, &dest);

}
