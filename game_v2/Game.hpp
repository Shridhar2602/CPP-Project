#pragma once 

#include <iostream>
//#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

        static SDL_Renderer *renderer;

        SDL_Window *getWindow() { return window; }

    private:
        int count = 0 ;
        bool isRunning;
        SDL_Window *window;
};
