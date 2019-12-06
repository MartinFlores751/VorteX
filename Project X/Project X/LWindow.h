#pragma once

class LWindow {
public:
	// Initializes internals
	LWindow();

	// Creates window
	bool init();

	// Handels window events
	void handleEvent(SDL_Event& e);

	// Focuses on window
	void focus();

	// Shows windows contents
	void render();

	// Clear the window
	void clear();

	// Deallocates internals
	void free();

	// Window dimensions
	int getWidth();
	int getHeight();

	// Give renderer for img processing
	SDL_Renderer* getRenderer();

	// Window focii
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();
	bool isShown();

private:
	// Window data
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	int mWindowID;

	// Window dimensions
	int mWidth;
	int mHeight;

	// Window focus
	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
	bool mShown;
};