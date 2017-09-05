#ifndef CORE_H_
#define CORE_H_

// #pragma once should work too...

//CONST and ENUMS

// Screen Res
const int SCREEN_WIDTH = 144;
const int SCREEN_HEIGHT = 160;

// Speed cap
const int VELOCITY = 2;

//FUNC PROTO

bool init();
bool loadMedia();
void Quit();

#endif