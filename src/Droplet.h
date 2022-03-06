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

    int map(double value, double maxValue, int wantedMinValue,
            int wantedMaxValue) {
        double rounded =
            std::round(value / maxValue * (wantedMaxValue - wantedMinValue) +
                       wantedMinValue);
        return static_cast<int>(rounded);
    }

    double map(double value, double maxValue, double wantedMinValue,
               double wantedMaxValue) {
        return value / maxValue * (wantedMaxValue - wantedMinValue) +
               wantedMinValue;
    }

   public:
    static const double maxVel;
    static const double minVel;

    Droplet() {
        this->x = rand() % 640;
        this->y = rand() % 1000 - 500;
        this->z = rand() % 100;
        int minWidth = 1;
        int maxWidth = 3;
        this->width = map(z, 99, minWidth, maxWidth);
        int minLen = 10;
        int maxLen = 20;
        this->length = map(z, 99, minLen, maxLen);
        this->yVelocity = map(z, 99, minVel, maxVel);
    }

    void move(double deltaTime) {
        y += yVelocity * deltaTime;
        double gravity = map(z, 99, 0.0, 0.1);
        yVelocity += gravity * deltaTime;
        if (y > 480) {
            x = rand() % 640;
            y = rand() % 500 - 500;
            yVelocity = map(z, 99, minVel, maxVel);
        }
    }

    void draw(SDL_Surface* surface, Uint32 color) {
        DrawRectangle(surface, static_cast<int>(x), static_cast<int>(y), width,
                      length, color, color);
    }
};

const double Droplet::minVel = 3;
const double Droplet::maxVel = 5;

#endif