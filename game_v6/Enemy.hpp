#pragma once
#include "constants.hpp"
#include "GameObject.hpp"
#include "TextureManager.hpp"
class Enemy : public GameObject
{
    public:
        Enemy(int,int);
        ~Enemy();
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
        int life=100;
    private: 
        SDL_Texture *e2;
        int width,height;
        SDL_Texture* enemy;
        int current_frame=0;
        int animation_fps=20;
        bool dead=false;
        bool done=false;
        int enemy1[17][5]=
        {
            {2,18,918,267,-200},
            {922,18,918,267,-160},
            {1842,18,918,267,-120},
            {2762,18,918,267,-80},
            {2,303,936,294,-40},
            {940,303,936,294,0},
            {1878,303,936,294,40},
            {2,615,959,310,80},
            {963,615,959,310,120},
            {1924,615,959,310,80},
            {2885,615,959,310,40},
            {2,959,922,325,0},
            {926,959,922,325,-40},
            {1850,959,922,325,-80},
            {2774,959,922,325,-120},
            {2,1286,922,324,-160},
            {926,1286,922,324,-200}
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
