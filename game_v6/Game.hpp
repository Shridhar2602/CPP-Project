#pragma once

#include "constants.hpp"
#include "Mouse.hpp"
#include "Button.hpp"
#include "Music.hpp"
//#include "Platform.hpp"
//#include <bits/stdc++.h>
#include <vector>
using namespace std;

enum render_type
{
    MAIN_MENU,
    INSTRUCTIONS,
    GAME,
    EXIT
};

class Game
{
public:
    Game();
    ~Game();

    void init(string, int, int, int, int, bool);

    void handleEvents();
    void update();
    bool running();
    void render();
    void clean();
    static SDL_Renderer* renderer;

    SDL_Window* getWindow() { return window; }

private:

    int screen_type = MAIN_MENU;
    SDL_Texture *menu_background = NULL;
    SDL_Texture *menu_instruction = NULL;

    bool playeralive=true;
    int score = 0;
    string score_str = "Score: 0";

    int life = 3;
    string life_str = "Life: 3";

    int invincible_period = 180;

    Music m;

    int count = 0;
    bool isRunning;
    SDL_Window* window;
    int distCovered = 0;
    //int platforms[50][4];
    int platforms[20][4] = {
        {(200 + SCREEN_WIDTH),              250, 0, 1},
        {(500 + 3 * SCREEN_WIDTH / 2),      300, 0, 4},
        {(500 + 4 * SCREEN_WIDTH / 2),      450, 0, 7},
        {(200 + 5 * SCREEN_WIDTH / 2),      650, 0, 8},
        {(400 + 5 * SCREEN_WIDTH / 2),      400, 0, 5},
        {(050 + 6 * SCREEN_WIDTH / 2),      470, 0, 6},
        {(580 + 6 * SCREEN_WIDTH / 2),      400, 0, 2},
        {(100 + 8 * SCREEN_WIDTH / 2),      350, 0, 3},
        {(500 + 9 * SCREEN_WIDTH / 2),      350, 0, 7},
        {(200 + 10 * SCREEN_WIDTH / 2),     550, 0, 7},
        {(300 + 11 * SCREEN_WIDTH / 2),     250, 0, 1},
        {(500 + 12 * SCREEN_WIDTH / 2),     250, 0, 1},
        {(500 + 13 * SCREEN_WIDTH / 2),     250, 0, 1},
        {(500 + 14 * SCREEN_WIDTH / 2),     270, 0, 6},
        {(200 + 15 * SCREEN_WIDTH / 2),     550, 0, 1},
        {(400 + 16 * SCREEN_WIDTH / 2),     650, 0, 1},
        {(000 + 17 * SCREEN_WIDTH / 2),     750, 0, 1},
        {(500 + 18 * SCREEN_WIDTH / 2),     350, 0, 1},
        {(000 + 19 * SCREEN_WIDTH / 2),     750, 0, 1},
        {(500 + 20 * SCREEN_WIDTH / 2),     408, 0, 1}
    };

    void fillPlatform() {
        int n = sizeof(platforms) / sizeof(platforms[0]);

        //for (int i = 0;i < n;i++) {
        //    platforms[i][3] = 1 + rand() % 8;
        //    platforms[i][0] = (rand() % 600) + (i * SCREEN_WIDTH / 2);
        //    if (platforms[i][3] != 7 && platforms[i][3] != 8)
        //        platforms[i][1] = (250 + rand() % 400);
        //    else
        //        platforms[i][1] = (400 + rand() % 400);
        //}
        for (int i = 0;i < n;i++) {
            switch (platforms[i][3])
            {
            case 1:
                platforms[i][2] = 432;
                break;
            case 2:
                platforms[i][2] = 700;
                break;
            case 3:
                platforms[i][2] = 545;
                break;
            case 4:
                platforms[i][2] = 748;
                break;
            case 5:
                platforms[i][2] = 700;
                break;
            case 6:
                platforms[i][2] = 600;
                break;
            case 7:
                platforms[i][2] = 425;
                break;
            case 8:
                platforms[i][2] = 184;
                break;
            default:
                break;
            }
        }
    }
    //std::vector<Platform*> ListOfPlatforms;
    //
    // 432, 188
    // 700, 570
    // 545, 200
    //
};
