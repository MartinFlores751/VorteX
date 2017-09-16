#include <stdio.h>
#include "core.h"
#include "Ship.h"


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

void Ship::fire(vector<Bullets> *bullets, bool isPlayer) {
	for (Bullets &bullet : *bullets) {
		if (!bullet.isOnScreen()) {
			if (isPlayer)
				bullet.setXY(xCord, yCord - LEN_HEIGHT, true);
			else
				bullet.setXY(xCord, yCord + LEN_HEIGHT, false);
			break;
		}
	}
}

void Ship::fireSpecial() {
	if (numSpecial-- > 0) {
		printf("Special attack go!!!");
	}
}

void Ship::handleInput(SDL_Event& e, vector<Bullets> *bullets, bool isPlayer) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: yVel -= VELOCITY; break;
		case SDLK_DOWN: yVel += VELOCITY; break;
		case SDLK_LEFT: xVel-= VELOCITY; break;
		case SDLK_RIGHT: xVel += VELOCITY; break;
		case SDLK_z: this->fire(bullets, isPlayer); break;
		case SDLK_x: fireSpecial(); break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: yVel += VELOCITY; break;
		case SDLK_DOWN: yVel -= VELOCITY; break;
		case SDLK_LEFT: xVel += VELOCITY; break;
		case SDLK_RIGHT: xVel -= VELOCITY; break;
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

bool Ship::hasCollided(vector<Bullets> *bullets) {
	int xBullet, yBullet;
	for (Bullets &bullet : *bullets) {
		xBullet = bullet.getXCord();
		yBullet = bullet.getYCord();

		// If the bullet is not outisde the ship, woe to ye
		if (!(xCord > xBullet || (xCord + LEN_HEIGHT) < xBullet))
			if (!(yCord > yBullet || (yCord + LEN_HEIGHT < yBullet)))
				return true;
	}

	return false;
}

bool Ship::hasCollided(vector<Ship> *gShips) {
	int xShip, yShip;
	for (Ship &ship : *gShips) {
		xShip, yShip;
		xShip = ship.getXCords();
		yShip = ship.getYCords();

		// If the ship is not outside of you, woe to both
		if (!(xCord > xShip || (xCord + LEN_HEIGHT) < xShip))
			if (!(yCord > yShip || (yCord + LEN_HEIGHT) < yShip))
				return true;
	}

	return false;
}

int* Ship::getXVel() {
	return &xVel;
}

int* Ship::getYVel() {
	return &yVel;
}

int Ship::getXCords() {
	return xCord;
}

int Ship::getYCords() {
	return yCord;
}

void Ship::render(SDL_Renderer* renderer) {
	mShip.render(renderer, xCord, yCord);
}

Ship::~Ship(){
	mShip.freeTexture();
}
