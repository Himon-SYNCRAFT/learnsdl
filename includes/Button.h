/*
 * =====================================================================================
 *
 *       Filename:  Button.hpp
 *
 *        Created:  02.10.2019 09:17:10
 *         Author:  Daniel Zawłocki
 *
 * =====================================================================================
 */
#pragma once
#include "SDL2/SDL.h"
#include "Texture.h"


enum ButtonSprite {
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};


class Button {

    public:
        Button();

        void setPosition(int x, int y);

        void handleEvent(SDL_Event* e);

        void render(Texture* texture, SDL_Rect* spriteClips);

        SDL_Point getPosition() { return position_; }

    private:
        SDL_Point position_;
        ButtonSprite currentSprite_;
};
