#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "const.h"
#include "game.h"
#include "graphic.h"
#include "draw.h"
#include "solving.h"
#include "event.h"
#include "res.h"
#include "button.h"

using namespace std;

// Game tutorial: Random -> Check movement -> Draw board -> Repeat.
// Use Space to return ONE move

struct HighScore
{
    int top5 = 5;
    long long score[5];
};

SDL_Texture *createTexture(SDL_Renderer *renderer, string path);
void initSpriteRects(vector<SDL_Rect> &spriteRec, vector<SDL_Rect> &winRec); // Make spriteRec
void err(string &m);

// Create game when start a new game --------------------------------------------//

void RandBoard(Game &game);
void createGame(Game &game, HighScore &highscore);
bool initGraphic(Graphic &g);

// When end game --------------------------------------------------------------//

void highBoard(Graphic &g, HighScore &hs);                 // Draw high score board
void textEnd(Graphic &g, long long &score, HighScore &hs); // Play again by pressing ENTER
void close(Graphic &g);                                    // Destroy everything <necessary>

// Music and menu ------------------------------------------------------------//
extern bool mute;
extern bool mainMenu;
extern int VOLUME_music_max;
extern int VOLUME_music;
extern int VOLUME_chuck;

extern Button playButton;
extern Button MuteButton;
extern Button UnmuteButton;
extern Button UpBotton;
extern Button DownBotton;
extern Button quitButton;

// Render menu ---------------------------------------------------------------//
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

//=============================================================================//

int main(int agrc, char *agrv[])
{
    Game game;

    HighScore highscore;
    srand(time(NULL));
    if (!initGraphic(g))
    {
        close(g);
        return EXIT_FAILURE;
    }

    game.gaming = 1;
    bool run = 1, drawed = 1;
    g.font = TTF_OpenFont(fontPath.c_str(), 26);
    loadttf();
    while (game.gaming)
    {
        bool moved = 1;

        if (run == 1)
        {
            drawed = 1;
            createGame(game, highscore);
            g.music = Mix_LoadMUS(musicPath[rand() % 5].c_str());
            if (Mix_PlayMusic(g.music, -1) != 0)
            {
                string m;
                m = Mix_GetError();
                err(m);
                break;
            }
        }
        else
        {
            Mix_FreeMusic(g.music);
            g.music = NULL;
        }

        while (run)
        {
            while (SDL_PollEvent(&g.event) != 0) // Analyze event
            {

                if (g.event.type == SDL_QUIT) // Quit game if click X button
                {
                    close(g);
                    return 0;
                }
                if (g.event.type == SDL_KEYDOWN) // Quit game if click X button
                {
                    if (g.event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        run = 0;
                        break;
                    }
                }

                if (mainMenu)
                {

                    if (isMouseIn(g.event, quitButton))
                    {
                        if (g.event.type == SDL_MOUSEBUTTONDOWN)
                        {
                            close(g);
                            return 0;
                        }
                    }
                    if (isMouseIn(g.event, MuteButton))
                    {
                        if (!mute && g.event.type == SDL_MOUSEBUTTONDOWN)
                        {
                            mute = true;
                            Mix_VolumeMusic(0);
                            continue;
                        }
                    }
                    if (isMouseIn(g.event, UnmuteButton))
                    {
                        if (mute && g.event.type == SDL_MOUSEBUTTONDOWN)
                        {
                            mute = false;
                            Mix_VolumeMusic(VOLUME_music);
                            continue;
                        }
                    }
                    if (isMouseIn(g.event, UpBotton))
                    {
                        if (g.event.type == SDL_MOUSEBUTTONDOWN)
                        {
                            VOLUME_music += 10;
                            mute = false;
                            if (VOLUME_music > VOLUME_music_max)
                                VOLUME_music = VOLUME_music_max;
                            Mix_VolumeMusic(VOLUME_music);
                        }
                    }
                    if (isMouseIn(g.event, DownBotton))
                    {
                        if (g.event.type == SDL_MOUSEBUTTONDOWN)
                        {
                            VOLUME_music -= 10;
                            if (VOLUME_music < 0)
                            {
                                VOLUME_music = 0;
                                mute = true;
                            }
                            Mix_VolumeMusic(VOLUME_music);
                        }
                    }
                    if (isMouseIn(g.event, playButton))
                    {
                        if (g.event.type == SDL_MOUSEBUTTONDOWN)
                        {
                            mainMenu = false;
                        }
                    }
                }
                else
                {
                    if (g.event.type == SDL_KEYDOWN) // Solving
                    {
                        initEvent(game, g, moved);
                    }
                    if (moved == 1)
                        break;
                }
            }

            if (mainMenu)
            {
                renderButton();
            }
            else
            {
                if (moved == 1) // If Board has moved then random a number for an empty box
                {
                    SavePreBoard(game);
                    RandBoard(game);
                    moved = 0;
                }
                drawGame(game, g);       // Draw the board
                if (GameOver(game) == 1) // If after random, there are no available move then gameover, run = 0; Ask if the player wants to play again
                {
                    run = 0;
                    break;
                }
            }
        }
        while (SDL_PollEvent(&g.event) != 0) // After endgame
        {

            if (g.event.type == SDL_QUIT)
            {
                close(g);
                return 0;
            }

            if (g.event.type == SDL_KEYDOWN && g.event.key.keysym.sym == SDLK_RETURN) // If wanna play again
            {
                run = 1;
                mainMenu = 1;
                break;
            }
            if (g.event.type == SDL_KEYDOWN && g.event.key.keysym.sym == SDLK_SPACE) // If not, or click X button
            {
                run = 0;
                game.gaming = 0;
                break;
            }
        }

        if (game.score > 99999999)
            game.score = 0;
        if (drawed == 1)
        {

            textEnd(g, game.score, highscore); // Instruction to play agian
            drawed = 0;
        }
    }
    close(g); // Delay 1s then close
    return 0;
}

