/**
 * @file enigme_match.c
 */
#include "matchsticks.h"
#include "background.h"
#include "hero.h"

void initialiser_text_enigme(text_enigme *i, char message[40], int x, int y, int size)
{
    TTF_Init();
    i->color1.r = 255;
    i->color1.g = 0;
    i->color1.b = 0;
    i->color2.r = 255;
    i->color2.g = 255;
    i->color2.b = 255;
    i->font = TTF_OpenFont("../fonts/angelina.TTF", size);
    i->text = TTF_RenderText_Blended(i->font, message, i->color1);
    i->position.x = x;
    i->position.y = y;
}

void afficher_text_enigme(text_enigme i, SDL_Surface *ecran, char message[20])
{
    i.text = TTF_RenderText_Blended(i.font, message, i.color1);
    SDL_BlitSurface(i.text, NULL, ecran, &i.position);
}

int rand_matchs(int MatchCount)
{
    srand(time(0));
    MatchCount = (rand() % 21 + 1);
    return MatchCount;
}

void Init(text_enigme *matchText, text_enigme *PturnText, text_enigme *AIturnText, Matchstick *match)
{
    int Matchcount = 0;
    initialiser_text_enigme(matchText, "Do not pick more than 4 matchsticks.", 200, 10, 35);
    initialiser_text_enigme(PturnText, "Player's Turn!", 320, 100, 20);
    initialiser_text_enigme(AIturnText, "AI's Turn!", 320, 150, 20);
    match->Matchstick = IMG_Load("../img/enigme/match.png");
    match->MatchCount = rand_matchs(Matchcount);
    match->positionMatchstick.x = SCREEN_WIDTH / (match->MatchCount);
    match->positionMatchstick.y = (SCREEN_HEIGHT / 3) * 2;
}

void affichage_matchs(SDL_Surface *screen, Matchstick *match)
{
    int i;

    for (i = 0; i < match->MatchCount; i++)
    {
        SDL_BlitSurface(match->Matchstick, NULL, screen, &match->positionMatchstick);
        match->positionMatchstick.x += 20;
    }
    match->positionMatchstick.x = 10;
}

void updateText(SDL_Surface *screen, int turn, text_enigme *PturnText, text_enigme *AIturnText)
{
    //Update
    switch (turn)
    {
    case 1:
        PturnText->text = TTF_RenderText_Blended(PturnText->font, "Player's Turn!", PturnText->color1);
        AIturnText->text = TTF_RenderText_Blended(AIturnText->font, "AI's Turn!", AIturnText->color2);
        break;
    case -1:
        AIturnText->text = TTF_RenderText_Blended(AIturnText->font, "AI's Turn!", AIturnText->color1);
        PturnText->text = TTF_RenderText_Blended(PturnText->font, "Player's Turn!", PturnText->color2);
        break;
    }
}

void afficherText(SDL_Surface *screen, text_enigme matchtext, text_enigme PturnText, text_enigme AIturnText, int turn)
{
    SDL_BlitSurface(matchtext.text, NULL, screen, &matchtext.position);
    SDL_BlitSurface(PturnText.text, NULL, screen, &PturnText.position);
    SDL_BlitSurface(AIturnText.text, NULL, screen, &AIturnText.position);
}

void game_end(Matchstick match, int Turn, text_enigme *PturnText, text_enigme *AIturnText, int *AIcontinuer, int *win)
{
    if (match.MatchCount <= 0)
    {
        switch (Turn)
        {
        case 1:
            PturnText->text = TTF_RenderText_Blended(PturnText->font, "You Win!", PturnText->color1);
            AIturnText->text = TTF_RenderText_Blended(AIturnText->font, "AI Wins!", AIturnText->color2);
            (*win) *= (-1);
            break;
        case -1:
            AIturnText->text = TTF_RenderText_Blended(AIturnText->font, "AI Wins!", AIturnText->color1);
            PturnText->text = TTF_RenderText_Blended(PturnText->font, "You Win!", PturnText->color2);
            break;
        }
        (*AIcontinuer) = 0;
    }
}

int AI_enigme(SDL_Surface *screen, hero *h)
{
    text_enigme matchText;
    text_enigme PturnText;
    text_enigme AIturnText;

    Matchstick match;

    SDL_Event event;

    SDL_Surface *bg = NULL;
    SDL_Rect positionbg;

    positionbg.x = 0;
    positionbg.y = 0;
    bg = IMG_Load("../img/enigme/bg.jpg");

    screen = SDL_SetVideoMode(bg->w, bg->h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    int turn = 1, user = 0, AI = 0, AIcontinuer = 1, test = 0, win = -1;
    int tempsActuel = 0, tempsPrecedent = 0;
    
    Init(&matchText, &PturnText, &AIturnText, &match);
    while (AIcontinuer)
    {
        if (turn == 1)
        {
            while (SDL_PollEvent(&event))
            {
                printf("MATCH_COUNT: %d\n", match.MatchCount);
                switch (event.type)
                {
                case SDLK_ESCAPE:
                    AIcontinuer = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        AIcontinuer = 0;
                        break;
                    case SDLK_a:

                        user = 1;
                        turn = -1;

                        break;
                    case SDLK_z:

                        user = 2;
                        turn = -1;

                        break;
                    case SDLK_e:

                        user = 3;
                        turn = -1;

                        break;
                    case SDLK_r:

                        user = 4;
                        turn = -1;

                        break;
                    }
                    break;
                }
            }
        }
        SDL_BlitSurface(bg, NULL, screen, &positionbg);
        match.MatchCount -= user;
        affichage_matchs(screen, &match);
        updateText(screen, turn, &PturnText, &AIturnText);
        game_end(match, turn, &PturnText, &AIturnText, &AIcontinuer, &win);
        afficherText(screen, matchText, PturnText, AIturnText, turn);
        SDL_Flip(screen);
        if (turn == -1 && match.MatchCount > 0)
        {
            SDL_Delay(3000);
            switch (match.MatchCount)
            {
            case 4:
                AI = 3;
                break;
            case 3:
                AI = 2;
                break;
            case 2:
                AI = 1;
                break;
            case 1:
                AI = 1;
                break;

            default:
                AI = rand() % 4 + 1;
                break;
            }
            match.MatchCount -= AI;
            affichage_matchs(screen, &match);
            AI = 0;
            user = 0;
            turn = 1;

            updateText(screen, turn, &PturnText, &AIturnText);
            game_end(match, turn, &PturnText, &AIturnText, &AIcontinuer, &win);
            afficherText(screen, matchText, PturnText, AIturnText, turn);
        }

        SDL_Flip(screen);
    }
    SDL_Delay(5000);
    SDL_FreeSurface(matchText.text);
    SDL_FreeSurface(PturnText.text);
    TTF_CloseFont(matchText.font);
    TTF_CloseFont(PturnText.font);
    SDL_FreeSurface(bg);

    if (win == 1)
        h->score_hero.valeur_score += 20;
    else
    {
        h->score_hero.valeur_score -= 20;
    }
}
