#pragma once

#include "constants.hpp"
#include <SDL_mixer.h>
using namespace std;


class Music
{
public:

	Music();
	~Music();
	void playmusic(const char*, bool);
};
