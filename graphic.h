#pragma once
#ifndef GRAPHIC_H;
#define GRAPHIC_H;

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "const.h"

using namespace std;

struct Graphic
{
    SDL_Window* Window; 

    SDL_Renderer* renderer; // To draw into Window

    SDL_Texture* background; // Background image
    SDL_Texture* spriteTexture; // Sprites image

    Mix_Music* music; 

    TTF_Font* font; 

    SDL_Texture* text; // Game text for both score and textEnd

    vector <SDL_Rect> spriteRec; // Sprite location in sprite.png
    vector <SDL_Rect> winRec; // Sprite location in Window

    SDL_Event event; // Event include space to undo, up, down, left, right
};

#endif // GRAPHIC_H