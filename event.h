#pragma once
#ifndef EVENT_H;
#define EVENT_H;

#include <iostream>
#include "game.h"
#include "graphic.h"

void initEvent(Game& game, Graphic& g, bool& moved); 
void toolhack(Game& game, Graphic& g); // Trick

#endif // EVENT_H