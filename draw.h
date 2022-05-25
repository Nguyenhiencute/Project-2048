#pragma once
#ifndef DRAW_H;
#define DRAW_H;

#include <iostream>
#include <SDL.h>
#include <vector>
#include "graphic.h"
#include "game.h"

void drawScore(long long& score, Graphic& g);
void drawGame(Game& game, Graphic& g); // Draw board
bool GameOver(Game& game); // Check the board if still have an available move after creating a random number 

#endif // DRAW_H