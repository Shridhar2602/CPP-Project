#pragma once
#include "Game.hpp"
#include "TextureManager.hpp"

class Map
{
public:
    Map();
    ~Map();

    void LoadMap(int arr[50][50]);
    void DrawMap();

private:
    SDL_Rect src, dest;

    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;

    int map[50][50];
};