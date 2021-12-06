#include "Sprites.hpp"

enum KeyPresses
{
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT
};

Sprites::Sprites()
{
    GameObject *cuphead = new GameObject("assets/cuphead_running.png", 1, true, true);
    cuphead->setDest(0, 676 - 155, 160, 162);
    cuphead->setSrc(0, 0, 138, 155);
    cuphead->setSpeed(8);

    GameObject *background = new GameObject("assets/background.png", 0, false, false);
    background->setDest(0, 0, 1800, 676);
    background->setSpeed(0);

    objects.push_back(background);
    objects.push_back(cuphead);
}

Sprites::~Sprites()
{

}

void Sprites::update()
{
    for(int i = 0; i < objects.size(); i++)
    {
        objects[i]->Update();
    }
}

void Sprites::render()
{
    for(int i = 0; i < objects.size(); i++)
    {
        objects[i]->Render();
    }
}

