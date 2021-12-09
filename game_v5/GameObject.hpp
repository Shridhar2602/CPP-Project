#pragma once

#include "Game.hpp"
#include <vector>

#define GRAVITY 10

class GameObject
{
public:
    void setTexture(const char* texturesheet);
    void setSrc(int x, int y, int w, int h);
    void setDest(int x, int y, int w, int h);
    void setSpeed(int s) { speed = s; }

protected:
    int xpos, ypos, width, height;
    int speed;
    SDL_Texture* objTexture;
    SDL_Rect src_rect, dest_rect;
};