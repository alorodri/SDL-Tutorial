#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Rect& stretchedRectDimensions();

SDL_Window* gWindow = nullptr;
// surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

// textures
SDL_Texture* loadTexture(const std::string path);
SDL_Texture* gTexture = nullptr;

SDL_Renderer* gRenderer = nullptr;

// main quit flag
bool quit;
// poll events
SDL_Event e;

constexpr char SONIC_BMP[] = "resources/sonic.bmp";
constexpr char CATTO_BMP[] = "resources/catto.bmp";
constexpr char SMILE_BMP[] = "resources/smile.bmp";
constexpr char DOGGI_BMP[] = "resources/doggi.bmp";
constexpr char DOGGI_PNG[] = "resources/doggi.png";
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
SDL_Texture* gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL];
SDL_Texture* gLoadedTexture = nullptr;

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
							gLoadedTexture = gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_UP];
							break;
						case SDLK_DOWN:
							gLoadedTexture = gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN];
							break;
						case SDLK_LEFT:
							gLoadedTexture = gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT];
							break;
						case SDLK_RIGHT:
							gLoadedTexture = gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT];
							break;
						default:
							gLoadedTexture = gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
					
					SDL_RenderClear(gRenderer);
					SDL_RenderCopy(gRenderer, gLoadedTexture, nullptr, nullptr);
					SDL_RenderPresent(gRenderer);
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

			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			if (gRenderer) {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					std::cout << "SDL Image couldn't initialize, SDL Error: " << IMG_GetError() << "\n";
					return false;
				}
				else {
					gScreenSurface = SDL_GetWindowSurface(gWindow);
				}

			}

		}
	}

	return true;
}

void close() {
	SDL_DestroyTexture(gLoadedTexture);
	gLoadedTexture = nullptr;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = nullptr;
	gWindow = nullptr;

	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(const std::string path) {
	SDL_Texture* texture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface) {
		texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (!texture) {
			std::cout << "Unable to create the texture, SDL Error: " << SDL_GetError();
		}

		SDL_FreeSurface(loadedSurface);
	}
	else {
		std::cout << "Unable to load image, IMG Error: " << IMG_GetError();
	}

	return texture;
}

bool loadMedia() {
	gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT] = loadTexture(SONIC_BMP);
	gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_UP] = loadTexture(CATTO_BMP);
	gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN] = loadTexture(SMILE_BMP);
	gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT] = loadTexture(DOGGI_PNG);
	gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT] = loadTexture(SKINNER_BMP);
	if (!gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT]) {
		std::cout << "Unable to load image '" << SONIC_BMP << "', SDL Error: " << SDL_GetError() << "\n";
		return false;
	}
	if (!gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_UP]) {
		std::cout << "Unable to load image '" << CATTO_BMP << "', SDL Error: " << SDL_GetError() << "\n";
		return false;
	}
	if (!gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN]) {
		std::cout << "Unable to load image '" << SMILE_BMP << "', SDL Error: " << SDL_GetError() << "\n";
		return false;
	}
	if (!gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT]) {
		std::cout << "Unable to load image '" << DOGGI_BMP << "', SDL Error: " << SDL_GetError() << "\n";
		return false;
	}
	if (!gTextureKeyImages[KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT]) {
		std::cout << "Unable to load image '" << SKINNER_BMP << "', SDL Error: " << SDL_GetError() << "\n";
		return false;
	}

	return true;
}

// deprecated since part 7
SDL_Rect& stretchedRectDimensions() {
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = SCREEN_WIDTH;
	rect.h = SCREEN_HEIGHT;
	return rect;
}