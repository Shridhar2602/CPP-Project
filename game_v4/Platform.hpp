#pragma once

#include "constants.hpp"

class Platform : public GameObject {
public:
	Platform(int , int, int, int);
	//Platform();
	~Platform();

	void update(int *);
	void keyboard_handler(int *);
	void render();

	// getters
	int getWidth();
	int getHeight();
	int getPosX();
	int getPosY();

private:
	int width, height;
	SDL_Texture* platform;
};