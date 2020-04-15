
// this is an example of how you can do a scrolling and this is one will put the character on the middle of the background most of the time
//how this works ? so we will draw our map depending on the map.startX which wil tell us where we will start drawing our map
// so by default it will be drawn at a place where we will most of the time see our character on the middle of the screen so it will take care the character pos and substract half of the screen width so we start drawing from there
// but if the character didn't reach the first half of the screen we will start drawing from 0 so we don't have empty space with no background in there
// and the same for the last part of the map if we reach the last part of the map we don't want that bad looking part showing off so we will fix our map at it's length - the screen length 
void centerScrollingOnPlayer(void)
{

    map.startX = player.x - (SCREEN_WIDTH / 2);
    if (map.startX < 0)
    {

        map.startX = 0;

    }
    else if (map.startX + SCREEN_WIDTH >= MAX_X)
    {

        map.startX = MAX_X - SCREEN_WIDTH;

    }
}
