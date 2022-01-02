#pragma once

#include "constants.hpp"
#include "TextureManager.hpp"
#include "Text.hpp"
#include <fstream>

using namespace std;

class Leaderboard
{
    private:
        fstream file;
        string scores[6];
        SDL_Event e;
        string name = "";

    public:
        Leaderboard();
        void open();
        void update();
        void sort();
        void render();
};

