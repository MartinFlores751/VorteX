#pragma once
#include "LTexture.h"
#include <SDL.h>
#include <string>

using std::string;

class Ship
{
public:
	// General ship constructor
	Ship(int special = 0);

	// Initializes the ship
	bool init(SDL_Renderer* renderer = nullptr, string file = "");

	// Sets the x, y cords of the ship
	void setXY(int x, int y);

	// Default firemode
	virtual void fire();

	// Preforms the special attack
	virtual void fireSpecial();

	// Handles input
	virtual void handleInput(SDL_Event& e);

	// Moves the ship
	void move();

	// Render the ship
	void render(SDL_Renderer* renderer);

	// General ship destructor
	~Ship();

private:
	LTexture mShip;
	int xCord, yCord, numSpecial;
	int xVel, yVel;
};

