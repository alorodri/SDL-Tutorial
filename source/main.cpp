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

// main quit flag
bool quit;
// poll events
SDL_Event e;

int main(int argc, char *argv[]) {
	if (init()) {
		if (loadMedia()) {
			SDL_BlitSurface(gImage, nullptr, gScreenSurface, nullptr);
			SDL_UpdateWindowSurface(gWindow);
			while (!quit) {
				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}
			}
		}
	}
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
	SDL_FreeSurface(gImage);
	gImage = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	SDL_Quit();
}

bool loadMedia() {
	gImage = SDL_LoadBMP("resources/sonic.bmp");
	if (!gImage) {
		std::cout << "Unable to load image 'sonic.bmp', SDL Error: " << SDL_GetError() << "\n";
		return false;
	}

	return true;
}