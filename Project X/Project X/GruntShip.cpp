#include "GruntShip.h"
#include <stdlib.h>
#include <time.h>


GruntShip::GruntShip(){
	scanRadi = 0;
	numSpecial = 1;
}

void GruntShip::handleInput() {
	static int counter = 0;
	srand(time(NULL));
	// Shoot once every 20 frames?
	// Relying on VSync... Tsk tsk...
	if (++counter >= 20) {
		counter = 0;
		fire();
	}

	// Create zig-zag function here
	if (!isMoving) {
		// Move from 1 px to the other side of the screen
		int movPixels = rand() % 144 + 1;
		
		// Move left or right?
		movLeft ? false : true;
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
	
}

bool GruntShip::inRange() {
	// Do a basic circualr collison here to determin if player is within blast radius
}

GruntShip::~GruntShip(){

}
