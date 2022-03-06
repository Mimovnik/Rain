#ifndef DROPLET_H
#define DROPLET_H

#include <stdlib.h>
#include <time.h>

#include "Draw.cpp"

class Droplet {
    double x;
    double y;
    double z;
    int length;
    int width;
    double yVelocity;

   public:
    Droplet() {
        this->x = rand() % 640;
        this->y = rand() % 1000 - 500;
        // this->z = rand() % 5 + 1;
        this->width = 1;
        int minLen = 10;
        int maxLen = 20;
        this->length = rand() % (maxLen - minLen) + minLen;
        this->yVelocity = rand() % 3 + 2;
    }

    void move(double deltaTime) {
        y += yVelocity * deltaTime;
        yVelocity += 0.05 * deltaTime;
        if (y > 480) {
            y = rand() % 500 - 500;
            yVelocity = rand() % 3 + 2;
        }
    }

    void draw(SDL_Surface* surface, Uint32 color) {
        DrawRectangle(surface, static_cast<int>(x), static_cast<int>(y), width,
                      length, color, color);
    }
};

#endif