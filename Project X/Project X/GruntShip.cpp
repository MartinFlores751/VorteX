#include "GruntShip.h"
#include "core.h"
#include <stdlib.h>
#include <time.h>


GruntShip::GruntShip(){
	scanRadi = numMoves = 0;
	numSpecial = 1;
	isMoving = movLeft = false;
}

void GruntShip::handleInput([[maybe_unused]] SDL_Event& e, vector<Bullets> *bullets, bool isPlayer) {
	static int counter = 0;
	srand(time(NULL));
	// Stable but do something better...
	if (++counter >= 20) {
		counter = 0;
		fire(bullets, isPlayer);
	}

	// Create zig-zag function here
	if (!isMoving) {
		// Move from VELOCITY to the other side of the screen
		numMoves = rand() % (144 / VELOCITY) + 1;
		
		// Move left or right?
		movLeft = movLeft ? false : true;

		// Set moving states
		isMoving = true;
	}

	// If player is in special range && score is so high
	// perform special
	if (inRange()) {
		int hitChance = rand() % 100 + 1;
		if (hitChance >= 95)// ADD: add score here!
			fireSpecial();
	}
}

void GruntShip::fireSpecial() {
	// Initate self destruct sequence
}

void GruntShip::aiMove() {
	// Make an oops moment, upcasting to call
	// over move function...
	if (isMoving) {
		if (numMoves > 0) {
			// Retrive needed variables and dec counter
			int* xVel = getXVel();
			int* yVel = getYVel();
			--numMoves;

			// Set the darn thing to actually move down
			*yVel = VELOCITY;

			// Move left or right
			if (movLeft)
				*xVel = -VELOCITY;
			else
				*xVel = VELOCITY;

			// This is stupid, will fix later... >.<
			move();
		}
		else
			isMoving = false;
	}
}

bool GruntShip::inRange() {
	// Do a basic circualr collison here to determin if player is within blast radius
	// Temp thing
	return false;
}
