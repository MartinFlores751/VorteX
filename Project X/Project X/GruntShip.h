#pragma once
#include "Ship.h"
class GruntShip :
	public Ship
{
public:
	GruntShip();

	// Handle events differnently
	virtual void handleInput();

	

	// Self-Destruct! SH-BOOM!
	virtual void fireSpecial();

	// Checks if player is in range
	bool inRange();

	~GruntShip();

private:
	int scanRadi; // The special ranged attack
	int numSpecial;
	bool isMoving;
	bool movLeft;
};

