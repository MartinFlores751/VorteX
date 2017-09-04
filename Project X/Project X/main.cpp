#include <SDL.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "LWindow.h"
#include "core.h"

LWindow gWindow;
using std::string;

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
				if (SDL_WaitEvent(&e) != 0) {
					// Exit the program?
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}
				// Do rendering here!!!
			}
		}
	}

	Quit();
	return 0;
}