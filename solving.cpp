#include <iostream>
#include <sstream>
#include "game.h"
#include "graphic.h"
#include "draw.h"

using namespace std;

void StoreBoard(Game& game)
{
    for (int i = 1; i <= boardSize; i++)
        for (int j = 1; j <= boardSize; j++) game.TempBoard[i][j] = game.Board[i][j];
    game.tmpscore = game.score;
}

void SavePreBoard(Game& game)
{
    for (int i = 1; i <= boardSize; i++)
        for (int j = 1; j <= boardSize; j++) game.PrevBoard[i][j] = game.TempBoard[i][j];
    game.prevscore = game.tmpscore;
}

//-----------------------------------------------------------------------------//

void moveU(Game& game, Graphic& g)
{
    int canMove = true;
    bool canPlus[5][5];
    for (int i = 1; i <= boardSize; i++)
    for (int j = 1; j <= boardSize; j++)
            canPlus[i][j] = true;
    while(canMove)
    {
        canMove = false;
        for (int i = 2; i <= boardSize; i++)
        for (int j = 1; j <= boardSize; j++)
        {
            if (game.Board[i][j] == 0)  continue;

            if (game.Board[i - 1][j] == 0)
            {
                game.Board[i - 1][j] = game.Board[i][j];
                game.Board[i][j] = 0;
                canMove = true;
            }
            else
            if (game.Board[i - 1][j] == game.Board[i][j] && canPlus[i - 1][j] == true && canPlus[i][j] == true)
            {
                game.Board[i - 1][j] *= 2;
                game.score += game.Board[i - 1][j];
                game.Board[i][j] = 0;
                canPlus[i - 1][j] = false;
                canMove = true;
            }
        }
        drawGame(game, g);
        SDL_Delay(30);
    }
}

void moveD(Game& game, Graphic& g)
{
    int canMove = true;
    bool canPlus[5][5];
    for (int i = 1; i <= boardSize; i++)
    for (int j = 1; j <= boardSize; j++)
            canPlus[i][j] = true;
    while(canMove)
    {
        canMove = false;
        for (int i = boardSize - 1; i >= 1; i--)
        for (int j = 1; j <= boardSize; j++)
        {
            if (game.Board[i][j] == 0)  continue;

            if (game.Board[i + 1][j] == 0)
            {
                game.Board[i + 1][j] = game.Board[i][j];
                game.Board[i][j] = 0;
                canMove = true;
            }
            else
            if (game.Board[i + 1][j] == game.Board[i][j] && canPlus[i + 1][j] == true && canPlus[i][j] == true)
            {
                game.Board[i + 1][j] *= 2;
                game.score += game.Board[i + 1][j];
                game.Board[i][j] = 0;
                canPlus[i + 1][j] = false;
                canMove = true;
            }
        }
        drawGame(game, g);
        SDL_Delay(30);
    }
}

void moveL(Game& game, Graphic& g)
{
    int canMove = true;
    bool canPlus[5][5];
    for (int i = 1; i <= boardSize; i++)
    for (int j = 1; j <= boardSize; j++)
            canPlus[i][j] = true;
    while(canMove)
    {
        canMove = false;
        for (int j = 2; j <= boardSize; j++)
        for (int i = 1; i <= boardSize; i++)
        {
            if (game.Board[i][j] == 0)  continue;

            if (game.Board[i][j - 1] == 0)
            {
                game.Board[i][j - 1] = game.Board[i][j];
                game.Board[i][j] = 0;
                canMove = true;
            }
            else
            if (game.Board[i][j - 1] == game.Board[i][j] && canPlus[i][j - 1] == true && canPlus[i][j] == true)
            {
                game.Board[i][j - 1] *= 2;
                game.score += game.Board[i][j - 1];
                game.Board[i][j] = 0;
                canPlus[i][j - 1] = false;
                canMove = true;
            }
        }
        drawGame(game, g);
        SDL_Delay(30);
    }
}

void moveR(Game& game, Graphic& g)
{
    int canMove = true;
    bool canPlus[5][5];
    for (int i = 1; i <= boardSize; i++)
    for (int j = 1; j <= boardSize; j++)
            canPlus[i][j] = true;
    while(canMove)
    {
        canMove = false;
        for (int j = boardSize - 1; j >= 1; j--)
        for (int i = 1; i <= boardSize; i++)
        {
            if (game.Board[i][j] == 0)  continue;

            if (game.Board[i][j + 1] == 0)
            {
                game.Board[i][j + 1] = game.Board[i][j];
                game.Board[i][j] = 0;
                canMove = true;
            }
            else
            if (game.Board[i][j + 1] == game.Board[i][j] && canPlus[i][j + 1] == true && canPlus[i][j] == true)
            {
                game.Board[i][j + 1] *= 2;
                game.score += game.Board[i][j + 1];
                game.Board[i][j] = 0;
                canPlus[i][j + 1] = false;
                canMove = true;
            }
        }
        drawGame(game, g);
        SDL_Delay(30);
    }
}

void moveUndo(Game& game)
{
    for (int i = 1; i <= boardSize; i++)
        for (int j = 1; j <= boardSize; j++) game.Board[i][j] = game.PrevBoard[i][j];
    game.score = game.prevscore;
}

bool CheckMove(Game& game)
{
    for (int i = 1; i <= boardSize; i++)
        for (int j = 1; j <= boardSize; j++) if (game.Board[i][j] != game.TempBoard[i][j]) return 1;
    return 0;
}