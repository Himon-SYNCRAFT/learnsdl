//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "core/Texture.hpp"
#include "core/Button.hpp"
#include "core/Timer.hpp"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TOTAL_BUTTONS = 4;
/* const int WALKING_ANIMATION_FRAMES = 4; */
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGTH = 200;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect spriteClips[BUTTON_SPRITE_TOTAL];
Button buttons[TOTAL_BUTTONS];
TTF_Font* font = NULL;
Texture texture;
Texture pauseTexture;
Texture startTexture;


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

    SDL_Color textColor = { 0, 0, 0, 255 };

    texture.setRenderer(renderer);
    pauseTexture.setRenderer(renderer);
    startTexture.setRenderer(renderer);

    if (!pauseTexture.loadFromRenderedText("Press P to Pause or Unpause the Timer", textColor, font)) {
        printf("Unable to render pause/unpause prompt texture");
        return false;
    }

    if (!startTexture.loadFromRenderedText("Press S to Start or Stop the Timer", textColor, font)) {
        printf("Unable to render pause/unpause prompt texture");
        return false;
    }

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

            Timer timer;

            std::stringstream timeText;

            //While application is running
            while(!quit) {
                //Handle events on queue
                while(SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        if (e.key.keysym.sym == SDLK_s) {
                            if (timer.isStarted()) {
                                timer.stop();
                            } else {
                                timer.start();
                            }
                        } else if (e.key.keysym.sym == SDLK_p) {
                            if (timer.isPaused()) {
                                timer.unpause();
                            } else {
                                timer.pause();
                            }
                        }
                    }
                }

                timeText.str("");
                timeText << "Seconds since start time " << (timer.getTicks() / 1000.f);

                if (!texture.loadFromRenderedText(timeText.str().c_str(), textColor, font)) {
                    printf("Unable to render time texture\n");
                }

                //Clear screen
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                startTexture.render((SCREEN_WIDTH - startTexture.getWidth()) / 2, 0);
                pauseTexture.render((SCREEN_WIDTH - pauseTexture.getWidth()) / 2, pauseTexture.getHeight());
                texture.render((SCREEN_WIDTH - texture.getWidth()) / 2, (SCREEN_HEIGHT - texture.getHeight()) / 2);

                //Update screen
                SDL_RenderPresent(renderer);
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
