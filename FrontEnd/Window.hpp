#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include<iostream>

using namespace std;


class Window
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;


public:
    Window(const char* title, int w, int h);
    void cleanUp();
    SDL_Texture* loadTexture(const char* file_path);
    void clear();
    void Render_texture(SDL_Texture* tex);
    void Render_texture(SDL_Texture* tex, int x, int y, int width, int height);
    void display();

    // getter
    SDL_Window* get_window() {
        return this->window;
    }
    SDL_Renderer* get_renderer() {
        return this->renderer;
    }

};
