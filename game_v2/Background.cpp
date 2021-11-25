#include "Background.hpp"

Background::Background()
{
    setTexture("assets/background.png");
    setDest(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Background::update()
{
    ;
}

void Background::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, NULL, &dest_rect);
}