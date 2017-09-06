#include <SDL.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "LTexture.h"
#include "LWindow.h"
#include "PlayerShip.h"
#include "core.h"

using std::vector;
using std::string;

LWindow gWindow;
PlayerShip pShip(3);


/*	Self imposed limitions:
 *	- 4 sound channels only
 *	- 8x8 tiles
 */

/*
	TO-DO:
	- Create a score system
	- Be able to load and save score system
	- Get a colision system in place
	- Organize the code better...
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
					pShip.handleInput(e);
				}
				// Moves the player ship
				pShip.move();

				// Clear the screen
				gWindow.clear();

				// Render sources here
				pShip.render(gWindow.getRenderer());

				// Present Window
				gWindow.render();
			}
		}
	}

	Quit();
	return 0;
}