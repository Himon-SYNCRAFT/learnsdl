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

    collider_.r = WIDTH / 2;
    shiftColliders();

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

void Dot::move(const SDL_Rect &rectangle, const Circle &circle) {
    x_ += velocityX_;
    shiftColliders();

    if ((x_ - collider_.r < 0) || (x_ + collider_.r > SCREEN_WIDTH) || checkCollision(rectangle) || checkCollision(circle)) {
        x_ -= velocityX_;
        shiftColliders();
    }

    y_ += velocityY_;
    shiftColliders();

    if ((y_ - collider_.r < 0) || (y_ + collider_.r > SCREEN_HEIGHT) || checkCollision(rectangle) || checkCollision(circle)) {
        y_ -= velocityY_;
        shiftColliders();
    }
}

void Dot::render() {
    texture_.render(x_ - collider_.r, y_ - collider_.r);
}

bool Dot::checkCollision(const Circle &other) {
    int totalRadiusSquared = collider_.r + other.r;
    totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    return distanceSquared(collider_.x, collider_.y, other.x, other.y) < totalRadiusSquared;
}

bool Dot::checkCollision(const SDL_Rect &other) {
    int closestX, closestY;

    if (collider_.x < other.x) {
        closestX = other.x;
    } else if (collider_.x > other.x + other.w) {
        closestX = other.x + other.w;
    } else {
        closestX = collider_.x;
    }

    if (collider_.y < other.y) {
        closestY = other.y;
    } else if (collider_.y > other.y + other.h) {
        closestY = other.y + other.h;
    } else {
        closestY = collider_.y;
    }

    printf("pos: %d, %d\n", x_, y_);
    printf("collider: %d, %d\n", collider_.x, collider_.y);
    printf("closest: %d, %d\n", closestX, closestY);
    printf("other: %d, %d\n", other.x, other.y);

    double distance = distanceSquared(collider_.x, collider_.y, closestX, closestY);

    printf("distance: %f, r^2: %d\n", distance, collider_.r * collider_.r);

    return  distance < (collider_.r * collider_.r);
}

void Dot::shiftColliders() {
    collider_.x = x_;
    collider_.y = y_;
}

Circle& Dot::getCollider() {
    return collider_;
}

double Dot::distanceSquared(int x1, int y1, int x2, int y2) {
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;

    return deltaX * deltaX + deltaY * deltaY;
}
