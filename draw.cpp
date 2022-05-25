#include <iostream>
#include <sstream>
#include "draw.h"

using namespace std;

void drawScore(long long &score, Graphic &g)
{
    SDL_Surface *sur = NULL;

    stringstream ss;
    ss << score; // Turn score to string
    string out = "Score: " + ss.str();

    sur = TTF_RenderText_Solid(g.font, out.c_str(), White); // Create text from surface
    g.text = SDL_CreateTextureFromSurface(g.renderer, sur); // Turn text into texture

    SDL_FreeSurface(sur);
}

void drawGame(Game &game, Graphic &g)
{
    SDL_RenderClear(g.renderer); // Clear the render before drawing again
    SDL_Rect rec = {0, 0, window_width, window_height};
    SDL_RenderCopy(g.renderer, g.background, &rec, NULL); // Draw background

    bool MTP; // If a box is empty
    int pos = 0;

    for (int i = 1; i <= boardSize; i++)
        for (int j = 1; j <= boardSize; j++)
        {
            MTP = 0;
            switch (game.Board[i][j])
            {
            case 2:
                rec = g.spriteRec[0];
                break;
            case 4:
                rec = g.spriteRec[1];
                break;
            case 8:
                rec = g.spriteRec[2];
                break;
            case 16:
                rec = g.spriteRec[3];
                break;
            case 32:
                rec = g.spriteRec[4];
                break;
            case 64:
                rec = g.spriteRec[5];
                break;
            case 128:
                rec = g.spriteRec[6];
                break;
            case 256:
                rec = g.spriteRec[7];
                break;
            case 512:
                rec = g.spriteRec[8];
                break;
            case 1024:
                rec = g.spriteRec[9];
                break;
            case 2048:
                rec = g.spriteRec[10];
                break;
            case 4096:
                rec = g.spriteRec[11];
                break;
            case 8192:
                rec = g.spriteRec[12];
                break;
            case 16384:
                rec = g.spriteRec[13];
                break;
            case 32768:
                rec = g.spriteRec[14];
                break;
            case 65536:
                rec = g.spriteRec[15];
                break;
            default:
                MTP = 1;
            }
            pos = i * boardSize - (boardSize - j) - 1; // Position of the box in winRec[]
            if (MTP == 0)
                SDL_RenderCopy(g.renderer, g.spriteTexture, &rec, &g.winRec[pos]); // cut spriteTexture into rec and then draw in Window at the position of winRec
        }

    drawScore(game.score, g);                           // Update the score and change g.text
    SDL_RenderCopy(g.renderer, g.text, NULL, &textRec); // Null to get full texture of text
    SDL_DestroyTexture(g.text);                         // Free memory
    SDL_RenderPresent(g.renderer);                      // Show on Win
}

//-----------------------------------------------------------------------------//

bool GameOver(Game &game)
{
    // Check available space
    for (int i = 1; i <= boardSize; i++)
    {
        for (int j = 1; j <= boardSize; j++)
            if (game.Board[i][j] == 0) // If this box is empty then the board is not full yet, return GameOver = False
                return false;
    }
    // Check if there are two boxes have a same number when the board is full
    for (int i = boardSize; i >= 1; i--)
    {
        for (int j = boardSize; j >= 1; j--)
        {
            if (game.Board[i][j] == game.Board[i - 1][j] || game.Board[i][j] == game.Board[i][j - 1])
                return false;
        }
    }

    return true;
}