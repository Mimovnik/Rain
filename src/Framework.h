#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <SDL.h>
class Framework {
    int width;
    int height;
    SDL_Window* window = nullptr;
    SDL_Texture* screenTexture = nullptr;
    SDL_Renderer* renderer = nullptr;

   public:
    Framework(int width_, int height_) : width(width_), height(height_) {
        this->width = width;
        this->height = height;
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window,
                                    &renderer);
        SDL_SetWindowTitle(window, "Rain");
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        screenTexture =
            SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                              SDL_TEXTUREACCESS_STREAMING, width, height);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    ~Framework() {
        SDL_DestroyTexture(screenTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void update(SDL_Surface* surface) {
        // Copy surface to texture
        SDL_DestroyTexture(screenTexture);
        screenTexture = SDL_CreateTextureFromSurface(renderer, surface);
        // Copy texture to renderer
        SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    int getWidth() { return width; }
    int getHeight() { return height; }
};

#endif