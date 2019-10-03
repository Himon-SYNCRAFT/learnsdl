#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Texture.hpp"
#include <string>
#include <iostream>


Texture::Texture() {
    texture = NULL;
    width = 0;
    height = 0;
}

Texture::~Texture() {
    free();
}

bool Texture::loadFromFile(std::string path) {
    free();

    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return false;
    }

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    if (newTexture == NULL) {
        printf("Unable to create texture %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }

    width = loadedSurface->w;
    height = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    texture = newTexture;
    return true;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font) {
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);

    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL Error: %s\n" , SDL_GetError());
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (!texture) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n" , SDL_GetError());
        return false;
    }

    width = textSurface->w;
    height = textSurface->h;

    SDL_FreeSurface(textSurface);

    return true;
}

void Texture::free() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = { x, y, width, height };

    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}

void Texture::setRenderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(texture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(texture, blending);
}

void Texture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture, alpha);
}
