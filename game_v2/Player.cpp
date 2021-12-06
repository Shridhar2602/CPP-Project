#include "Player.hpp"

Player::Player()
{
    setTexture("assets/cuphead_idle_2.png");
    tex_running = TextureManager::LoadTexture("assets/cuphead_running.png");
    tex_jumping = TextureManager::LoadTexture("assets/cuphead_jump.png");

    setSrc(0, 0, 0, 0);
    setDest(120, SCREEN_HEIGHT - 160, 128, 128);
    setSpeed(6);
}

void Player::update()
{
    keyboard_handler();
    dest_rect.x = xpos;
    dest_rect.y = ypos;
    
    if(jump_frame_count < 0)
    {
        switch(animate_type)
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

    else
    {
        animate_jump();

        if(jump_frame_count < 25)
            ypos -= 5;

        else if(jump_frame_count > 36)
            ypos += 5;

        if(jump_frame_count == 60)
            jump_frame_count = -1;
    }
    
}

void Player::keyboard_handler()
{
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if(currentKeyStates[SDL_SCANCODE_LEFT])
        {
            last_direction = animate_type = RUN_LEFT;
            xpos -= speed;
        }

        if(currentKeyStates[SDL_SCANCODE_RIGHT])
        {
            last_direction = animate_type = RUN_RIGHT;
            xpos += speed;
        }

        if(currentKeyStates[SDL_SCANCODE_Z])
        {
            if(jump_frame_count == -1)
                jump_frame_count = 0;

            animate_type = JUMP_IDLE;
        }

        if(!currentKeyStates[SDL_SCANCODE_RIGHT] && !currentKeyStates[SDL_SCANCODE_LEFT] && !currentKeyStates[SDL_SCANCODE_Z])
        {
            animate_type = IDLE;
        }

        if(xpos > SCREEN_WIDTH - dest_rect.w)
            xpos -= speed;
        if(xpos < 0)
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
    if(jump_frame_count < 0)
    {
        switch(animate_type)
        {      
            case IDLE:

                switch(last_direction)
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