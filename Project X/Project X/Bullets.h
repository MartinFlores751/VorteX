#pragma once
#include "LTexture.h"

using std::string;

class Bullets
{
public:
	// init X, Y cords
	Bullets(int x = -8, int y = -8, bool fromP = false);

	// Set x, y cords
	void setXY(int x, int y, bool fromP);

	// Render the bullet to the screen
	void render(SDL_Renderer* renderer);

	// Moves the bullet
	void move();

	// Initialize the bullet texture
	bool init(SDL_Renderer * renderer, string path);

	// Returns if the bullet is on screen or not
	bool isOnScreen();

	// Return x cord
	int getXCord();

	// Return y cord
	int getYCord();

private:
	bool onScreen;
	bool fromPlayer;
	int xAxis, yAxis;
	LTexture missile;
};

