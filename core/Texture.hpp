#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>



class Texture {
    public:
        Texture();
        ~Texture();

        void setRenderer(SDL_Renderer* renderer);

        bool loadFromFile(std::string path);

        bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font);

        // Deallocates texture
        void free();

        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        void setBlendMode(SDL_BlendMode blending);

        void setAlpha(Uint8 alpha);

        // Render texture at given point
        void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);


        int getWidth();
        int getHeight();

    private:
        SDL_Texture* texture;

        int width;
        int height;
        SDL_Renderer* renderer;
};
