/*
 * =====================================================================================
 *
 *       Filename:  Dot.hpp
 *
 *        Created:  03.10.2019 11:16:59
 *         Author:  Daniel Zawłocki
 *
 * =====================================================================================
 */
#pragma once

#include <SDL2/SDL.h>
#include "Texture.hpp"


struct Circle {
    int x, y;
    int r;
};

class Dot {

    public:
        static const int WIDTH = 20;
        static const int HEIGHT = 20;
        static const int VELOCITY = 10;

        Dot(SDL_Renderer* renderer, const int startX, const int startY);

        void handleEvent(SDL_Event& e);
        void move(const SDL_Rect &rectangle, const Circle &circle);
        void render();
        bool checkCollision(const Circle &other);
        bool checkCollision(const SDL_Rect  &other);
        double distanceSquared(int x1, int y1, int x2, int y2);
        Circle& getCollider();

    private:
        int x, y;
        int velocityX, velocityY;

        Texture texture;
        Circle collider;

        // Moves the collision circle relative to the dot's offset
        void shiftColliders();
};
