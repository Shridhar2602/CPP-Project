#include "Background.hpp"

Background::Background()
{

    /*
    * WINDOWS
    */
    grass = TextureManager::LoadTexture("C:/Users/anura/Desktop/CppProject/testSDL/Source/assets/grass.png");
    sky = TextureManager::LoadTexture("C:/Users/anura/Desktop/CppProject/testSDL/Source/assets/sky1.png");

    /*
    * lINUX
    */
    //grass = TextureManager::LoadTexture("assets/grass.png");
    //sky = TextureManager::LoadTexture("assets/sky1.png");

    bg.push_back(objTexture);
    bg.push_back(background2);

    grass_init();

    setDest(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    setSrc(0, 0, 900, 1000);
    setSpeed(6);

    // sky
    sky_src.x = 0;
    sky_src.y = 0;
    sky_src.w = SCREEN_WIDTH;
    sky_src.h = 255;
    sky_dest.x = 0;
    sky_dest.w = SCREEN_WIDTH;
    sky_dest.y = 0;
    sky_dest.h = SCREEN_HEIGHT;
}

void Background::grass_init()
{
    grass_src2.x = grass_src.x = 0;
    grass_src3.y = grass_src2.y = grass_src.y = 0;
    grass_src2.w = grass_src.w = SCREEN_WIDTH;
    grass_src3.h = grass_src2.h = grass_src.h = 255;
    grass_dest.x = 0;
    grass_dest.w = SCREEN_WIDTH;
    grass_dest3.y = grass_dest2.y = grass_dest.y = SCREEN_HEIGHT - 225;
    grass_dest3.h = grass_dest2.h = grass_dest.h = 225;

    grass_src3.x = 2048;
    grass_src3.w = 0;
}

void Background::update()
{
    keyboard_handler();

    if (grass_offset == 1)
    {
        grass_dest2.x = 2048 - grass_src.x;
        grass_src2.w = SCREEN_WIDTH - grass_dest2.x;
        grass_dest2.w = grass_src2.w;

        grass_dest.w = grass_src.w = SCREEN_WIDTH - grass_src2.w;
    }

    else if (grass_offset_backwards == 1)
    {
        grass_dest3.x = 0;
        grass_src3.x = 2048 - grass_dest.x;
        grass_src3.w = grass_dest3.w = grass_dest.x;

        grass_src.w = grass_dest.w = SCREEN_WIDTH - grass_dest.x;
        grass_src.x = 0;
    }

    if (grass_offset == 1 && (grass_src.x >= 2048 || grass_src.x == 0))
    {
        grass_offset = 0;
        grass_init();
    }

    else if (grass_offset_backwards == 1 && (grass_src3.x <= 0 || grass_src3.x >= 2048))
    {
        grass_offset_backwards = 0;
        grass_init();
    }
}

void Background::keyboard_handler()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        curr_dist -= speed;
        src_rect.x -= speed;
        grass_src.x -= speed;
    }

    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        curr_dist += speed;
        src_rect.x += speed;
        grass_src.x += speed;

        if (grass_offset_backwards == 1)
        {
            grass_dest.x -= speed;
        }
    }

    if (grass_src.x >= (2048 - SCREEN_WIDTH))
        grass_offset = 1;

    if (grass_src.x < 0)
    {
        grass_src.x = 0;

        if (curr_dist > 0)
        {
            grass_offset_backwards = 1;
            grass_dest.x += speed;
        }
    }
}

void Background::render()
{
    SDL_RenderCopy(Game::renderer, sky, NULL, &sky_dest);
    //SDL_RenderCopy(Game::renderer, objTexture, &src_rect, &dest_rect);

    SDL_RenderCopy(Game::renderer, grass, &grass_src, &grass_dest);
    if (grass_offset == 1)
    {
        SDL_RenderCopy(Game::renderer, grass, &grass_src2, &grass_dest2);
    }

    else if (grass_offset_backwards == 1)
    {
        SDL_RenderCopy(Game::renderer, grass, &grass_src3, &grass_dest3);
    }
}