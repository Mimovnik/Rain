#ifndef DROPLET_H
#define DROPLET_H

#include <stdlib.h>
#include <time.h>
#include "Draw.cpp"

class Droplet {
    int x;
    int y;
    int length;
    int width;
    int v;

   public:
    Droplet() {
        this->x = rand() % 640;
        this->y = rand() % 480;
        this->width = 1;
        this->length = 5;
        this->v = 1;
    }

    void move(double deltaTime){
        y += v * deltaTime;
        y = y % (480 - length);
    }

    void draw(SDL_Surface* surface, Uint32 color) {
        DrawRectangle(surface, x, y, width, length, color, color);
    }
};

#endif