#pragma once

#include "GameObject.hpp"
#include "constants.hpp"

class Background: public GameObject
{
    public:

        Background();
        ~Background();

        void update();
        void render();
};