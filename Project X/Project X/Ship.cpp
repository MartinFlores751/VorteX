#include "Ship.h"
#include "core.h"
#include <stdio.h>
#include <string>
#include <vector>

using std::vector;
using std::string;

Ship::Ship(int special){
	// Initialize all variables
	xCord = yCord = xVel = yVel = 0;
	numSpecial = special;
}

bool Ship::init(SDL_Renderer* renderer, string file) {
	bool isGood = true;
	if (!mShip.loadFromFile(renderer, file.c_str())) {
		printf("An error has occured trying to render the ship! ending ship now!");
		isGood = false;
	}
	return isGood;
}

void Ship::setXY(int x, int y) {
	xCord = x;
	yCord = y;
}

void Ship::fire() {
	printf("PEW!");
}

void Ship::fireSpecial() {
	if (numSpecial-- > 0) {
		printf("Special attack go!!!");
	}
}

void Ship::handleInput(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_w: yVel -= VELOCITY; break;
		case SDLK_s: yVel += VELOCITY; break;
		case SDLK_a: xVel-= VELOCITY; break;
		case SDLK_d: xVel += VELOCITY; break;
		case SDLK_j : this->fire(); break;
		case SDLK_n: fireSpecial(); break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_w: yVel += VELOCITY; break;
		case SDLK_s: yVel -= VELOCITY; break;
		case SDLK_a: xVel += VELOCITY; break;
		case SDLK_d: xVel -= VELOCITY; break;
		}
	}
}

void Ship::move() {
	// Move the xCords of the ship first
	xCord += xVel;
	if (xCord < 0) {
		xCord = 0;
	}
	else if (xCord + mShip.getWidth() > SCREEN_WIDTH) {
		xCord -= xVel;
	}

	// Move the yCords of the ship there after
	yCord += yVel;
	if (yCord < 0) {
		yCord = 0;
	}
	else if (yCord + mShip.getHeight() > SCREEN_HEIGHT) {
		yCord -= yVel;
	}
}

int* Ship::getXVel() {
	return &xVel;
}

int* Ship::getYVel() {
	return &yVel;
}

void Ship::render(SDL_Renderer* renderer) {
	mShip.render(renderer, xCord, yCord);
}

Ship::~Ship(){
	mShip.freeTexture();
}
