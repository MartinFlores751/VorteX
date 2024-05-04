#include "Bullets.h"
#include "core.h"

Bullets::Bullets(int x, int y, [[maybe_unused]] bool fromP) {
  xAxis = x;
  yAxis = y;
  onScreen = false;
}

void Bullets::setXY(int x, int y, bool fromP) {
  xAxis = x;
  yAxis = y;
  fromPlayer = fromP;
  onScreen = true;
}

void Bullets::render(SDL_Renderer* renderer) {
  if (onScreen) {
    missile.render(renderer, xAxis, yAxis);
  }
}

void Bullets::move() {
  if (onScreen) {
    if ((xAxis >= 0 && xAxis + LEN_HEIGHT <= SCREEN_WIDTH) &&
        (yAxis >= -8 && yAxis + LEN_HEIGHT <= SCREEN_HEIGHT + 8)) {
      if (fromPlayer) {
        yAxis -= 2;
      } else {
        yAxis += 2;
      }
    } else {
      onScreen = false;
    }
  }
}

bool Bullets::init(SDL_Renderer* renderer, string path) {
  return missile.loadFromFile(renderer, path.c_str());
}

bool Bullets::isOnScreen() {
  return onScreen;
}

int Bullets::getXCord() {
  return xAxis;
}

int Bullets::getYCord() {
  return yAxis;
}
