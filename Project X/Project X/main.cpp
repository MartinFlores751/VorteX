#include <SDL.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "core.h"

using std::vector;
using std::string;

LWindow gWindow;
PlayerShip pShip(3);
GruntShip test;
LTexture bg;


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
			int BGScroll = -160;
			SDL_Renderer * renderer = gWindow.getRenderer();

			while (!quit) {
				if (SDL_PollEvent(&e) != 0) {
					// Exit the program?
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					pShip.handleInput(e);
				}
				// Process AI event
				test.handleInput();

				// Moves the player ship
				pShip.move();
				test.aiMove();

				// Clear the screen
				gWindow.clear();

				// Render sources here
				if (BGScroll++ < SCREEN_HEIGHT) {
					bg.render(renderer, 0, BGScroll);
					bg.render(renderer, 0, BGScroll - (SCREEN_HEIGHT * 2));
				}
				else {
					BGScroll = -SCREEN_HEIGHT;
					bg.render(renderer, 0, BGScroll);
					bg.render(renderer, 0, BGScroll - (SCREEN_HEIGHT * 2));
				}
				pShip.render(renderer);
				test.render(renderer);

				// Present Window
				gWindow.render();
			}
		}
	}

	Quit();
	return 0;
}