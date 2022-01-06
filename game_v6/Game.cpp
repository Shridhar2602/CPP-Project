#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Background.hpp"
#include "Platform.hpp"
#include "Enemy.hpp"
#include "SDL2/SDL_mixer.h"
#include "Text.hpp"
#include "Enemy1.hpp"
#include <vector>
using namespace std;

Player* player1;
Background* background1;
vector<Enemy*> e1;
Enemy1* e2;

Mouse *mouse;
Button *button_play ;
Button *button_ins;
Button *button_back;
Button *button_exit;

Leaderboard *lb;

vector<Platform*> ListOfPlatforms;

Text *score_text;
Text *life_text;

SDL_Renderer* Game::renderer = NULL;

Game::Game()
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
    for(int i=0;i<sizeof(l1)/sizeof(l1[0]);i++)
    {
        Enemy *x=new Enemy(1,l1[i]);
        e1.push_back(x);
    }
    e2 = new Enemy1(1);
    mouse = new Mouse();
    menu_background = TextureManager::LoadTexture("assets/BackGround3.png");
    menu_instruction = TextureManager::LoadTexture("assets/instruction.png");
    

    button_play = new Button(SCREEN_WIDTH / 2 - 135, 150, 271, 79, "assets/play4.png");
    button_ins = new Button(SCREEN_WIDTH / 2 - 300, 250, 605, 89, "assets/Instructions1.png");
    button_back = new Button(20, 20, 200, 81, "assets/back.jpg");

    lb = new Leaderboard();

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
        for(int i=0;i<e1.size();i++)
        {
            e1[i]->update(&distCovered);
        }
        e2->update(&distCovered);
        if(e2->getdestrect()->x<-100)
        {
            e2->setDest(10000,SCREEN_HEIGHT-225+20,264,SCREEN_HEIGHT-200);
        }
        vector <SDL_Rect> comv;
        for(int i=0;i<e1.size();i++)
        {
            SDL_Rect tc=*e1[i]->getdestrect();
            tc.w -= 651;
            tc.x+=330;
            tc.h+=80;
            comv.push_back(tc);
            
        }
        for(int i=0;i<player1->getBullets().size();i++)
        {
            for(int j=0; j<e1.size();j++)
            {
                SDL_bool collision=SDL_HasIntersection(&comv[j],&player1->getBullets()[i]->dest);
                if(collision)
                {
                    e1[j]->life--;
                    m.playchannel(6, "assets/hit.wav", 0);
                    player1->getBullets()[j]->hit=true;
                    score_str = "Score: ";
                    //score+=20;
                    score_str.append(to_string(score));
                    if(e1[j]->life==0)
                    {
                        score_str = "Score: ";
                        score+=250;
                        score_str.append(to_string(score));
                        e1[j]->kill();
                        e1.erase(e1.begin()+j);
                        e1.push_back(new Enemy(1,e1[0]->getdestrect()->x+15000));
                    }
                }
            }
        }
        for(int i=0;i<e1.size();i++)
        {
            SDL_bool c2=SDL_HasIntersection(&comv[i],player1->getdestrect());
            if(invincible_period != 600)
                invincible_period--;
            if(invincible_period == 0)
                invincible_period = 600;

            if(c2)
            {
                //playeralive=false;
                if(life > 0 && invincible_period == 600)
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
        }
        SDL_bool c3=SDL_HasIntersection(e2->getdestrect(),player1->getdestrect());
        if(invincible_period != 600)
            invincible_period--;
        if(invincible_period == 0)
            invincible_period = 600;

        if(c3)
        {
            //playeralive=false;
            if(life > 0 && invincible_period == 600)
            {
                life_str = "Life: ";
                life--;
                m.playchannel(5, "assets/player_hit.wav", 0);
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
            screen_type = LEADERBOARD;
        }
    }

    else if(screen_type == LEADERBOARD)
        lb->update();
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
        for(int i=0;i<e1.size();i++)
        {
            e1[i]->render();
        }

        e2->render();

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

    else if(screen_type == LEADERBOARD)
    {
        Mix_PauseMusic();

        if(!(Mix_Playing(4)))
        {
            m.playchannel(4, "assets/menu.wav", -1);
            Mix_Volume(4, 128);
        }

        background1->render_leaderboard();
        lb->render(score);
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

Game::~Game()
{
    // delete player1;
    // delete background1;
    // delete e2;
    // delete mouse;
    // delete button_play;
    // delete button_ins;
    // delete button_back;
    // delete button_exit;
    // delete lb;
    // delete score_text;
    // delete life_text;
}