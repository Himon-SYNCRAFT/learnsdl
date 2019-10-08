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
#include "Texture.h"

struct Circle {
    int x, y;
    int r;
};

class Dot {

    public:
        static const int WIDTH = 20;
        static const int HEIGHT = 20;
        static const int VELOCITY = 10;

        Dot(SDL_Renderer *renderer, int startX, int startY);

        void handleEvent(SDL_Event &e);
        void move();
        void render(int camX, int camY);
        int getX() { return x_; };
        int getY() { return y_; };

    private:
        int x_, y_;
        int velocityX_, velocityY_;

        Texture texture_;
};
