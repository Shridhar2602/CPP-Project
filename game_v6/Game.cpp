#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Background.hpp"
#include "Platform.hpp"
#include "Enemy.hpp"
#include "SDL2/SDL_mixer.h"
#include "Text.hpp"
#include <vector>
using namespace std;

Player* player1;
Background* background1;
Enemy* e1;

Mouse *mouse;
Button *button_play ;
Button *button_ins;
Button *button_back;
Button *button_exit;

vector<Platform*> ListOfPlatforms;

Text *score_text;
Text *life_text;

SDL_Renderer* Game::renderer = NULL;

Game::Game()
{

}

Game::~Game()
{

}

void Game::init(string title, int xpos, int ypos, int width, int height, bool fullscrean)
{
    // flag for fullscrean
    int flags = 0;

    if (fullscrean)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // if everything initialized 
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Subsystem Initialised!....." << endl;

        window = SDL_CreateWindow("Cuphead", xpos, ypos, width, height, flags);
        SDL_Surface *icon=IMG_Load("assets/icon.png");
        SDL_SetWindowIcon(window,icon);
        SDL_FreeSurface(icon);
        if (window)
            cout << "Window Created" << endl;

        if(TTF_Init() == -1)
            cout << "TTF init failed...." << endl;

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        // ERROR::WINDOW::NOTCREATED
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            cout << "Renderer Created!" << endl;
        }

        isRunning = true;
    }

    else
    {
        isRunning = false;
    }

    player1 = new Player();
    background1 = new Background();
    e1 = new Enemy(1);

    mouse = new Mouse();
    menu_background = TextureManager::LoadTexture("assets/BackGround3.png");
    menu_instruction = TextureManager::LoadTexture("assets/instruction.png");

    button_play = new Button(SCREEN_WIDTH / 2 - 135, 150, 271, 79, "assets/play4.png");
    button_ins = new Button(SCREEN_WIDTH / 2 - 300, 250, 605, 89, "assets/Instructions1.png");
    button_back = new Button(20, 20, 200, 81, "assets/back.jpg");



    score_text = new Text();
    score_text->set_rect(SCREEN_WIDTH - 250, 20, 200, 75);

    life_text = new Text();
    life_text->set_rect(SCREEN_WIDTH - 250, 100, 200, 75);

    //int disX = rand() % (SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 2);
    //int disY = rand() % (SCREEN_HEIGHT / 2) + 160;
    //platform1 = new Platform(disX, disY);
    fillPlatform();
    int n = sizeof(platforms) / sizeof(platforms[0]);
    for (int i = 0;i < n;i++) {
        ListOfPlatforms.push_back(new Platform(platforms[i][0], platforms[i][1], platforms[i][2], platforms[i][3]));
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_ESCAPE])
    {
        isRunning = false;
    }

    switch (event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update()
{

if(screen_type == GAME)
{
    background1->update();

    int CurrGround = 260;
    
    int n = sizeof(platforms) / sizeof(platforms[0]);
    //for (int i = 0;i < n;i++) {
    //    if((platforms[i][0] - distCovered) >= SCREEN_WIDTH && (platforms[i][0] - distCovered) >= -SCREEN_WIDTH)
    //        ListOfPlatforms.push_back(new Platform(platforms[i][0], platforms[i][1], platforms[i][2], platforms[i][3], platforms[i][4]));
    //}
    vector<int>::iterator it;
    for (auto it = ListOfPlatforms.begin(); it != ListOfPlatforms.end(); it++) {
        (*it)->update(&distCovered);
    }
    for (int i = 0;i < n;i++) {
        if (((SCREEN_WIDTH / 2) + distCovered >= platforms[i][0] + 80) && 
            (SCREEN_WIDTH / 2) + distCovered <= platforms[i][0] + platforms[i][2]) {
            CurrGround = platforms[i][1] + 121;
        }
    }

    player1->update(SCREEN_HEIGHT - CurrGround, &distCovered);
    e1->update(&distCovered);
    for(int i=0;i<player1->getBullets().size();i++)
    {
        SDL_bool collision=SDL_HasIntersection(e1->getdestrect(),&player1->getBullets()[i]->dest);
        if(collision)
        {
            e1->life--;
            Mix_Chunk* sound = Mix_LoadWAV("assets/hit.wav");
            Mix_PlayChannel(1, sound, 0);
            player1->getBullets()[i]->hit=true;

            score_str = "Score: ";
            score+=20;
            score_str.append(to_string(score));
            if(e1->life==0)
            {
                score_str = "Score: ";
                score+=50;
                score_str.append(to_string(score));
                e1->kill();
            }
        }
    }

    SDL_bool c2=SDL_HasIntersection(e1->getdestrect(),player1->getdestrect());
    
    if(invincible_period != 200)
        invincible_period--;
    if(invincible_period == 0)
        invincible_period = 200;

    if(c2)
    {
        //playeralive=false;
        if(life > 0 && invincible_period == 200)
        {
            life_str = "Life: ";
            life--;
            life_str.append(to_string(life));
            invincible_period--;
            cout << "dead" << endl;
        }
           
        else if(life <= 0)
        {
            m.playchannel(3, "assets/player_dead.wav", 0);
            playeralive = false;
        }
    }

    if(!playeralive)
    {
        //isRunning=false;
        screen_type = MAIN_MENU;
    }
}
}

void Game::render()
{
    SDL_RenderClear(renderer);

    if(screen_type == MAIN_MENU)
    {

        if(!(Mix_Playing(4)))
        {
            m.playchannel(4, "assets/menu.wav", -1);
            Mix_Volume(4, 128);
        }
        
        Mix_PauseMusic();
        SDL_RenderCopy(Game::renderer, menu_background, NULL, NULL);
        button_play->render_button();
        button_ins->render_button();

        if(button_play->isClicked(mouse))
        {
            screen_type = GAME;
        }

        if(button_ins->isClicked(mouse))
        {
            screen_type = INSTRUCTIONS;
        }
    }

    else if(screen_type == GAME)
    {
        // add stuff to render
        Mix_HaltChannel(4);
        Mix_ResumeMusic();
        background1->render();
        for (int i = 0;i < ListOfPlatforms.size();i++) 
        {
            if (ListOfPlatforms[i]->getPosX() - distCovered <= SCREEN_WIDTH || ListOfPlatforms[i]->getPosX() - distCovered <= -SCREEN_WIDTH) 
            {
                ListOfPlatforms[i]->render();
            }
        }
        //platform1->render();

        player1->render();
        e1->render();
        score_text->Render(score_str);
        life_text->Render(life_str);
    }

    else if(screen_type == INSTRUCTIONS)
    {
        SDL_RenderCopy(Game::renderer, menu_instruction, NULL, NULL);
        button_back->render_button();
        if(button_back->isClicked(mouse))
            screen_type = MAIN_MENU;
    }

    else if(screen_type == EXIT)
    {

    }

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    cout << "Game Cleaned" << endl;
}

bool Game::running()
{
    return isRunning;
}