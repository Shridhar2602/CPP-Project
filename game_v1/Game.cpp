#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
using namespace std;

GameObject *cuphead;
Map* map;

SDL_Renderer *Game::renderer = NULL;

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
    if(fullscrean)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // if everything initialized 
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Subsystem Initialised!....." << endl;

        window = SDL_CreateWindow("Cuphead", xpos, ypos, width, height, flags);

        if(window)
            cout << "Window Created" << endl;

        renderer = SDL_CreateRenderer(window, -1, 0);

        if(renderer)
        {   
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
            cout << "Renderer Created!" << endl; 
        }

        isRunning = true;
    }

    else
    {
        isRunning = false;
    }

    cuphead = new GameObject("assets/cuphead_run_shoot_0001.png", 0, 0);
    map = new Map();
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
    cuphead->Update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    map->DrawMap();
    // add stuff to render
    cuphead->Render();

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