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


class Dot {

    public:
        static const int WIDTH = 20;
        static const int HEIGHT = 20;
        static const int VELOCITY = 10;

        Dot(SDL_Renderer* renderer);

        void handleEvent(SDL_Event& e);
        void move();
        void render();

    private:
        int x, y;
        int velocityX, velocityY;
        Texture texture;
};
