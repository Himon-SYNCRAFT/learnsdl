#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <algorithm>
#include <cassert>

#include "Texture.h"
#include "Dot.h"
#include "consts.h"

//Screen dimension constants
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;
Texture texture;


int forceBetweenMinAndMax(const int input, const int minValue, const int maxValue) {
    return std::min(std::max(input, minValue), maxValue);
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    //Set texture_ filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture_ filtering not enabled!");
    }

    window = SDL_CreateWindow(
            "SDL Tutorial",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) {
        printf("Renderer could not be created!");
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;

    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

bool loadMedia() {
    font = TTF_OpenFont("assets/lazy.ttf", 28);

    if (font == nullptr) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    texture.setRenderer(renderer);

    if (!texture.loadFromFile("assets/bg.png")) {
        printf("Failed to load background texture\n");
        return false;
    }

    return true;
}

void close() {
    texture.free();

    TTF_CloseFont(font);
    font = nullptr;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main() {
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        //Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            Dot dot = Dot(renderer, Dot::WIDTH / 2, Dot::HEIGHT / 2);
            SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }

                    dot.handleEvent(e);
                }

                dot.move();

                camera.x = (dot.getX() + Dot::WIDTH / 2) - SCREEN_WIDTH / 2;
                camera.y = (dot.getY() + Dot::HEIGHT / 2) - SCREEN_HEIGHT / 2;

                // blocked moving camera out of level
                camera.x = forceBetweenMinAndMax(camera.x, 0, LEVEL_WIDTH - camera.w);
                camera.y = forceBetweenMinAndMax(camera.y, 0, LEVEL_HEIGHT - camera.h);

                //Clear screen
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                texture.render(0, 0, &camera);
                dot.render(camera.x, camera.y);

                SDL_RenderPresent(renderer);
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
