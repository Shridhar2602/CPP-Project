#pragma once

#include "constants.hpp"
#include "TextureManager.hpp"
#include "Text.hpp"
#include <map>
#include <fstream>

using namespace std;

class Leaderboard
{
    private:
        fstream file;
        string scores[6];

        int score;
        int set_score = 1;
        int buffer_time = 200;


        SDL_Event e;
        string name = "";

    public:
        Leaderboard();
        ~Leaderboard();

        void open();
        void update();
        void sort();
        void add();
        void render(int);
};


