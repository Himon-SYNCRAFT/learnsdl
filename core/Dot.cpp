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


Dot::Dot(SDL_Renderer* renderer, const int startX, const int startY) {
    x = startX;
    y = startY;
    velocityX = 0;
    velocityY = 0;

    collider.r = WIDTH / 2;
    shiftColliders();

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

void Dot::move(const SDL_Rect &rectangle, const Circle &circle) {
    x += velocityX;
    y += velocityY;
    shiftColliders();

    if ((x - collider.r < 0) || (x + collider.r > SCREEN_WIDTH) || checkCollision(rectangle) || checkCollision(circle)) {
        x -= velocityX;
        shiftColliders();
    }

    if ((y - collider.r < 0) || (y + collider.r > SCREEN_HEIGHT) || checkCollision(rectangle) || checkCollision(circle)) {
        y -= velocityY;
        shiftColliders();
    }
}

void Dot::render() {
    texture.render(x, y);
}

bool Dot::checkCollision(const Circle &other) {
    int totalRadiusSquared = collider.r + other.r;
    totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    if (distanceSquared(collider.x, collider.y, other.x, other.y) < totalRadiusSquared) {
        return true;
    }

    return false;
}

bool Dot::checkCollision(const SDL_Rect &other) {
    int closestX, closestY;

    if (collider.x < other.x) {
        closestX = other.x;
    } else if (collider.x > other.x + other.w) {
        closestX = other.x + other.w;
    } else {
        closestX = collider.x;
    }

    if (collider.y < other.y) {
        closestY = other.y;
    } else if (collider.y > other.y + other.h) {
        closestY = other.y + other.h;
    } else {
        closestY = collider.y;
    }

    if (distanceSquared(collider.x, collider.y, closestX, closestY) < collider.r * collider.r) {
        return true;
    }

    return false;
}

void Dot::shiftColliders() {
    collider.x = x;
    collider.y = y;
}

Circle& Dot::getCollider() {
    return collider;
}

double Dot::distanceSquared(int x1, int y1, int x2, int y2) {
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;

    return deltaX * deltaX + deltaY * deltaY;
}