//=============================================================================//

SDL_Texture *createTexture(SDL_Renderer *renderer, string path)
{
    SDL_Surface *sur = IMG_Load(path.c_str());
    if (sur == NULL)
    {
        string m = SDL_GetError();
        err(m);
        return NULL;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, sur);
    SDL_FreeSurface(sur);
    return tex;
}

void initSpriteRects(vector<SDL_Rect> &spriteRec, vector<SDL_Rect> &winRec)
{
    SDL_Rect rec = {0, 0, spriteSize, spriteSize};

    for (int i = 0; i <= (spriteSize - 1) * boardSize; i += spriteSize)
        for (int j = 0; j <= (spriteSize - 1) * boardSize; j += spriteSize)
        {
            rec.x = j;
            rec.y = i;
            spriteRec.push_back(rec);
        }
    rec = {0, 0, spriteWin, spriteWin};

    int space = (window_width - boardSize * spriteWin) / 2;
    for (int i = space; i < window_width - space; i += spriteWin)
        for (int j = space; j < window_width - space; j += spriteWin)
        {
            rec.x = j;
            rec.y = i;
            winRec.push_back(rec);
        }
}

void err(string &m)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", m.c_str(), NULL);
}

//-----------------------------------------------------------------------------//

void RandBoard(Game &game)
{
    game.r = rand() % (boardSize * boardSize) + 1;
    game.x = (game.r - 1) / boardSize + 1;
    game.y = (game.r - 1) % boardSize + 1;

    while (game.Board[game.x][game.y] != 0)
    {
        game.r = rand() % (boardSize * boardSize) + 1;
        game.x = (game.r - 1) / boardSize + 1;
        game.y = (game.r - 1) % boardSize + 1;
    }

    game.Board[game.x][game.y] = aRandom[rand() % 6];
}

void createGame(Game &game, HighScore &highscore)
{
    for (int i = 0; i <= boardSize; i++)
        for (int j = 0; j <= boardSize; j++)
        {
            game.Board[i][j] = 0;
            game.TempBoard[i][j] = 0;
            game.PrevBoard[i][j] = 0;
        }

    RandBoard(game);
    game.score = 0;
    game.tmpscore = 0;
    game.prevscore = 0;
    game.gaming = 1;

    // Load Top 5 High score
    ifstream hs(highScorePath);

    if (hs)
    {
        for (int i = 0; i < highscore.top5; i++)
        {
            hs >> highscore.score[i];
        }
        hs.close();
    }
    else
    {
        string m = "Bug fstream";
        err(m);
    }
}

