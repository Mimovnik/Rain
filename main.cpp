#include <SDL.h>

#include <iostream>

class Framework {
    int width;
    int height;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

   public:
    Framework(int width, int height) {
        this->width = width;
        this->height = height;
        SDL_Init(SDL_INIT_EVERYTHING);
        // SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window,
        // &renderer);
        window = SDL_CreateWindow("Rain", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, width, height,
                                  SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    ~Framework() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

int main(int argc, char* argv[]) {
    Framework fw(640, 480);
    SDL_Delay(5000);

    return 0;
}
