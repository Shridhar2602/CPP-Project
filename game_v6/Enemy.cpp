#include "Enemy.hpp"

Enemy::Enemy(int eNo)
{
    e2=TextureManager::LoadTexture("assets/explosion.png");
    int ht=0;
    switch(eNo)
    {
        case 1:
        {
            setTexture("assets/woodpecker.png");
        }
        break;
        default:
            break;
    }
    setSrc(0,0,0,0);
    setDest(500+3*SCREEN_WIDTH/2,0,264,SCREEN_HEIGHT-200);
    setSpeed(6);
}
Enemy::~Enemy()
{
    
}
void Enemy::update(int *dist)
{
    keyboard_handler(dist);
    dest_rect.x=xpos;
    animate();
}
void Enemy::kill()
{
    dead=true;
}
void Enemy::keyboard_handler(int *dist) 
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        if (*dist > 0) {
            xpos += speed;
        }
    }

    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
            xpos -= speed;
    }
}
void Enemy::animate()
{
    if(!dead)
    {
        current_frame = (SDL_GetTicks() * animation_fps / 1000) % 17;
        src_rect.x=enemy1[current_frame][0];
        src_rect.y=enemy1[current_frame][1];
        dest_rect.w=src_rect.w=enemy1[current_frame][2]-2;
        dest_rect.h=src_rect.h=enemy1[current_frame][3]-2;
        dest_rect.y=enemy1[current_frame][4]+160;
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
void Enemy::render()
{
    if(!dead)
    {
        SDL_RenderCopyEx(Game::renderer,objTexture,&src_rect,&dest_rect,-90,NULL,SDL_FLIP_NONE);
    }
    else if(dead && !done)
    {
        SDL_RenderCopy(Game::renderer,e2,&src_rect,&dest_rect);
    }
}
int Enemy::getWidth()    { return width; }
int Enemy::getHeight()   { return height; }
int Enemy::getPosX()     { return xpos; }
int Enemy::getPosY()     { return ypos; }