#include "GruntShip.h"
#include <stdlib.h>
#include <time.h>


GruntShip::GruntShip(){
	scanRadi = 0;
	numSpecial = 1;
}

void GruntShip::handleInput() {
	// Shoot once every 20 frames?


	// Create zig-zag function here


	// If player is in special range && score is so high
	// perform special
	if (inRange()) {
		srand(time(NULL));
		int hitChance = rand() % 100 + 1;
		if (hitChance >= 95)
			fireSpecial();
	}
}

void GruntShip::fireSpecial() {
	
}

bool GruntShip::inRange() {

}

GruntShip::~GruntShip(){

}
