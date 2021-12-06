#include "GameObject.hpp"
#include "Platform.hpp"

Platform::Platform(int distX, int distY, int wd, int ht) {
    // 120 , 160
	setTexture("C:/Users/anura/Desktop/CppProject/testSDL/Source/assets/Platform1.png");
    setSrc(0, 0, 432, 188);
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
            cout << "Distance = " << *dist << endl;
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