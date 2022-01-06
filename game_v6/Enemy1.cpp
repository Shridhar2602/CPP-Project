#include "Enemy1.hpp"

Enemy1::Enemy1(int eNo)
{
    e2=TextureManager::LoadTexture("assets/explosion.png");
    int ht=0;
    switch(eNo)
    {
        case 1:
        {
            setTexture("assets/seadog.png");
        }
        break;
        default:
            break;
    }
    setSrc(0,0,0,0);
    setDest(5000,SCREEN_HEIGHT-225+20,264,SCREEN_HEIGHT-200);
    setSpeed(4);
}
Enemy1::~Enemy1()
{

}
void Enemy1::update(int *dist)
{
    keyboard_handler(dist);
    xpos-=(speed);
    dest_rect.x=xpos;
    animate();
}
void Enemy1::kill()
{
    dead=true;
}
void Enemy1::keyboard_handler(int *dist) 
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    //if (currentKeyStates[SDL_SCANCODE_LEFT])
    //{
    //    if (*dist > 0) {
    //        xpos += speed;
    //    }
    //}

    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
            xpos -= (speed + 2);
    }
}
void Enemy1::animate()
{
    if(!dead)
    {
        current_frame = (SDL_GetTicks() * animation_fps / 1000) % 12;
        src_rect.x=enemy1[current_frame][0];
        src_rect.y=enemy1[current_frame][1];
        dest_rect.w=src_rect.w=enemy1[current_frame][2]-15;
        dest_rect.h=src_rect.h=enemy1[current_frame][3]-15;
    }
    if(dead)
    {
        animation_fps=10;
        current_frame = (SDL_GetTicks() * animation_fps / 1000) % 5;
        src_rect.x=e[current_frame][0];
        src_rect.y=e[current_frame][1];
        dest_rect.w=src_rect.w=e[current_frame][2];
        dest_rect.h=src_rect.h=e[current_frame][3];
        if(current_frame==4)
        {
            done=true;
        }
    }

}
void Enemy1::render()
{
    if(!dead)
    {
        SDL_RenderCopyEx(Game::renderer,objTexture,&src_rect,&dest_rect,0,NULL,SDL_FLIP_NONE);
    }
    else if(dead && !done)
    {
        SDL_RenderCopy(Game::renderer,e2,&src_rect,&dest_rect);
    }
}
int Enemy1::getWidth()    { return width; }
int Enemy1::getHeight()   { return height; }
int Enemy1::getPosX()     { return xpos; }
int Enemy1::getPosY()     { return ypos; }