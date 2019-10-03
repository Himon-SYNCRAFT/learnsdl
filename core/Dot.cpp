/*
 * =====================================================================================
 *
 *       Filename:  Dot.cpp
 *
 *        Created:  03.10.2019 11:21:12
 *         Author:  Daniel Zawłocki
 *
 * =====================================================================================
 */
#include <SDL2/SDL.h>
#include "Dot.hpp"
#include "Texture.hpp"
#include "consts.hpp"


Dot::Dot(SDL_Renderer* renderer) {
    x = 0;
    y = 0;
    velocityX = 0;
    velocityY = 0;

    texture.setRenderer(renderer);

    if (!texture.loadFromFile("assets/dot.bmp")) {
        printf("Failed to load dot texture!\n");
    }
}

void Dot::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: velocityY -= VELOCITY; break;
            case SDLK_DOWN: velocityY += VELOCITY; break;
            case SDLK_LEFT: velocityX -= VELOCITY; break;
            case SDLK_RIGHT: velocityX += VELOCITY; break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: velocityY += VELOCITY; break;
            case SDLK_DOWN: velocityY -= VELOCITY; break;
            case SDLK_LEFT: velocityX += VELOCITY; break;
            case SDLK_RIGHT: velocityX -= VELOCITY; break;
        }
    }
}

void Dot::move() {
    x += velocityX;

    if ((x < 0) || (x + WIDTH > SCREEN_WIDTH)) {
        x -= velocityX;
    }

    y += velocityY;

    if ((y < 0) || (y + HEIGHT > SCREEN_HEIGHT)) {
        y -= velocityY;
    }
}

void Dot::render() {
    texture.render(x, y);
}
