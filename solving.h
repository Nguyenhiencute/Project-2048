#pragma once
#ifndef SOLVING_H;
#define SOLVING_H;

#include <iostream>
#include <SDL.h>
#include "graphic.h"
#include "game.h"

using namespace std;

void StoreBoard(Game& game); // Store board into TempBoard before moving
void SavePreBoard(Game& game); // Store previous board

void inDoMove(vector <int>& DoMove, long long& score); // Sort each row or column in each move

void moveU(Game& game, Graphic& g); // Move up
void moveD(Game& game, Graphic& g); // Move down
void moveL(Game& game, Graphic& g); // Move left
void moveR(Game& game, Graphic& g); // Move right

void moveUndo(Game& game); // Undo one move

bool CheckMove(Game& game); // Check if after moving the board is different or not

#endif // SOLVING_H