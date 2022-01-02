#pragma once

#include "constants.hpp"
#include "Mouse.hpp"
#include "TextureManager.hpp"
using namespace std;

class Button {
private:
	int x_pos;
	int y_pos;

	int width;
	int height;
	SDL_Texture *tex = NULL;
	SDL_Rect dest;

public:
	Button(int x_pos, int y_pos, int width, int height, const char* image_path);
	void render_button();
	bool isOnButton(Mouse* m); // returns if True if mouse is on the button
	bool isClicked(Mouse* m); // returs true if the Button is clicked

};