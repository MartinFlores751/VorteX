#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string>

using std::string;

LTexture::LTexture() {
  mTexture = nullptr;
  mWidth = 0;
  mHeight = 0;
}

LTexture::~LTexture() {
  freeTexture();
}

bool LTexture::loadFromFile(SDL_Renderer *renderer, string path) {
  freeTexture();
  SDL_Texture *newTexture = nullptr;
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr) {
    printf("Failed to load image! SDL Image Error: %s \n", IMG_GetError());
  } else {
    SDL_SetColorKey(loadedSurface, 1,
                    SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == nullptr) {
      printf("Failed to create texture! SDL Error: %s \n", SDL_GetError());
    } else {
      mHeight = loadedSurface->h;
      mWidth = loadedSurface->w;
    }
    SDL_FreeSurface(loadedSurface);
  }
  mTexture = newTexture;
  return mTexture != nullptr;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(SDL_Renderer *renderer, string textureText,
                                    SDL_Color textColor) {
  freeTexture();
  SDL_Color bg = {255, 255, 255};
  SDL_Surface *textSurface =
      TTF_RenderText_Blended(gFont, textureText.c_str(), textColor);
  if (textSurface == nullptr) {
    printf("Unable to render text surface! SDL_tff Error: %s \n",
           TTF_GetError());
  } else {
    mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (mTexture == nullptr) {
      printf("Unable to create texture from surface! SDL Error: %s \n",
             SDL_GetError());
    } else {
      mWidth = textSurface->w;
      mHeight = textSurface->h;
    }
    SDL_FreeSurface(textSurface);
  }
  return mTexture != nullptr;
}
#endif

void LTexture::freeTexture() {
  if (mTexture != nullptr) {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
    mHeight = 0;
    mWidth = 0;
  }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
  SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
  SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha) {
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip,
                      double angle, SDL_Point *center, SDL_RendererFlip flip) {
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};
  if (clip != nullptr) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getHeight() {
  return mHeight;
}

int LTexture::getWidth() {
  return mWidth;
}