#pragma once

#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "constants.hpp"
#include "Music.hpp"
#include <vector>

class Background : public GameObject
{
public:

    Background();
    ~Background();

    void grass_init();
    void update();
    void keyboard_handler();
    void render();
    void render_leaderboard();

private:
    SDL_Texture* background2 = NULL;
    SDL_Texture* grass = NULL;
    SDL_Texture* sky = NULL;
    SDL_Texture* start = NULL;

    SDL_Texture *leaderboard_background = NULL;
    SDL_Texture *leaderboard_board = NULL;
    SDL_Texture *tex_result = NULL;
    SDL_Texture *quit = NULL;

    SDL_Rect result_dest, board_dest, quit_dest;

    Music *level_start;

    int curr_dist = 0;
    int grass_offset = 0;
    int grass_offset_backwards = 0;

    SDL_Rect grass_src, grass_dest;
    SDL_Rect grass_src2, grass_dest2;
    SDL_Rect grass_src3, grass_dest3;
    SDL_Rect sky_src, sky_dest;

    const int x = 120;
    int start_counter = 250;
    SDL_Rect start_dest;

    vector <SDL_Texture*> bg;
};