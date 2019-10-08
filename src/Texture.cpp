#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Texture.h"
#include <string>
#include <iostream>


Texture::Texture() {
    texture_ = NULL;
    width_ = 0;
    height_ = 0;
}

Texture::~Texture() {
    free();
}

bool Texture::loadFromFile(const std::string& path) {
    free();

    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return false;
    }

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
    newTexture = SDL_CreateTextureFromSurface(renderer_, loadedSurface);

    if (newTexture == nullptr) {
        printf("Unable to create texture_ %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }

    width_ = loadedSurface->w;
    height_ = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    texture_ = newTexture;
    return true;
}

bool Texture::loadFromRenderedText(const std::string& textureText, SDL_Color textColor, TTF_Font* font) {
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);

    if (textSurface == nullptr) {
        printf("Unable to render text surface! SDL Error: %s\n" , SDL_GetError());
        return false;
    }

    texture_ = SDL_CreateTextureFromSurface(renderer_, textSurface);

    if (!texture_) {
        printf("Unable to create texture_ from rendered text! SDL Error: %s\n" , SDL_GetError());
        return false;
    }

    width_ = textSurface->w;
    height_ = textSurface->h;

    SDL_FreeSurface(textSurface);

    return true;
}

void Texture::free() {
    if (texture_ != nullptr) {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
        width_ = 0;
        height_ = 0;
    }
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = { x, y, width_, height_ };

    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer_, texture_, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth() {
    return width_;
}

int Texture::getHeight() {
    return height_;
}

void Texture::setRenderer(SDL_Renderer* renderer) {
    this->renderer_ = renderer;
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(texture_, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(texture_, blending);
}

void Texture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture_, alpha);
}
