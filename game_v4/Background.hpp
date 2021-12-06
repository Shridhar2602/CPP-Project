#pragma once

#include "GameObject.hpp"
#include "TextureManager.hpp"
#include "constants.hpp"
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

private:
    SDL_Texture* background2 = NULL;
    SDL_Texture* grass = NULL;
    SDL_Texture* sky = NULL;

    int grass_offset = 0;
    SDL_Rect grass_src, grass_dest;
    SDL_Rect grass_src2, grass_dest2;
    SDL_Rect sky_src, sky_dest;

    const int x = 120;

    vector <SDL_Texture*> bg;
};