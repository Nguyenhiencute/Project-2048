#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "res.h"
#include "const.h"

Graphic g;
TTF_Font *font36;
TTF_Font *font32;
TTF_Font *font32_outline;
TTF_Font *font28;
TTF_Font *font24;
TTF_Font *font16;
SDL_Texture *BG;
SDL_Color white = {255, 255, 255};
SDL_Color black = {0, 0, 0};

void loadttf()
{
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    BG = IMG_LoadTexture(g.renderer, "assets/image/Bgmenu.png");
    if (BG == NULL)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    std::cerr << "WTF" << '\n';
    font36 = TTF_OpenFont("assets/font/SigmarOne-Regular.ttf", 36);
    font32 = TTF_OpenFont("assets/font/SigmarOne-Regular.ttf", 32);
    font28 = TTF_OpenFont("assets/font/SigmarOne-Regular.ttf", 28);
    font32_outline = TTF_OpenFont("assets/font/SigmarOne-Regular.ttf", 32);
    font24 = TTF_OpenFont("assets/font/SigmarOne-Regular.ttf", 24);
    font16 = TTF_OpenFont("assets/font/SigmarOne-Regular.ttf", 16);
    TTF_SetFontOutline(font32_outline, 3);
}

void clear()
{
    SDL_SetRenderDrawColor(g.renderer, 0, 0, 0, 255);
    SDL_RenderClear(g.renderer);
}
void render(float p_x, float p_y, SDL_Texture *p_tex)
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

    SDL_Rect dst;
    dst.x = p_x;
    dst.y = p_y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(g.renderer, p_tex, &src, &dst);
}

void render(const float &p_x, const float &p_y, const std::string &p_text, TTF_Font *font, const SDL_Color textColor)
{
    char *cstr = new char[p_text.length() + 1];
    strcpy(cstr, p_text.c_str());
    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, cstr, textColor);
    SDL_Texture *message = SDL_CreateTextureFromSurface(g.renderer, surfaceMessage);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage->w;
    src.h = surfaceMessage->h;

    SDL_Rect dst;
    dst.x = p_x;
    dst.y = p_y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(g.renderer, message, &src, &dst);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void render(const float &p_x, const float &p_y, const char *p_text, TTF_Font *font, const SDL_Color textColor)
{
    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, p_text, textColor);
    SDL_Texture *message = SDL_CreateTextureFromSurface(g.renderer, surfaceMessage);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage->w;
    src.h = surfaceMessage->h;

    SDL_Rect dst;
    dst.x = p_x;
    dst.y = p_y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(g.renderer, message, &src, &dst);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void renderCenter(const float &p_x, const float &p_y, const std::string &p_text, TTF_Font *font, const SDL_Color textColor)
{
    char *cstr = new char[p_text.length() + 1];
    strcpy(cstr, p_text.c_str());

    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, cstr, textColor);
    SDL_Texture *message = SDL_CreateTextureFromSurface(g.renderer, surfaceMessage);
    delete[] cstr;
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage->w;
    src.h = surfaceMessage->h;

    SDL_Rect dst;
    dst.x = window_width / 2 - src.w / 2 + p_x;
    dst.y = window_height / 2 - src.h / 2 + p_y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(g.renderer, message, &src, &dst);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void renderCenter(const float &p_x, const float &p_y, const char *p_text, TTF_Font *font, const SDL_Color textColor)
{
    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(font, p_text, textColor);
    SDL_Texture *message = SDL_CreateTextureFromSurface(g.renderer, surfaceMessage);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage->w;
    src.h = surfaceMessage->h;

    SDL_Rect dst;
    dst.x = window_width / 2 - src.w / 2 + p_x;
    dst.y = window_height / 2 - src.h / 2 + p_y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(g.renderer, message, &src, &dst);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void display()
{
    SDL_RenderPresent(g.renderer);
}

void cleanUp()
{
    SDL_DestroyWindow(g.Window);
}