#pragma once
#ifndef CONST_H;
#define CONST_H ;

#include <iostream>
#include <string>
#include <SDL.h>

using namespace std;

const int boardSize = 4; 

const int spriteSize = 130; // Size of source sprite
const int spriteWin = 100;  // Size of Window sprite

const int window_width = 600;
const int window_height = 700;

const int aRandom[] = {2, 2, 2, 2, 2, 4}; 

const SDL_Color White = {255, 255, 255, 255};

const SDL_Rect textRec = {window_width / 2 - 100, window_height - 120, 200, 70}; // Score text rec for score only

const string windowTitle = "2048";
const string backgroundPath[] = {"./assets/image/bg1.jpeg",
                                 "./assets/image/bg2.jpeg",
                                 "./assets/image/bg3.jpeg",
                                 "./assets/image/bg4.jpeg"};

const string spritePath = "./assets/image/sprite.png";

const string musicPath[] = {"./assets/music/Dance-the-night-away.ogg",
                            "./assets/music/Tabun.ogg",
                            "./assets/music/No-Guidance.ogg",
                            "./assets/music/Dynamite.ogg",
                            "./assets/music/Haru-Haru.ogg"};

const string fontPath = "./assets/font/chesnagrotesk.ttf"; // Font path for "Score:..."

const string fontPath2 = "./assets/font/chesnagrotesk.ttf"; // Font path for text Play again

const string highScorePath = "highscore.txt";

#endif // CONST_H