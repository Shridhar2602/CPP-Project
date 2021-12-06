#include "Background.hpp"

Background::Background()
{
    setTexture("C:/Users/anura/Desktop/CppProject/testSDL/Source/assets/background.png");
    background2 = TextureManager::LoadTexture("C:/Users/anura/Desktop/CppProject/testSDL/Source/assets/b2.png");
    grass = TextureManager::LoadTexture("C:/Users/anura/Desktop/CppProject/testSDL/Source/assets/grass.png");
    sky = TextureManager::LoadTexture("C:/Users/anura/Desktop/CppProject/testSDL/Source/assets/sky1.png");

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
    // grass 1
    grass_src.x = 0;
    grass_src.y = 0;
    grass_src.w = SCREEN_WIDTH;
    grass_src.h = 255;
    grass_dest.x = 0;
    grass_dest.w = SCREEN_WIDTH;
    grass_dest.y = SCREEN_HEIGHT - 225;
    grass_dest.h = 225;
    // grass 2
    grass_src2.x = 0;
    grass_src2.y = 0;
    grass_src2.w = SCREEN_WIDTH;
    grass_src2.h = 255;
    grass_dest2.y = SCREEN_HEIGHT - 225;
    grass_dest2.h = 225;
}

void Background::update()
{
    keyboard_handler();

    grass_dest2.x = 2048 - grass_src.x;
    grass_src2.w = SCREEN_WIDTH - grass_dest2.x;
    grass_dest2.w = grass_src2.w;

    if (grass_offset == 1)
    {
        grass_dest.w = grass_src.w = SCREEN_WIDTH - grass_src2.w;
    }

    if (grass_src.x >= 2048)
    {
        grass_offset = 0;
        grass_init();
    }
}

void Background::keyboard_handler()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        src_rect.x -= speed;
        grass_src.x -= speed;
    }

    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        src_rect.x += speed;
        grass_src.x += speed;
    }

    if (grass_src.x >= (2048 - SCREEN_WIDTH))
        grass_offset = 1;

    if (grass_src.x < 0)
        grass_src.x = 0;


    /*
    if(xpos > SCREEN_WIDTH - dest_rect.w)
        xpos -= speed;
    if(xpos < 0)
        xpos = 0;
    */

}

void Background::render()
{
    SDL_RenderCopy(Game::renderer, sky, NULL, &sky_dest);
    //SDL_RenderCopy(Game::renderer, objTexture, &src_rect, &dest_rect);

    SDL_RenderCopy(Game::renderer, grass, &grass_src, &grass_dest);
    if (grass_offset == 1)
    {
        SDL_RenderCopy(Game::renderer, grass, &grass_src2, &grass_dest2);
        //cout << grass_dest2.x << endl;
    }
}