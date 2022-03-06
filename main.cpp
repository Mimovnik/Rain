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

    const int black = SDL_MapRGB(screen->format, 0, 0, 0);
    const int white = SDL_MapRGB(screen->format, 255, 255, 255);
    const int blue = SDL_MapRGB(screen->format, 0, 121, 255);
    const int lightPurple = SDL_MapRGB(screen->format, 230, 230, 250);
    const int purple = SDL_MapRGB(screen->format, 148, 43, 226);
    const int green = SDL_MapRGB(screen->format, 9, 164, 0);
    const int lightGreen = SDL_MapRGB(screen->format, 204, 255, 202);
    const int orange = SDL_MapRGB(screen->format, 255, 122, 0);
    const int lightOrange = SDL_MapRGB(screen->format, 255, 236, 191);

    const int colorCount = 4;
    const int rainColors[colorCount] = {blue, purple, green, orange};
    const int backColors[colorCount] = {white, lightPurple, lightGreen,
                                        lightOrange};

    int rainColor = rainColors[0];
    int backgroundColor = backColors[0];
    int currentColors = 0;

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
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        currentColors++;
                        currentColors %= colorCount;
                        backgroundColor = backColors[currentColors];
                        rainColor = rainColors[currentColors];
                    }
                    break;
                case SDL_KEYDOWN:
                    SDL_Keycode keySym = event.key.keysym.sym;
                    if (keySym == SDLK_b) {
                        currentColors = 0;
                    }
                    if (keySym == SDLK_p) {
                        currentColors = 1;
                    }
                    if (keySym == SDLK_g) {
                        currentColors = 2;
                    }
                    if (keySym == SDLK_o) {
                        currentColors = 3;
                    }
                    if (keySym == SDLK_SPACE) {
                        currentColors++;
                        currentColors %= colorCount;
                    }
                    backgroundColor = backColors[currentColors];
                    rainColor = rainColors[currentColors];
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
        SDL_FillRect(screen, NULL, backgroundColor);
        for (int i = 0; i < dropletCount; i++) {
            droplets[i].draw(screen, rainColor);
        }
        fw.update(screen);

        // fps
        Uint64 end = SDL_GetPerformanceCounter();

        float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
        // std::cout << "Current FPS: " << 1.0f / elapsed << std::endl;
    }
    return 0;
}
