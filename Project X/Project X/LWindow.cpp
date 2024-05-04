#include "LWindow.h"
#include "core.h"

#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

#include <sstream>


extern SDL_Renderer* gRenderer;

LWindow::LWindow() {
  // Initialize window values
  mWindow = nullptr;
  mMouseFocus = false;
  mKeyboardFocus = false;
  mFullScreen = false;
  mMinimized = false;
  mWidth = 0;
  mHeight = 0;
}

bool LWindow::init() {
  // Create window
  mWindow = SDL_CreateWindow(
      "Project X", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
  if (mWindow != nullptr) {
    mMouseFocus = true;
    mKeyboardFocus = true;
    mWidth = SCREEN_WIDTH;
    mHeight = SCREEN_HEIGHT;

    // Create renderer for window
    mRenderer = SDL_CreateRenderer(
        mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == nullptr) {
      spdlog::error("Renderer could not be created! SDL Error: [{}]",
                    SDL_GetError());
      SDL_DestroyWindow(mWindow);
      mWindow = nullptr;
    } else {
      // Initialize renderer color
      SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

      // Grab window idenrifier
      mWindowID = SDL_GetWindowID(mWindow);

      // Flag as opened
      mShown = true;
    }
  } else {
    spdlog::error("Window could not be created! SDL Error: [{}]",
                  SDL_GetError());
  }

  return mWindow != nullptr && mRenderer != nullptr;
}

void LWindow::handleEvent(SDL_Event& e) {
  // Window event occured

  if (e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID) {
    // Caption update flag
    bool updateCaption = false;
    switch (e.window.event) {
      // Window appeared
    case SDL_WINDOWEVENT_SHOWN:
      mShown = true;
      break;

      // Window dissapeared
    case SDL_WINDOWEVENT_HIDDEN:
      mShown = false;
      break;

      // Get new dimensions and repaint
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      mWidth = e.window.data1;
      mHeight = e.window.data2;
      SDL_RenderPresent(mRenderer);
      break;

      // Repaint on expose
    case SDL_WINDOWEVENT_EXPOSED:
      SDL_RenderPresent(mRenderer);
      break;

      // Mouse enter
    case SDL_WINDOWEVENT_ENTER:
      mMouseFocus = true;
      updateCaption = true;
      break;

      // Mouse exit
    case SDL_WINDOWEVENT_LEAVE:
      mMouseFocus = false;
      updateCaption = true;
      break;

      // Keyboard focus regained
    case SDL_WINDOWEVENT_FOCUS_GAINED:
      mKeyboardFocus = true;
      updateCaption = true;
      break;

      // Keyboad focus lost
    case SDL_WINDOWEVENT_FOCUS_LOST:
      mKeyboardFocus = false;
      updateCaption = true;
      break;

      // Window minimized
    case SDL_WINDOWEVENT_MINIMIZED:
      mMinimized = true;
      break;

      // Window maximized
    case SDL_WINDOWEVENT_MAXIMIZED:
      mMinimized = false;
      break;

      // Window restored
    case SDL_WINDOWEVENT_RESTORED:
      mMinimized = false;
      break;

      // Hide on close
    case SDL_WINDOWEVENT_CLOSE:
      SDL_HideWindow(mWindow);
      break;
    }

    // Update window caption with new data
    if (updateCaption) {
      std::stringstream caption;
      caption << "SDL Multi-Window ID:" << mWindowID
              << " MouseFocus:" << ((mMouseFocus) ? "On" : "Off")
              << " KeyboardFocus:" << ((mKeyboardFocus) ? "On" : "Off");
      SDL_SetWindowTitle(mWindow, caption.str().c_str());
    }
  } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
    if (mFullScreen) {
      SDL_SetWindowFullscreen(mWindow, SDL_FALSE);
      mFullScreen = false;
    } else {
      SDL_SetWindowFullscreen(mWindow, SDL_TRUE);
      mFullScreen = true;
      mMinimized = false;
    }
  }
}

void LWindow::focus() {
  // Restore window if needed
  if (!mShown) {
    SDL_ShowWindow(mWindow);
  }
  // Move window forward
  SDL_RaiseWindow(mWindow);
}

void LWindow::render() {
  if (!mMinimized) {
    // Update screen
    SDL_RenderPresent(mRenderer);
  }
}

void LWindow::clear() {
  SDL_RenderClear(mRenderer);
}

void LWindow::free() {
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);
  mRenderer = nullptr;
  mWindow = nullptr;
}

int LWindow::getWidth() {
  return mWidth;
}

int LWindow::getHeight() {
  return mHeight;
}

SDL_Renderer* LWindow::getRenderer() {
  return mRenderer;
}

bool LWindow::hasMouseFocus() {
  return mMouseFocus;
}

bool LWindow::hasKeyboardFocus() {
  return mKeyboardFocus;
}

bool LWindow::isMinimized() {
  return mMinimized;
}

bool LWindow::isShown() {
  return mShown;
}
