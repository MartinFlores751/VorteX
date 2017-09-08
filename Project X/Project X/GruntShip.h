#pragma once
#include "Ship.h"
class GruntShip :
	public Ship
{
public:
	GruntShip();

	// Handle events differnently
	virtual void handleInput();

	virtual void fireSpecial();

	// Checks if player is in range
	bool inRange();

	~GruntShip();

private:
	int scanRadi; // The special ranged
	int numSpecial;
};

