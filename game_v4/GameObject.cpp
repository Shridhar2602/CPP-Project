#include "GameObject.hpp"
#include "TextureManager.hpp"

void GameObject::setTexture(const char* texturesheet)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
}

void GameObject::setSrc(int x, int y, int w, int h)
{
    src_rect.x = x;
    src_rect.y = y;
    src_rect.w = w;
    src_rect.h = h;
}

void GameObject::setDest(int x, int y, int w, int h)
{
    xpos = x;
    ypos = y;
    width = w;
    height = h;

    dest_rect.x = x;
    dest_rect.y = y;
    dest_rect.w = w;
    dest_rect.h = h;
}
