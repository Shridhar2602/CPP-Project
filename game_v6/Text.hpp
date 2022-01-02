#pragma once

#include "constants.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"

using namespace std;

class Text
{
    public:
        Text();
        void set_rect(int x, int y, int w, int h);
        void set_color(Uint8 red, Uint8 green, Uint8 blue);
        void Render(string text);

    private:
        TTF_Font *Sans;
        SDL_Color color;
        SDL_Texture *tex;
        SDL_Rect dest_rect;
};