#pragma once
#include "Ship.h"
class PlayerShip :
	public Ship
{
public:
	PlayerShip(int numSpecials);
	~PlayerShip();

private:
	int mNumLives;
};

