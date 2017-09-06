#pragma once
#include "Ship.h"
#include <SDL.h>
class PlayerShip :
	public Ship
{
public:
	PlayerShip(int numSpecials);
	~PlayerShip();

private:
	Uint8 mNumLives;
};

