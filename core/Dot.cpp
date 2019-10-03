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

    collider.w = WIDTH;
    collider.h = HEIGHT;
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

void Dot::move(SDL_Rect &wall) {
    x += velocityX;
    collider.x = x;

    if ((x < 0) || (x + WIDTH > SCREEN_WIDTH) || checkCollision(wall)) {
        x -= velocityX;
    }

    y += velocityY;
    collider.y = y;

    if ((y < 0) || (y + HEIGHT > SCREEN_HEIGHT) || checkCollision(wall)) {
        y -= velocityY;
    }
}

void Dot::render() {
    texture.render(x, y);
}

bool Dot::checkCollision(const SDL_Rect &other) {
    int leftA = collider.x;
    int rightA = collider.x + collider.w;
    int topA = collider.y;
    int bottomA = collider.y + collider.h;

    int leftB = other.x;
    int rightB = other.x + other.w;
    int topB = other.y;
    int bottomB = other.y + other.h;

    if (bottomA <= topB) {
        return false;
    }

    if (topA >= bottomB) {
        return false;
    }

    if (rightA <= leftB) {
        return false;
    }

    if (leftA >= rightB) {
        return false;
    }

    return true;
}
