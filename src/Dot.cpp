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
#include "Dot.h"
#include "Texture.h"
#include "consts.h"


Dot::Dot(SDL_Renderer* renderer, const int startX, const int startY) {
    x_ = startX;
    y_ = startY;
    velocityX_ = 0;
    velocityY_ = 0;

    texture_.setRenderer(renderer);

    if (!texture_.loadFromFile("assets/dot.png")) {
        printf("Failed to load dot texture_!\n");
    }
}

void Dot::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: velocityY_ -= VELOCITY; break;
            case SDLK_DOWN: velocityY_ += VELOCITY; break;
            case SDLK_LEFT: velocityX_ -= VELOCITY; break;
            case SDLK_RIGHT: velocityX_ += VELOCITY; break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: velocityY_ += VELOCITY; break;
            case SDLK_DOWN: velocityY_ -= VELOCITY; break;
            case SDLK_LEFT: velocityX_ += VELOCITY; break;
            case SDLK_RIGHT: velocityX_ -= VELOCITY; break;
        }
    }
}

void Dot::move() {
    x_ += velocityX_;

    if (x_ < 0 || (x_ + WIDTH > LEVEL_WIDTH)) {
        x_ -= velocityX_;
    }

    y_ += velocityY_;

    if (y_ < 0 || (y_ + HEIGHT > LEVEL_HEIGHT)) {
        y_ -= velocityY_;
    }
}

void Dot::render(const int camX, const int camY) {
    texture_.render(x_ - camX, y_ - camY);
}
