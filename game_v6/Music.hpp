#pragma once

#include "constants.hpp"
using namespace std;

class Music
{
public:

	Music();
	~Music();
	void playmusic(const char*, int);
	void playchannel(int, const char*, int);
};
