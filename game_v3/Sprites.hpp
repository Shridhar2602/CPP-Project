#pragma once 

#include "GameObject.hpp"
#include <vector>

class Sprites
{
    private:
        vector <GameObject *> objects;

    public:
        Sprites();
        ~Sprites();

        void update();
        void render();
};