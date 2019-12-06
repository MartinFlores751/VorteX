#ifndef CORE_H_
#define CORE_H_

// #pragma once should work too...

//CONST and ENUMS

// Screen Res
const int SCREEN_WIDTH = 144;
const int SCREEN_HEIGHT = 160;

// Since every sprite is 8x8, I can do this, but I really shouldn't
const int LEN_HEIGHT = 8;

// The max height that a sprite can appear off screen
const int Y_BOUND = -16;

// Speed cap
const int VELOCITY = 2;

//FUNC PROTO

bool init();
bool loadMedia();
void Quit();

#endif