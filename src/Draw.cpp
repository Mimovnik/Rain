#ifndef DRAW_CPP
#define DRAW_CPP

#include <SDL.h>
#include <iostream>

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
    if(y >= 0 && y <= surface->h){
    SDL_LockSurface(surface);
    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
    *(Uint32*)p = color;
    SDL_UnlockSurface(surface);
    } else {
        std::cout << "Cannot draw pixel outside of surface\n";
    }
};

// rysowanie linii o długości l w pionie (gdy dx = 0, dy = 1)
// bądź poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface* surface, int x, int y, int length, int dx, int dy,
              Uint32 color) {
    for (int i = 0; i < length; i++) {
        DrawPixel(surface, x, y, color);
        x += dx;
        y += dy;
    };
};

void DrawRectangle(SDL_Surface* surface, int x, int y, int side1, int side2,
                   Uint32 outlineColor, Uint32 fillColor) {
    int i;
    DrawLine(surface, x, y, side2, 0, 1, outlineColor);
    DrawLine(surface, x + side1 - 1, y, side2, 0, 1, outlineColor);
    DrawLine(surface, x, y, side1, 1, 0, outlineColor);
    DrawLine(surface, x, y + side2 - 1, side1, 1, 0, outlineColor);
    for (i = y + 1; i < y + side2 - 1; i++)
        DrawLine(surface, x + 1, i, side1 - 2, 1, 0, fillColor);
};

#endif