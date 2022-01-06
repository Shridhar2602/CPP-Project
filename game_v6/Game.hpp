#pragma once

#include "constants.hpp"
#include "Mouse.hpp"
#include "Button.hpp"
#include "Music.hpp"
#include "Leaderboard.hpp"
//#include "Platform.hpp"
//#include <bits/stdc++.h>
#include <vector>
using namespace std;

enum render_type
{
    MAIN_MENU,
    INSTRUCTIONS,
    GAME,
    LEADERBOARD,
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

    int invincible_period = 600;

    Music m;

    int count = 0;
    bool isRunning;
    SDL_Window* window;
    int distCovered = 0;
    //int platforms[50][4];
    int l1[5]={3569,6106,10052,13964,17043};
    int platforms[25][4] = 
    {
        {1560, 280, 0, 1},
        {2204, 350, 0, 1},
        {2831, 273, 0, 1},
        {4307, 300, 0, 4},
        {5069, 481, 0, 7},
        {5535, 650, 0, 8},
        {5756, 400, 0, 5},
        {6456, 216, 0, 6},
        {7083, 554, 0, 2},
        {9022, 320, 0, 3},
        {9679, 495, 0, 7},
        {10434, 501, 0, 7},
        {11494, 302, 0, 1},
        {12115, 314, 0, 1},
        {13971, 288, 0, 1},
        {14874, 240, 0, 2},
        {16782, 350, 0, 4},
        {15894, 287, 0, 6},
        {18163, 573, 0, 7},
        {17674, 314, 0, 1},
        {19637, 339, 0, 3},
        {20869, 281, 0, 4},
        {23225, 555, 0, 5},
        {21754, 214, 0, 6},
        {22488, 453, 0, 7}
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
