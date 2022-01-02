#include "Button.hpp"

Button::Button(int x_pos, int y_pos, int width, int height, const char* image_path) 
{
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->width = width;
	this->height = height;

	dest.x = x_pos;
	dest.y = y_pos;
	dest.w = width;
	dest.h = height;

	tex = TextureManager::LoadTexture(image_path);
}

void Button::render_button() 
{
	SDL_RenderCopy(Game::renderer, tex, NULL, &dest);
}


bool Button::isOnButton(Mouse* m) 
{
	int mouse_x = m->get_mouse_x();
	int mouse_y = m->get_mouse_y();

	if ((mouse_x > this->x_pos) && (mouse_x < this->x_pos + this->width)) 
	{
		if ((mouse_y > this->y_pos) && (mouse_y < this->y_pos + this->height)) 
		{
			return true;
		}

		return false;
	}
	return false;
}

bool Button::isClicked(Mouse* m) 
{
	if (this->isOnButton(m) && m->isClicked()) 
	{
		return true;
	}

	return false;
}