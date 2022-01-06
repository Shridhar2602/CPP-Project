#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
    SDL_Surface* tempSurface = IMG_Load(texture);
    if (tempSurface == NULL)
        cout << "Unable to load image...." << endl;

    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}

SDL_Texture* TextureManager::LoadText(TTF_Font *f, string text, SDL_Color c)
{
    SDL_Surface* tempSurface = TTF_RenderText_Blended(f, text.c_str(), c);
    if (tempSurface == NULL)
    {
        //cout << "Unable to load text...." << TTF_GetError() << endl;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_NONE);
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}