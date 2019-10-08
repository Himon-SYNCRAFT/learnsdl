#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>



class Texture {
    public:
        Texture();
        ~Texture();

        void setRenderer(SDL_Renderer* renderer);

        bool loadFromFile(const std::string& path);

        bool loadFromRenderedText(const std::string& textureText, SDL_Color textColor, TTF_Font* font);

        // Deallocates texture_
        void free();

        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        void setBlendMode(SDL_BlendMode blending);

        void setAlpha(Uint8 alpha);

        // Render texture_ at given point
        void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);


        int getWidth();
        int getHeight();

    private:
        SDL_Texture* texture_;

        int width_;
        int height_;
        SDL_Renderer* renderer_;
};
