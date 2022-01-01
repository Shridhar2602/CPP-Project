#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Background.hpp"
#include "Platform.hpp"
#include "Enemy.hpp"
#include "SDL2/SDL_mixer.h"
#include <vector>
using namespace std;

Player* player1;
Background* background1;
Enemy* e1;
vector<Platform*> ListOfPlatforms;

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
    e1=new Enemy(1);
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
            score+=20;
            if(e1->life==0)
            {
                score+=50;
                e1->kill();
            }
        }
    }
    SDL_bool c2=SDL_HasIntersection(e1->getdestrect(),player1->getdestrect());
    if(c2)
    {
        playeralive=false;
    }
    if(!playeralive)
    {
        isRunning=false;
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // add stuff to render
    background1->render();
    for (int i = 0;i < ListOfPlatforms.size();i++) {
        if (ListOfPlatforms[i]->getPosX() - distCovered <= SCREEN_WIDTH
            || ListOfPlatforms[i]->getPosX() - distCovered <= -SCREEN_WIDTH) {
            ListOfPlatforms[i]->render();
        }
    }
    //platform1->render();
    player1->render();
    e1->render();
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