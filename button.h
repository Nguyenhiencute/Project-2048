#pragma once
#ifndef BUTTON_H;
#define BUTTON_H;

#include <iostream>
#include <string>
#include <SDL.h>

using namespace std;

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

Button playButton(230, 210, 180, 28);
Button MuteButton(230, 250, 100, 28);
Button UnmuteButton(230, 250, 100, 28);
Button UpBotton(280, 290, 36, 36);
Button DownBotton(230, 290, 36, 36);
Button quitButton(230, 330, 100, 28);

#endif // BUTTON_H