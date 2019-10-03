/*
 * =====================================================================================
 *
 *       Filename:  Button.cpp
 *
 *        Created:  02.10.2019 09:19:26
 *         Author:  Daniel Zawłocki
 *
 * =====================================================================================
 */
#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "Button.hpp"
#include <cstdio>


const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGTH = 200;


Button::Button() {
    position.x = 0;
    position.y = 0;

    currentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void Button::handleEvent(SDL_Event * e) {
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        if (x < position.x) {
            inside = false;
        } else if (x > position.x + BUTTON_WIDTH) {
            inside = false;
        } else if (y < position.y) {
            inside = false;
        } else if (y > position.y + BUTTON_HEIGTH) {
            inside = false;
        }

        if (!inside) {
            currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        } else {
            switch (e->type) {
                case SDL_MOUSEMOTION:
                    currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;

                case SDL_MOUSEBUTTONUP:
                    currentSprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}

void Button::render(Texture* texture, SDL_Rect* spriteClips) {
    texture->render(position.x, position.y, &spriteClips[currentSprite]);
}
