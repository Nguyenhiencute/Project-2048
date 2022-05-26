#include <iostream>
#include "game.h"
#include "graphic.h"
#include "solving.h"

using namespace std;

void toolhack(Game& game, Graphic& g)
{
    int k = 1;
    for (int i = 1; i <= boardSize; i++)
        for (int j = 1; j <= boardSize; j++) game.Board[i][j] = (k*=2);
    game.score = 9999999999;
}

void initEvent(Game& game, Graphic& g, bool& moved)
{
    switch (g.event.key.keysym.sym)
    {
        case SDLK_UP:           StoreBoard(game); moveU(game, g);   moved = CheckMove(game); break;
        case SDLK_DOWN:         StoreBoard(game); moveD(game, g);   moved = CheckMove(game); break;
        case SDLK_LEFT:         StoreBoard(game); moveL(game, g);   moved = CheckMove(game); break;
        case SDLK_RIGHT:        StoreBoard(game); moveR(game, g);   moved = CheckMove(game); break;
        case SDLK_SPACE:        if (game.score == 0) break; else {moveUndo(game); moved = 0; break; } 
        case SDLK_LCTRL:        toolhack(game, g); moved = 0; break; 
        default: return;
    }
}


