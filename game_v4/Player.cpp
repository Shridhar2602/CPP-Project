#include "Player.hpp"
#include <math.h>

Player::Player()
{
    setTexture("C:/Users/anura/Desktop/CppProject/testSDL/Source/assets/cuphead_idle_2.png");
    tex_running = TextureManager::LoadTexture("C:/Users/anura/Desktop/CppProject/testSDL/Source/assets/cuphead_running.png");
    tex_jumping = TextureManager::LoadTexture("C:/Users/anura/Desktop/CppProject/testSDL/Source/assets/cuphead_jump.png");

    setSrc(0, 0, 0, 0);
    setDest(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT - 225, 128, 128);
    setSpeed(0);
}

void Player::update(int ground, int *dist)
{
    keyboard_handler(dist);
    dest_rect.x = xpos;
    dest_rect.y = ypos;

    if (jump_frame_count < 0)
    {
        switch (animate_type)
        {
        case IDLE:
            animate_idle();
            break;

        case JUMP_IDLE:
            animate_jump();
            break;

        case RUN_LEFT:
            animate_run();
            break;

        case RUN_RIGHT:
            animate_run();
            break;
        }
    }

    //else
    //{
    //    animate_jump();

    //    if (jump_frame_count < 25) {
    //        ypos -= 10;
    //        cout << "Jump : " << ypos << endl;
    //    }

    //    else if (jump_frame_count > 36) {
    //        ypos += 10;
    //        cout << "Jump : " << ypos << endl;
    //        if (ypos >= ground) {
    //            ypos = ground;
    //            cout << "Successfully Changed" << endl;
    //        }
    //    }

    //    if (jump_frame_count == 60)
    //        jump_frame_count = -1;
    //}
    else {
        animate_jump();

        float t = 0.26, g = GRAVITY;
        ypos -= (currVelocity * t) - ((1 / 2) * g * t * t);
        currVelocity -= g * t;
        cout << "YPos: " << ypos << " Vel: " << currVelocity << endl;

        if (ypos - 193 > ground) {
            ground = SCREEN_HEIGHT - 200;
        }
        if (ypos >= ground && currVelocity < 0 && ypos - 193 < ground) {
            currVelocity = 0;
            ypos = ground;
        }
        
        if (jump_frame_count == 63)
            jump_frame_count = -1;
    }
    if (animate_type != JUMP_IDLE) {
        if (ypos < ground) {
            float t = 0.26, g = GRAVITY;
            ypos -= (currVelocity * t) - ((1 / 2) * g * t * t);
            currVelocity -= g * t;
        }
        //if (ypos >= ground) {
        //    currVelocity = 0;
        //    ypos = ground;
        //}
    }
}

void Player::keyboard_handler(int *dist)
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    bool jumpPressed = false;

    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        last_direction = animate_type = RUN_LEFT;
        xpos -= speed;
        if(*dist > 0)
            *dist -= 6;
        std::cout << "D: " << *dist << std::endl;
        //cout << "X: " << xpos << endl;
    }

    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        last_direction = animate_type = RUN_RIGHT;
        xpos += speed;
        *dist += 6;
        std::cout << "D: " << *dist << std::endl;
        //cout << "X: " << xpos << endl;
    }

    if (currentKeyStates[SDL_SCANCODE_Z])
    {
        if (jump_frame_count == -1) {
            currVelocity = 77.45;
            jump_frame_count = 0;
        }
        animate_type = JUMP_IDLE;
    }

    if (!currentKeyStates[SDL_SCANCODE_RIGHT] && !currentKeyStates[SDL_SCANCODE_LEFT] && !currentKeyStates[SDL_SCANCODE_Z])
    {
        animate_type = IDLE;
    }

    if (xpos > SCREEN_WIDTH / 2)
        xpos -= speed;
    if (xpos < 0)
        xpos = 0;
}

void Player::animate_idle()
{
    current_frame = (SDL_GetTicks() * animation_fps / 1000) % 5;

    src_rect.x = player_idle[current_frame][0];
    src_rect.y = 0;
    dest_rect.w = src_rect.w = player_idle[current_frame][1];
    dest_rect.h = src_rect.h = player_idle[current_frame][2];
}

void Player::animate_run()
{
    current_frame = (SDL_GetTicks() * animation_fps / 1000) % 16;

    src_rect.x = player_running[current_frame][0];
    src_rect.y = 0;
    dest_rect.w = src_rect.w = player_running[current_frame][1];
    dest_rect.h = src_rect.h = player_running[current_frame][2];
}

void Player::animate_jump()
{
    current_frame = (SDL_GetTicks() * 25 / 1000) % 8;

    src_rect.x = player_jump[current_frame][0];
    src_rect.y = 0;
    dest_rect.w = src_rect.w = player_jump[current_frame][1];
    dest_rect.h = src_rect.h = player_jump[current_frame][2];

    jump_frame_count++;
}

void Player::render()
{
    if (jump_frame_count < 0)
    {
        switch (animate_type)
        {
        case IDLE:

            switch (last_direction)
            {
            case RUN_RIGHT:
                SDL_RenderCopy(Game::renderer, objTexture, &src_rect, &dest_rect);
                break;

            case RUN_LEFT:
                SDL_RenderCopyEx(Game::renderer, objTexture, &src_rect, &dest_rect, 0, NULL, SDL_FLIP_HORIZONTAL);
                break;
            }

            break;
            /*
            case JUMP_IDLE:
                SDL_RenderCopy(Game::renderer, tex_jumping, &src_rect, &dest_rect);
                break;
            */

        case RUN_RIGHT:
            SDL_RenderCopy(Game::renderer, tex_running, &src_rect, &dest_rect);
            break;

        case RUN_LEFT:
            SDL_RenderCopyEx(Game::renderer, tex_running, &src_rect, &dest_rect, 0, NULL, SDL_FLIP_HORIZONTAL);
            break;
        }
    }

    else
        SDL_RenderCopy(Game::renderer, tex_jumping, &src_rect, &dest_rect);
}

int Player::getYpos() {
    return ypos;
}