
/* the use of this function depends on you
you might ask why we would use a function to draw a picture while we already have the SDL function SDL_BlitSurface and the answer is easy
this function has two benifits the first one is that we will get rid of all those SDL_Rect that we need to creat to each surface we want to draw and that with just passing the position : x and w to this function and it
will take care of creating an SDL_rect for the image and the drawing it . this is the first advantage

the second advantage which will only be valuable for those who want to work on their project after this year and which is you can just change the library which uses another function to draw images so you can adjust your code with just changing the SDL_BlitSurface on this fucntion and it will be done on every image you want to draw and not going through every draw you did !

 */

void drawImage(SDL_Surface *image, int x, int y)
{

    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = image->w;
    dest.h = image->h;

    SDL_BlitSurface(image, NULL, jeu.screen, &dest);

}
