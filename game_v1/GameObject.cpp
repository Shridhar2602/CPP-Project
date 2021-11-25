#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char *texturesheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);

    xpos = x;
    ypos = y;
}

void GameObject::Update()
{
    xpos++;
    ypos++;

    src_rect.h = 64;
    src_rect.w = 64;
    src_rect.x = 0;
    src_rect.y = 0;

    dest_rect.x = xpos;
    dest_rect.y = ypos;
    dest_rect.w = src_rect.w * 2;
    dest_rect.h = src_rect.h * 2;
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, NULL, &dest_rect);
}