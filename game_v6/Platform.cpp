#include "GameObject.hpp"
#include "Platform.hpp"

Platform::Platform(int distX, int distY, int wd, int platNo) {
    int ht = 0;
    switch (platNo)
    {
    case 1:
    {
        setTexture("assets/platform1.png");
        wd = 432;
        ht = 188;
    }
        break;
    case 2:
    {
        setTexture("assets/platform2.png");
        wd = 700;
        ht = 570;
    }
    break;
    case 3:
    {
        setTexture("assets/platform3.png");
        wd = 545;
        ht = 200;
    }
    break;
    case 4:
    {
        setTexture("assets/platform4.png");
        wd = 748;
        ht = 183;
    }
    break;
    case 5:
    {
        setTexture("assets/platform5.png");
        wd = 700;
        ht = 570;
    }
    break;
    case 6:
    {
        setTexture("assets/wood-platform6.png");
        wd = 600;
        ht = 142;
    }
    break;
    case 7:
    {
        setTexture("assets/platform7.png");
        wd = 425;
        ht = 101;
    }
    break;
    case 8:
    {
        setTexture("assets/platform8.png");
        wd = 184;
        ht = 96;
    }
    break;
    default:
        break;
    }
    width = wd;
    height = ht;

    setSrc(0, 0, wd, ht);
    setDest(distX, SCREEN_HEIGHT - distY, wd, ht);

    //setDest(120, SCREEN_HEIGHT - 160, 350, 152);
    setSpeed(6);
}

Platform::~Platform() {

}

void Platform::update(int *dist) {
	keyboard_handler(dist);
	dest_rect.x = xpos;
	dest_rect.y = ypos;
}
void Platform::keyboard_handler(int *dist) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        if (*dist > 0) {
            xpos += speed;
        }
    }

    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
            xpos -= speed;
    }
}
void Platform::render() {
    SDL_RenderCopy(Game::renderer, objTexture, &src_rect, &dest_rect);
}

// getters
int Platform::getWidth()    { return width; }
int Platform::getHeight()   { return height; }
int Platform::getPosX()     { return xpos; }
int Platform::getPosY()     { return ypos; }