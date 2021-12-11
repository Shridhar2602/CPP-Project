#include "Player.hpp"
#include <math.h>
#include <algorithm>
#include <SDL_mixer.h>

Player::Player()
{
    /*
    * WINDOWS (change path of image accordingly)
    */
    setTexture("D:/IIITB/COURSE/SEM 3/ESS 201-Programming II/CPPproj/Cuphead/assets/cuphead_idle_2.png");
    tex_running = TextureManager::LoadTexture("D:/IIITB/COURSE/SEM 3/ESS 201-Programming II/CPPproj/Cuphead/assets/cuphead_running.png");
    tex_jumping = TextureManager::LoadTexture("D:/IIITB/COURSE/SEM 3/ESS 201-Programming II/CPPproj/Cuphead/assets/cuphead_jump.png");
    tex_bullets = TextureManager::LoadTexture("D:/IIITB/COURSE/SEM 3/ESS 201-Programming II/CPPproj/Cuphead/assets/Bullets.png");
    tex_idle_shooting = TextureManager::LoadTexture("D:/IIITB/COURSE/SEM 3/ESS 201-Programming II/CPPproj/Cuphead/assets/cuphead_idle_shoot2.png");

    /*
    * LINUX
    */
    //setTexture("assets/cuphead_idle_2.png");
    //tex_running = TextureManager::LoadTexture("assets/cuphead_running.png");
    //tex_jumping = TextureManager::LoadTexture("assets/cuphead_jump.png");
    //tex_bullets = TextureManager::LoadTexture("assets/Bullets.png");
    //tex_idle_shooting = TextureManager::LoadTexture("assets/cuphead_idle_shoot.png");

    setSrc(0, 0, 0, 0);
    setDest(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 225, 128, 128);
    setSpeed(0);

    SDL_Init(SDL_INIT_AUDIO);

    int audio_rate = MIX_DEFAULT_FREQUENCY;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 2048;

    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
    {
        cout << "Couldn't initialise audio:" << Mix_GetError() << endl;
        exit(0);
    }
}

void Player::update(int ground, int* dist)
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

        case SHOOT_IDLE:
            animate_shoot_idle();
            break;
        }
    }

    else {
        animate_jump();

        float t = 0.26, g = GRAVITY;
        ypos -= (currVelocity * t) - ((1 / 2) * g * t * t);
        currVelocity -= g * t;

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
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        animate_bullet(bullets[i]);
    }


    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->dest.x >= SCREEN_WIDTH || bullets[i]->dest.x <= 0)
        {
            bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets[i]), bullets.end());
        }
    }
}


void Player::keyboard_handler(int* dist)
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    bool jumpPressed = false;
    
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        last_direction = animate_type = RUN_LEFT;
        xpos -= speed;
        if (*dist > 0)
            *dist -= 6;
    }

    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        last_direction = animate_type = RUN_RIGHT;
        xpos += speed;
        *dist += 6;
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
        if (!currentKeyStates[SDL_SCANCODE_X])
        {
            animate_type = IDLE;
        }

        else
        {
            animate_type = SHOOT_IDLE;
        }
    }

    if (currentKeyStates[SDL_SCANCODE_X])
    {
        if (bullet_count_limiter == 1)
        {
            bullet_animation = 1;

            bullet* b = new bullet;
            b->direction = last_direction;

            if (last_direction == RUN_RIGHT)
            {
                b->dest.x = dest_rect.x + 110;
                b->dest.y = dest_rect.y + 80;
            }

            else
            {
                b->dest.x = dest_rect.x - bullet_loop[current_frame][2];
                b->dest.y = dest_rect.y + 80;
            }

            bullets.push_back(b);
        }

        bullet_count_limiter++;

        if (bullet_count_limiter == 20)
            bullet_count_limiter = 1;

        playsound("D:/IIITB/COURSE/SEM 3/ESS 201-Programming II/CPPproj/Cuphead/assets/bullet.wav");

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

void Player::animate_shoot_idle()
{
    current_frame = (SDL_GetTicks() * animation_fps / 1400) % 3;

    src_rect.x = player_shoot_idle[current_frame][0];
    src_rect.y = 0;
    dest_rect.w = src_rect.w = player_shoot_idle[current_frame][1];
    dest_rect.h = src_rect.h = player_shoot_idle[current_frame][2];
}

void Player::animate_bullet(bullet* b)
{
    current_frame = (SDL_GetTicks() * animation_fps / 1000) % 8;

    bullet_src.x = bullet_loop[current_frame][0];
    bullet_src.y = bullet_loop[current_frame][1];
    b->dest.w = bullet_src.w = bullet_loop[current_frame][2];
    b->dest.h = bullet_src.h = bullet_loop[current_frame][3];

    if (b->direction == RUN_RIGHT)
    {
        b->dest.x += 12;
    }

    else
    {
        b->dest.x -= 12;
    }
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

        case SHOOT_IDLE:

            switch (last_direction)
            {
            case RUN_RIGHT:
                SDL_RenderCopy(Game::renderer, tex_idle_shooting, &src_rect, &dest_rect);
                break;

            case RUN_LEFT:
                SDL_RenderCopyEx(Game::renderer, tex_idle_shooting, &src_rect, &dest_rect, 0, NULL, SDL_FLIP_HORIZONTAL);
                break;
            }

            break;

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


    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->direction == RUN_RIGHT)
        {
            SDL_RenderCopy(Game::renderer, tex_bullets, &bullet_src, &bullets[i]->dest);
        }

        else
        {
            SDL_RenderCopyEx(Game::renderer, tex_bullets, &bullet_src, &bullets[i]->dest, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
}

int Player::getYpos()
{
    return ypos;
}


void Player::playsound(const char* path)
{
    Mix_Chunk* sound = Mix_LoadWAV(path);
    if (sound == nullptr)
    {
        cout << "Couldn't init audio:" << Mix_GetError()<<endl;
    }
    Mix_PlayChannel(-1, sound, 0);

}
