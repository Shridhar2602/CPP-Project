#include "Text.hpp"

Text::Text()
{
    Sans = TTF_OpenFont("assets/fonts/AlegreyaSansSC-Bold.ttf", 36);
    if(Sans == NULL)
        cout << "Failes to load font..." << endl;
    color = {0, 0, 0};
}

void Text::set_rect(int x, int y, int w, int h)
{
    dest_rect.x = x;
    dest_rect.y = y;
    dest_rect.w = w;
    dest_rect.h = h;
}

void Text::Render(string text)
{
    tex = TextureManager::LoadText(Sans, text, color);
    SDL_RenderCopy(Game::renderer, tex, NULL, &dest_rect);
}
