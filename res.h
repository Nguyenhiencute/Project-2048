#pragma once
#ifndef RES_H;
#define RES_H ;

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "graphic.h"

using namespace std;

void loadttf();

void clear();

void render(float p_x, float p_y, SDL_Texture *p_tex);

void render(const float &p_x, const float &p_y, const string &p_text, TTF_Font *font, const SDL_Color textColor);

void render(const float &p_x, const float &p_y, const char *p_text, TTF_Font *font, const SDL_Color textColor);

void renderCenter(const float &p_x, const float &p_y, const string &p_text, TTF_Font *font, const SDL_Color textColor);

void renderCenter(const float &p_x, const float &p_y, const char *p_text, TTF_Font *font, const SDL_Color textColor);

void display();

void cleanUp();

#endif // RES_H