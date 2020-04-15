/*
this function is pretty basic , we all know that sdl uses a queue for the key maping so we can only get one key on every lap of the loop so if we press the up key on the key board then we hit shift while still pressing the up key the sdl will return the last key we pressed which will be the shit and we will loose the up key
so to solve this problem we will creat a structure that will have all our main functions on the game as moving right , left , jump ect ...
and we will give them 1 when they are pressed and will only get 0 when we get our fingers out of that key so when we hit two or even 10 keys at the same time they will all have 1 on them so we can treat a combined key press and this is called key mapping

for further info on how SDL_PollEvent works you can check the documentation of this function on the sdl wiki it has a better and more detailed explanation
*/



void getInput(void)
{

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {

        switch (event.type)
        {

        case SDL_QUIT:
            exit(0);
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {

            case SDLK_ESCAPE:
                exit(0);
                break;

            case SDLK_DELETE:
                input.erase = 1;
                break;

            case SDLK_LSHIFT:

                break;

            case SDLK_LCTRL:
                input.parachute = 1;
                break;

            case SDLK_SPACE:
                input.jump = 1;
                break;

            case SDLK_v:
                input.attack = 1;
                break;

            case SDLK_LEFT:
                input.left = 1;
                break;

            case SDLK_RIGHT:
                input.right = 1;
                break;

            case SDLK_DOWN:
                input.down = 1;
                break;

            case SDLK_UP:
                input.up = 1;
                break;

            case SDLK_RETURN:
                input.enter = 1;
                break;

            default:
                break;

            }

            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {

            case SDLK_DELETE:
                input.erase = 0;
                break;

            case SDLK_LSHIFT:
                input.sprint = 0;
                break;

            case SDLK_LCTRL:
                input.parachute = 0;
                break;

            case SDLK_SPACE:
                input.jump = 0;
                break;

            case SDLK_v:
                input.attack = 0;
                break;

            case SDLK_LEFT:
                input.left = 0;
                break;

            case SDLK_RIGHT:
                input.right = 0;
                break;

            case SDLK_DOWN:
                input.down = 0;
                break;

            case SDLK_UP:
                input.up = 0;
                break;

            case SDLK_RETURN:
                input.enter = 0;
                break;

            default:
                break;

            }

            break;

        }
    }
}
