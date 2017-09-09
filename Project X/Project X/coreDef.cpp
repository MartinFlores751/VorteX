#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "LTexture.h"
#include "LWindow.h"
#include "core.h"
#include "PlayerShip.h"
#include "GruntShip.h"

extern LWindow gWindow;
extern PlayerShip pShip;
extern GruntShip test;
extern LTexture bg;

using std::string;

bool init() {
	bool isGood = true;
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("Failed to initialize video module! SDL Error: %s \n", SDL_GetError());
		isGood = false;
	}
	else {
		// Set linear texture filtering
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("WARNING: Failed to set linear filter, using nearest instead.\n");
		}

		// Create window
		if (!gWindow.init()) {
			printf("An error has occured while initializing the window! Exiting the program now...");
			isGood = false;
		}

		if (isGood) {
			// Initialize IMG
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("Failed to set image data type! SDL IMG Error: %s \n", IMG_GetError());
				isGood = false;
			}
#ifdef _SDL_MIXER_H
			// Initialize Mixer 
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
				printf("SDL_mixer could not be initialized! SDL_mixer Error: %s \n", Mix_GetError());
				isGood = false;
			}
#endif
#ifdef _SDL_TTF_H
			// Initialzie TTF
			if (TTF_Init() == -1) {
				printf("SDL_tff could not initialize! SDL TTF ERROR: %s \n", TTF_GetError());
				isGood = false;
			}
#endif
		}
	}
	return isGood;
}

bool loadMedia() {
	bool isGood = true;

	// Initialize textures and stuff here!
	if (!pShip.init(gWindow.getRenderer(), "img/p_ship.png")) {
		printf("File could not be found! Ending program...");
		isGood = false;
	}
	else
		pShip.setXY(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 8);

	if (!test.init(gWindow.getRenderer(), "img/p_ship.png")) {
		printf("File could not be loaded! Ending program...");
		isGood = false;
	}

	if (!bg.loadFromFile(gWindow.getRenderer(), "img/bg.png")) {
		printf("Bad");
		isGood = false;
	}

	return isGood;
}

void Quit() {
	gWindow.free();
	

	// Quits the subsystems and the main SDL
	IMG_Quit();
	SDL_Quit();
}