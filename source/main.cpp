#include <SDL.h>

#include <iostream>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = nullptr;
// surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

// main quit flag
bool quit;
// poll events
SDL_Event e;

constexpr char SONIC_BMP[] = "resources/sonic.bmp";
constexpr char CATTO_BMP[] = "resources/catto.bmp";
constexpr char SMILE_BMP[] = "resources/smile.bmp";
constexpr char DOGGI_BMP[] = "resources/doggi.bmp";
constexpr char SKINNER_BMP[] = "resources/skinner.bmp";

enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

// image to load
SDL_Surface* gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gLoadedImage = nullptr;

int main(int argc, char *argv[]) {
	if (init()) {
		if (loadMedia()) {
			while (!quit) {
				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN) {
						switch (e.key.keysym.sym) {
						case SDLK_UP:
							gLoadedImage = gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_UP];
							break;
						case SDLK_DOWN:
							gLoadedImage = gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN];
							break;
						case SDLK_LEFT:
							gLoadedImage = gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT];
							break;
						case SDLK_RIGHT:
							gLoadedImage = gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT];
							break;
						default:
							gLoadedImage = gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
					SDL_BlitSurface(gLoadedImage, nullptr, gScreenSurface, nullptr);
					SDL_UpdateWindowSurface(gWindow);
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
	SDL_FreeSurface(gLoadedImage);
	gLoadedImage = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	SDL_Quit();
}

bool loadMedia() {
	gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT] = SDL_LoadBMP(SONIC_BMP);
	gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_UP] = SDL_LoadBMP(CATTO_BMP);
	gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN] = SDL_LoadBMP(SMILE_BMP);
	gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT] = SDL_LoadBMP(DOGGI_BMP);
	gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT] = SDL_LoadBMP(SKINNER_BMP);
	if (!gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT]) {
		std::cout << "Unable to load image '" << SONIC_BMP << "', SDL Error: " << SDL_GetError() << "\n";
		return false;
	}
	if (!gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_UP]) {
		std::cout << "Unable to load image '" << CATTO_BMP << "', SDL Error: " << SDL_GetError() << "\n";
		return false;
	}
	if (!gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN]) {
		std::cout << "Unable to load image '" << SMILE_BMP << "', SDL Error: " << SDL_GetError() << "\n";
		return false;
	}
	if (!gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT]) {
		std::cout << "Unable to load image '" << DOGGI_BMP << "', SDL Error: " << SDL_GetError() << "\n";
		return false;
	}
	if (!gSurfaceKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT]) {
		std::cout << "Unable to load image '" << SKINNER_BMP << "', SDL Error: " << SDL_GetError() << "\n";
		return false;
	}

	return true;
}