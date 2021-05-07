#include <SDL.h>

#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = nullptr;
// surface contained by the window
SDL_Surface* gScreenSurface = nullptr;
// image to load
SDL_Surface* gImage = nullptr;

int main(int argc, char *argv[]) {
	init();
	loadMedia();
	close();
	return 0;
}

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL video couldn't initialize, SDL Error: " << SDL_GetError() << "\n";
		return false;
	}
	else {
		gWindow = SDL_CreateWindow(
			"SDL Tutorial",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		if (!gWindow) {
			std::cout << "Window couldn't be created, SDL Error: " << SDL_GetError() << "\n";
			return false;
		}
		else {
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return true;
}

void close() {
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}

bool loadMedia() {
	return true;
}