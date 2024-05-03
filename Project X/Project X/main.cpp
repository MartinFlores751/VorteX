#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
#include "core.h"
#include "LWindow.h"
#include "PlayerShip.h"
#include "GruntShip.h"

using std::vector;
using std::string;

LWindow gWindow;
PlayerShip pShip(3);
vector<GruntShip> enemyShips;
vector<Bullets> bullets;
LTexture bg;
LTexture title;


/*	Self imposed limitions:
 *	- 4 sound channels only
 */

/*
	TO-DO:
	- Create a score system
	- Be able to load and save score system
	- Get a colision system in place
*/

int main() {
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
			bool gamePlaying = false;

			while (!quit) {
				if (SDL_PollEvent(&e) != 0) {
					// Exit the program?
					if (e.type == SDL_QUIT  || e.key.keysym.sym == SDLK_ESCAPE)
						quit = true;

					else if (gamePlaying)
						pShip.handleInput(e, &bullets);

					else if (e.key.keysym.sym == SDLK_RETURN) {
							gamePlaying = true;
							continue;
						}
				}
				if (gamePlaying) {
					// Process AI event
					for (GruntShip &gship : enemyShips)
						gship.handleInput(e, &bullets);

					// Move the bullets
					for (Bullets &bullet : bullets)
						bullet.move();

					// Moves the player ship
					pShip.move();

					// Move Enemy
					for (GruntShip &gship : enemyShips)
						gship.aiMove();

					// Clear the screen
					gWindow.clear();

					// Render BG
					if (BGScroll++ < SCREEN_HEIGHT) {
						bg.render(renderer, 0, BGScroll);
						bg.render(renderer, 0, BGScroll - (SCREEN_HEIGHT * 2));
					}
					else {
						BGScroll = -SCREEN_HEIGHT;
						bg.render(renderer, 0, BGScroll);
						bg.render(renderer, 0, BGScroll - (SCREEN_HEIGHT * 2));
					}
					// Render bullets
					for (Bullets &bullet : bullets)
						bullet.render(renderer);

					// Render ships
					pShip.render(renderer);
					for (GruntShip &gship : enemyShips)
						gship.render(renderer);
				}
				else {
					title.render(renderer, 0, 0);
				}

				// Present Window
				gWindow.render();
			}
		}
	}

	Quit();
	return 0;
}
