#pragma once
#ifndef GAME_H;
#define GAME_H;

#include <iostream>
#include <SDL.h>
#include <vector>
#include "const.h"

using namespace std;

struct Game
{
    int Board[boardSize + 1][boardSize + 1]; // A square board from 1 to 4
    int TempBoard[boardSize + 1][boardSize + 1]; // Store the board before doing move
    int PrevBoard[boardSize + 1][boardSize + 1]; // Store the previous board in order to use undo move

    int x, y; // Location of a box in Board

    long long score;
    long long tmpscore;
    long long prevscore;

    int r; // A random number from aRandom to pick for a box

    vector <int> DoMove; // Step by step for each column or row

    bool gaming; // Still wanna play
};

#endif // GAME_H
