#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "graphic.h"
#include "res.h"
#include "button.h"

extern Graphic g;
extern TTF_Font *font36;
extern TTF_Font *font32;
extern TTF_Font *font32_outline;
extern TTF_Font *font28;
extern TTF_Font *font24;
extern TTF_Font *font16;
extern SDL_Texture *BG;
extern SDL_Color white;
extern SDL_Color black;

bool mute = false;
bool mainMenu = true;
int VOLUME_music_max = MIX_MAX_VOLUME / 2;
int VOLUME_music = MIX_MAX_VOLUME / 2;
int VOLUME_chuck = MIX_MAX_VOLUME / 2;

Button playButton(260, 210, 180, 28);
Button MuteButton(260, 250, 100, 28);
Button UnmuteButton(260, 250, 100, 28);
Button UpBotton(310, 290, 36, 36);
Button DownBotton(260, 290, 36, 36);
Button quitButton(260, 330, 100, 28);

bool isMouseIn(SDL_Event e, Button button)
{
    int mouseX, mouseY;
    int x, y, w, h;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (mouseX < button.x)
        return false;
    if (mouseY < button.y)
        return false;
    if (mouseX > button.x + button.w)
        return false;
    if (mouseY > button.y + button.h)
        return false;
    return true;
}

void renderButton()
{
    clear();
    render(0, 0, BG);
    if (isMouseIn(g.event, playButton))

        render(playButton.x, playButton.y, "PLAY", font28, white);

    else
        render(playButton.x, playButton.y, "PLAY", font24, white);

    if (mute)
    {
        if (isMouseIn(g.event, UnmuteButton))
            render(UnmuteButton.x, UnmuteButton.y, "UNMUTE", font28, white);
        else
            render(UnmuteButton.x, UnmuteButton.y, "UNMUTE", font24, white);
    }
    else
    {
        if (isMouseIn(g.event, MuteButton))
            render(MuteButton.x, MuteButton.y, "MUTE", font28, white);
        else
            render(MuteButton.x, MuteButton.y, "MUTE", font24, white);
    }

    if (isMouseIn(g.event, DownBotton))
        render(DownBotton.x, DownBotton.y, "-", font36, white);
    else
        render(DownBotton.x, DownBotton.y, "-", font32, white);

    if (isMouseIn(g.event, UpBotton))
        render(UpBotton.x, UpBotton.y, "+", font36, white);
    else
        render(UpBotton.x, UpBotton.y, "+", font32, white);

    if (isMouseIn(g.event, quitButton))
        render(quitButton.x, quitButton.y, "QUIT", font28, white);
    else
        render(quitButton.x, quitButton.y, "QUIT", font24, white);

    display();
}
