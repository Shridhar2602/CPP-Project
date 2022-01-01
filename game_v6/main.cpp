#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"
#include "constants.hpp"
#include <iostream>
#include "Music.hpp"

using namespace std;

Game* game = NULL;

int main(void)
{
    cout << "SCREEN WIDTH: " << SCREEN_WIDTH << " SCREEN HEIGHT: " << SCREEN_HEIGHT << endl;
    const int fps = 200;
    const int frame_delay = 1000 / fps;

    Uint32 frame_start; 
    int frame_time;

    game = new Game();
    game->init("Cuphead", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

    Uint32 no_frames = 0;
    Uint32 total_time = 0;
    
    Music m;
    m.playmusic("assets/bgm.wav",false);

    while (game->running())
    {
        // gives number of milliseconds since SDL started
        frame_start = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frame_time = SDL_GetTicks() - frame_start;


        if (frame_delay > frame_time)
        {
            SDL_Delay(frame_delay - frame_time);
        }

        no_frames++;
        total_time = SDL_GetTicks() / 1000;

        //if (total_time > 0)
        //    cout << no_frames / (total_time) << endl;
    }

    game->clean();

    return 0;
}
