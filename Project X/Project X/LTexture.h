#pragma once
class LTexture {
public:
	LTexture();
	~LTexture();

	//Loads image from specified path
	bool loadFromFile(SDL_Renderer* renderer, std::string path);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(SDL_Renderer* renderer, std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void freeTexture();

	//Set color mod
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha mod
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Return image dimensions
	int getHeight();
	int getWidth();
private:
	SDL_Texture* mTexture;
	int mHeight;
	int mWidth;
};