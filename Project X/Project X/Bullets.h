#pragma once
#include "LTexture.h"

class Bullets
{
public:
	// Set X, Y cords
	Bullets(int x, int y);

	// Render the bullet to the screen
	void render(SDL_Renderer* renderer);

	// ???
	~Bullets();
private:
	int xAxis, yAxis;
	LTexture missile;
};

