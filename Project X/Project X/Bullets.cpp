#include "Bullets.h"



Bullets::Bullets(int x, int y){
	xAxis = x;
	yAxis = y;
}

void Bullets::render(SDL_Renderer* renderer) {
	missile.render(renderer, xAxis, yAxis);
}

Bullets::~Bullets(){

}
