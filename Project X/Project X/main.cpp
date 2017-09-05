#include <SDL.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "LTexture.h"
#include "LWindow.h"
#include "Ship.h"
#include "core.h"

using std::vector;
using std::string;

LWindow gWindow;
Ship playerShip;


/*	Self imposed limitions:
 *	- 4 sound channels only
 *	- 8x8 tiles
 */

int main(int argc, char* argv[]) {
	if (!init()) {
		printf("An error has occured while initializing!\n");
	}
	else {
		if (!loadMedia()) {
			printf("Media could not be loaded!\n");
		}
		else {
			// Basic needed elements of the program
			bool quit = false;
			SDL_Event e;

			while (!quit) {
				if (SDL_PollEvent(&e) != 0) {
					// Exit the program?
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					playerShip.handleInput(e);
				}
				// Moves the player ship
				playerShip.move();

				// Clear the screen
				gWindow.clear();

				// Render sources here
				playerShip.render(gWindow.getRenderer());

				// Present Window
				gWindow.render();
			}
		}
	}

	Quit();
	return 0;
}