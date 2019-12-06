#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "LTexture.h"
#include "Bullets.h"

using std::string;
using std::vector;

// FIXME: Add a collision detection funciton
// FIXME: Determine best way to handle collisions

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
	virtual void fire(vector<Bullets> *bullets, bool isPlayer);

	// Preforms the special attack
	virtual void fireSpecial();

	// Handles input
	virtual void handleInput(SDL_Event& e, vector<Bullets> *bullets, bool isPlayer = true);

	// Moves the ship
	virtual void move();

	// Checks if there's a collision from bullet
	bool hasCollided(vector<Bullets> *bullets);

	// Checks if there's a collision from another ship
	bool hasCollided(vector<Ship> *gShips);

	// Returns address to xVel
	int* getXVel();
	
	// Returns address to yVel
	int* getYVel();

	// Returns xcords
	int getXCords();

	// Returns ycords
	int getYCords();

	// Render the ship
	void render(SDL_Renderer* renderer);

	// General ship destructor
	virtual ~Ship();

private:
	LTexture mShip;
	int xCord, yCord, numSpecial;
	int xVel, yVel;
};

