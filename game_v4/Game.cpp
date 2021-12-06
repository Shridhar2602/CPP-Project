#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Background.hpp"
#include "Platform.hpp"

#include <vector>
using namespace std;

Player* player1;
Background* background1;
//Platform* platform1;
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
    //int disX = rand() % (SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 2);
    //int disY = rand() % (SCREEN_HEIGHT / 2) + 160;
    //platform1 = new Platform(disX, disY);
    int n = sizeof(platforms) / sizeof(platforms[0]);
    for (int i = 0;i < n;i++) {
        int disX = rand() % (SCREEN_WIDTH * 10) + (SCREEN_WIDTH / 2);
        int disY = rand() % ((SCREEN_HEIGHT / 2) - 160) + 160;
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
    //platform1->update();

    int CurrGround = 260;

    int n = sizeof(platforms) / sizeof(platforms[0]);
    vector<int>::iterator it;
    for (auto it = ListOfPlatforms.begin(); it != ListOfPlatforms.end(); it++) {
        (*it)->update(&distCovered);
    }

    for (int i = 0;i < n;i++) {
        if (((SCREEN_WIDTH / 2) + distCovered >= platforms[i][0] + 80) && (SCREEN_WIDTH / 2) + distCovered <= platforms[i][0] + platforms[i][2]) {
            CurrGround = platforms[i][1] + platforms[i][3];
            cout << "GROUND CHANGED " << CurrGround << endl;
        }
    }

    player1->update(SCREEN_HEIGHT - CurrGround + 60, &distCovered);
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // add stuff to render
    background1->render();
    for (int i = 0;i < ListOfPlatforms.size();i++) {
        ListOfPlatforms[i]->render();
    }
    //platform1->render();
    player1->render();

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