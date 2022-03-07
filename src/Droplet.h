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

    static int dropletCount;
    static int dropletsInitialized;
    static const double maxVel;
    static const double minVel;

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

    int distribute(int arg){
        int a = Droplet::dropletCount;
        int x = arg;
        int value = (x*x/a);
        return value;
    }

   public:

    static void setDropletCount(const int dropletCount){
        Droplet::dropletCount = dropletCount;
    }

    Droplet() {
        Droplet::dropletsInitialized++;
        this->x = rand() % 640;
        this->y = rand() % 1000 - 500;
        this->z = distribute(Droplet::dropletsInitialized);
        int minWidth = 1;
        int maxWidth = 3;
        this->width = map(z, Droplet::dropletCount, minWidth, maxWidth);
        int minLen = 8;
        int maxLen = 20;
        this->length = map(z, Droplet::dropletCount, minLen, maxLen);
        this->yVelocity = map(z, Droplet::dropletCount, minVel, maxVel);
    }

    void move(double deltaTime) {
        y += yVelocity * deltaTime;
        double gravity = map(z, Droplet::dropletCount, 0.01, 0.1);
        yVelocity += gravity * deltaTime;
        if (y > 480) {
            x = rand() % 640;
            y = rand() % 500 - 500;
            yVelocity = map(z, Droplet::dropletCount, minVel, maxVel);
        }
    }

    void draw(SDL_Surface* surface, Uint32 color) {
        DrawRectangle(surface, static_cast<int>(x), static_cast<int>(y), width,
                      length, color, color);
    }
};

const double Droplet::minVel = 4;
const double Droplet::maxVel = 5;
int Droplet::dropletsInitialized = 0;
int Droplet::dropletCount = 0;

#endif