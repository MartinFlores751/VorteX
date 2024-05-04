#include "GruntShip.h"
#include "LWindow.h"
#include "PlayerShip.h"
#include "core.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <spdlog/spdlog.h>

#include <string>
#include <vector>

using std::string;
using std::vector;

extern LWindow gWindow;
extern PlayerShip pShip;
extern vector<GruntShip> enemyShips;
extern vector<Bullets> bullets;
extern LTexture bg;
extern LTexture title;

bool init() {
  bool isGood = true;
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    spdlog::error("Failed to initialize video module! SDL Error: [{}]",
                  SDL_GetError());
    isGood = false;
  } else {
    // Set linear texture filtering
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      spdlog::warn("Failed to set linear filter, using nearest instead.");
    }

    // Create window
    if (!gWindow.init()) {
      spdlog::error("An error has occured while initializing the window! "
                    "Exiting the program now...");
      isGood = false;
    }

    if (isGood) {
      // Initialize IMG
      int imgFlags = IMG_INIT_PNG;
      if (!(IMG_Init(imgFlags) & imgFlags)) {
        spdlog::error("Failed to set image data type! SDL IMG Error: [{}]",
                      IMG_GetError());
        isGood = false;
      }
#ifdef _SDL_MIXER_H
      // Initialize Mixer
      if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        spdlog::error(
            "SDL_mixer could not be initialized! SDL_mixer Error: [{}]",
            Mix_GetError());
        isGood = false;
      }
#endif
#ifdef _SDL_TTF_H
      // Initialzie TTF
      if (TTF_Init() == -1) {
        spdlog::error("SDL_tff could not initialize! SDL TTF ERROR: [{}]",
                      TTF_GetError());
        isGood = false;
      }
#endif
    }
  }
  return isGood;
}

bool loadMedia() {
  bool isGood = true;

  // Initialize ship
  if (!pShip.init(gWindow.getRenderer(), "img/pSprite/ship.png")) {
    spdlog::error("File could not be found! Ending program...");
    isGood = false;
  } else {
    pShip.setXY(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 8);
  }

  // Initialize enemy ships
  enemyShips.resize(10);
  for (GruntShip& gship : enemyShips) {
    if (!gship.init(gWindow.getRenderer(), "img/smalls/Dragonfly.png")) {
      spdlog::error("Failed to load texture! Ending program...");
      isGood = false;
      break;
    }
  }

  // Init the bullets
  bullets.resize(10);
  for (Bullets& bullet : bullets) {
    if (!bullet.init(gWindow.getRenderer(), "img/pSprite/missile.png")) {
      spdlog::error("Failed to load bullet sprite! Ending program...");
      isGood = false;
      break;
    }
  }

  // Load title screen
  if (!title.loadFromFile(gWindow.getRenderer(), "img/INTRO/t_all.png")) {
    spdlog::error("Title screen failed to load! Ending program now!");
    isGood = false;
  }

  // Load gameBG
  if (!bg.loadFromFile(gWindow.getRenderer(), "img/BG/bg1.png")) {
    spdlog::error("Failed to load background for game. Ending program.");
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
