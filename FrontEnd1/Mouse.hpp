#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include<iostream>
#include<inttypes.h>

using namespace std;


class Mouse {
private:
	int x_pos;
	int y_pos;


public:
	int get_mouse_x();
	int get_mouse_y();
	bool isClicked(); // only Left click can be detected


};