bool initGraphic(Graphic &g)
{
    g.Window = NULL;
    g.renderer = NULL;
    g.background = NULL;
    g.spriteTexture = NULL;
    g.music = NULL;
    g.font = NULL;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        string m = SDL_GetError();
        err(m);
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        string m = SDL_GetError();
        err(m);
        return false;
    }

    g.Window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);

    if (g.Window == NULL)
    {
        string m = SDL_GetError();
        err(m);
        return false;
    }

    g.renderer = SDL_CreateRenderer(g.Window, -1, SDL_RENDERER_ACCELERATED);

    if (g.renderer == NULL)
    {
        string m = SDL_GetError();
        err(m);
        return false;
    }

    g.background = createTexture(g.renderer, backgroundPath[rand() % 4]);
    g.spriteTexture = createTexture(g.renderer, spritePath);

    if (g.background == NULL || g.spriteTexture == NULL)
    {
        string m = SDL_GetError();
        err(m);
        return false;
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) != 0) // Open audio
    {
        string m = SDL_GetError();
        err(m);
        return false;
    }

    for (int i = 0; i < 5; i++)
    {
        g.music = Mix_LoadMUS(musicPath[i].c_str()); // Create music for game
        if (g.music == NULL)
        {
            string m = SDL_GetError();
            err(m);
            return false;
        }
    }

    if (TTF_Init() != 0)
    {
        string m = SDL_GetError();
        err(m);
        return false;
    }

    g.font = TTF_OpenFont(fontPath.c_str(), 26);

    if (g.font == NULL)
    {
        string m = SDL_GetError();
        err(m);
        return false;
    }

    initSpriteRects(g.spriteRec, g.winRec);

    return true;
}

//-----------------------------------------------------------------------------//

void highBoard(Graphic &g, HighScore &hs)
{
    g.font = TTF_OpenFont(fontPath2.c_str(), 22);
    string out;
    SDL_Surface *sur;
    SDL_Rect rec;

    for (int i = 0; i < hs.top5; i++)
    {
        ostringstream convert;
        convert << hs.score[i];
        out = convert.str();

        if (i == 0)
            SDL_SetRenderDrawColor(g.renderer, 25, 25, 112, 255); // Midnight Blue
        else if (i == 1)
            SDL_SetRenderDrawColor(g.renderer, 0, 139, 139, 255); // Dark Cyan
        else if (i == 2)
            SDL_SetRenderDrawColor(g.renderer, 46, 139, 87, 255); // Sea Green
        else if (i == 3)
            SDL_SetRenderDrawColor(g.renderer, 255, 210, 0, 255); // Gold
        else
            SDL_SetRenderDrawColor(g.renderer, 220, 20, 60, 255); // Crimson

        rec = {150, (i + 1) * 100, window_width - 300, 40};
        if (hs.score[i] < 10000)
            rec = {175, (i + 1) * 100, window_width - 350, 40};
        if (hs.score[i] < 1000)
            rec = {195, (i + 1) * 100, window_width - 390, 40};
        if (hs.score[i] < 10)
            rec = {235, (i + 1) * 100, window_width - 470, 40};
        SDL_RenderFillRect(g.renderer, &rec); // Draw a filled rec

        sur = TTF_RenderText_Solid(g.font, out.c_str(), White);
        g.text = SDL_CreateTextureFromSurface(g.renderer, sur);

        SDL_RenderCopy(g.renderer, g.text, NULL, &rec);
        SDL_DestroyTexture(g.text);
    }
    SDL_SetRenderDrawColor(g.renderer, 0, 0, 0, 0); // set colour transparent
    SDL_FreeSurface(sur);
}

void textEnd(Graphic &g, long long &score, HighScore &hs)
{
    clear();
    render(0, 0, BG);
    render(45, 60, "Press ENTER to play again", font32, white);
    render(250, 150, "TOP 5:", font28, white);
    for (int i = 0; i < hs.top5; i++)
    {
        if (hs.score[i] <= score)
        {
            for (int j = hs.top5 - 1; j > i; j--)
                hs.score[j] = hs.score[j - 1];
            hs.score[i] = score;
            break;
        }
    }

    ofstream outs(highScorePath);
    if (outs)
    {
        outs.clear();
        for (int i = 0; i < hs.top5; i++)
        {
            render(250, 220 + i * 50, std::to_string(hs.score[i]), font24, white);
            outs << hs.score[i] << endl;
        }

        outs.close();
    }
    else
    {
        string m = "Bug fstream";
        err(m);
    }
    display();
}

//-----------------------------------------------------------------------------//

void close(Graphic &g)
{
    SDL_Delay(500);
    Mix_FreeMusic(g.music);
    TTF_CloseFont(g.font);
    SDL_DestroyTexture(g.spriteTexture);
    SDL_DestroyTexture(g.text);
    SDL_DestroyTexture(g.background);
    SDL_DestroyRenderer(g.renderer);
    SDL_DestroyWindow(g.Window);

    g.music = NULL;
    g.font = NULL;
    g.spriteTexture = NULL;
    g.text = NULL;
    g.background = NULL;
    g.renderer = NULL;
    g.Window = NULL;

    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}
