#include <SDL.h>

#include <iostream>

#include "src/Draw.cpp"
#include "src/Droplet.h"
#include "src/Framework.h"

int main(int argc, char* argv[]) {
    const int windowWidth = 640;
    const int windowHeigth = 480;
    Framework fw(windowWidth, windowHeigth);
    SDL_Event event;
    SDL_Surface* screen = nullptr;
    bool running = true;
    const int dropletCount = 256;
    Droplet droplets[dropletCount];

    screen =
        SDL_CreateRGBSurface(0, fw.getWidth(), fw.getHeight(), 32, 0x00FF0000,
                             0x0000FF00, 0x000000FF, 0xFF000000);
    int black = SDL_MapRGB(screen->format, 0, 0, 0);
    int blue = SDL_MapRGB(screen->format, 56, 185, 208);

    srand(static_cast<unsigned int>(time(NULL)));
    Uint32 last = SDL_GetTicks();
    float gameTimeFactor = 10.0f;

    while (running) {
        Uint64 start = SDL_GetPerformanceCounter();

        // handle input
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        // change gamestate
        Uint32 current = SDL_GetTicks();
        float dT = (current - last) / gameTimeFactor;
        
        for (int i = 0; i < dropletCount; i++) {
            droplets[i].move(dT);
        }
        last = current;
        // display
        SDL_FillRect(screen, NULL, black);
        for (int i = 0; i < dropletCount; i++) {
            droplets[i].draw(screen, blue);
        }
        fw.update(screen);

        // fps
        Uint64 end = SDL_GetPerformanceCounter();

        float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
        std::cout << "Current FPS: " << 1.0f / elapsed << std::endl;
    }
    return 0;
}
