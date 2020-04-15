/*
this is a simple function that will detect a collision between any two rectangles , it can mainly used for two moving objectes ,
how it works is really simple if the two rectangles collide from any side of the 4 sides the functions return 1 otherwise it will return 0 , so this functions can be used to check collision with enemies ,moving platforms,items that needs to be collected or stuff like that 
*/
bool collision(Sprite *rect1,Sprite *rect2)
{
        if(rect1->y >= rect2->y + rect2->h)
                return 0;
        if(rect1->x >= rect2->x + rect2->w)
                return 0;
        if(rect1->y + rect1->h <= rect2->y)
                return 0;
        if(rect1->x + rect1->w <= rect2->x)
                return 0;
        return 1;
}
