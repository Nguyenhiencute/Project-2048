#pragma once
#ifndef BUTTON_H;
#define BUTTON_H ;

#include <iostream>
#include <SDL.h>
#include "graphic.h"
#include "res.h"

struct Button
{
    int x, y, w, h;
    Button(int _x = 0, int _y = 0, int _w = 0, int _h = 0)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }
};
bool isMouseIn(SDL_Event e, Button button);

void renderButton();

#endif // BUTTON_H