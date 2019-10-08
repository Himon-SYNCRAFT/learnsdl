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
#include <cstdio>
#include "Texture.h"
#include "Button.h"


const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;


Button::Button() {
    position_.x = 0;
    position_.y = 0;

    currentSprite_ = BUTTON_SPRITE_MOUSE_OUT;
}

void Button::setPosition(int x, int y) {
    position_.x = x;
    position_.y = y;
}

void Button::handleEvent(SDL_Event * e) {
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool outside = x < position_.x || x > position_.x + BUTTON_WIDTH || y < position_.y || y > position_.y + BUTTON_HEIGHT;

        if (outside) {
            currentSprite_ = BUTTON_SPRITE_MOUSE_OUT;
        } else {
            switch (e->type) {
                case SDL_MOUSEMOTION:
                    currentSprite_ = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    currentSprite_ = BUTTON_SPRITE_MOUSE_DOWN;
                    break;

                case SDL_MOUSEBUTTONUP:
                    currentSprite_ = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}

void Button::render(Texture* texture, SDL_Rect* spriteClips) {
    texture->render(position_.x, position_.y, &spriteClips[currentSprite_]);
}
