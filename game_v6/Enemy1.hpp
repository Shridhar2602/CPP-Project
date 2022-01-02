#pragma once
#include "constants.hpp"
#include "GameObject.hpp"
#include "TextureManager.hpp"
class Enemy1 : public GameObject
{
    public:
        Enemy1(int);
        ~Enemy1();
        void update(int *);
        void keyboard_handler(int *);
        void render();
        void animate();
        // getters
	    int getWidth();
	    int getHeight();
	    int getPosX();
	    int getPosY();
        void kill();
        int life=5;
    private: 
        SDL_Texture *e2;
        int width,height;
        SDL_Texture* enemy;
        int current_frame=0;
        int animation_fps=20;
        bool dead=false;
        bool done=false;
        int enemy1[12][5]=
        {
            {2,1088,246,104},
            {250,1088,246,104},
            {498,1088,246,104},
            {746,1088,246,104},
            {994,1088,246,104},
            {1242,1088,246,104},
            {1490,1088,246,104},
            {1738,1088,246,104},
            {1986,1088,246,104},
            {2234,1088,246,104},
            {2482,1088,246,104},
            {2730,1088,246,104}
        };
        int e[5][4]=
        {
            {60,194,88,170},
            {260,194,120,170},
            {448,194,172,170},
            {654,194,190,170},
            {850,194,200,170},
        };
};
