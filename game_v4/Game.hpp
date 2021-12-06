#pragma once

#include "constants.hpp"
//#include "Platform.hpp"
//#include <bits/stdc++.h>
#include <vector>
using namespace std;

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
    int count = 0;
    bool isRunning;
    SDL_Window* window;
    int distCovered = 0;

    int platforms[10][4] = {
        {(200 + SCREEN_WIDTH / 2),  250, 432, 188},
        {(500 + SCREEN_WIDTH),  650, 432, 188},
        {(200 + 3*SCREEN_WIDTH / 2),  250, 432, 188},
        {(400 + 4*SCREEN_WIDTH / 2),  350, 432, 188},
        {(200 + 5*SCREEN_WIDTH / 2),  450, 432, 188},
        {(500 + 6*SCREEN_WIDTH / 2),  400, 432, 188},
        {(200 + 7*SCREEN_WIDTH / 2),  550, 432, 188},
        {(400 + 8*SCREEN_WIDTH / 2),  650, 432, 188},
        {(000 + 9*SCREEN_WIDTH / 2),  750, 432, 188},
        {(500 + 10*SCREEN_WIDTH / 2),  350, 432, 188}
    };
    //std::vector<Platform*> ListOfPlatforms;
};