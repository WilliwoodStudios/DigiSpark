#include "util.h"
#include "light.h"

Light::Light() {
    mInit = false;
    mLevel = 255;
}

Light::~Light() {
    mInit = false;
}

void Light::init(uint8_t xPin, uint8_t yPin, uint8_t direction) {
    mXPin = xPin;
    mYPin = yPin;
    mDirection = direction;
    mInit = true;
}

void Light::show(uint8_t level) {
    write(mLevel >= level,mXPin,mDirection);
    write(mLevel >= level,mYPin,!mDirection);
    busyLoop();
    tristate(mXPin);
    tristate(mYPin);
}