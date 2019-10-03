//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <math.h>

#include "core/Texture.hpp"
#include "core/Button.hpp"
#include "core/Timer.hpp"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
Texture texture;


bool init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    //Set texture filtering to linear
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(window == NULL) {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
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

    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    texture.setRenderer(renderer);

    return true;
}

void close() {
    texture.free();

    TTF_CloseFont(font);
    font = NULL;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main() {
    //Start up SDL and create window
    if(!init()) {
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

            SDL_Color textColor = { 0, 0, 0, 255 };

            Timer fpsTimer;

            std::stringstream timeText;

            int countedFrames = 0;

            fpsTimer.start();

            //While application is running
            while(!quit) {
                //Handle events on queue
                while(SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);

                if (avgFPS > 2000000) {
                    avgFPS = 0;
                }

                timeText.str("");
                timeText << "Average FPS " << roundf(avgFPS * 100) / 100;

                if (!texture.loadFromRenderedText(timeText.str().c_str(), textColor, font)) {
                    printf("Unable to render FPS texture!\n");
                }

                //Clear screen
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                texture.render((SCREEN_WIDTH - texture.getWidth()) / 2, (SCREEN_HEIGHT - texture.getHeight()) / 2);

                //Update screen
                SDL_RenderPresent(renderer);
                ++countedFrames;
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
