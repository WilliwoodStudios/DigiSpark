#include "util.h"
#include "light.h"

Light::Light() {
    mInit = false;
    mLevel = random();
}

Light::~Light() {
    mInit = false;
}

void Light::setLevel(uint8_t level) {
    mLevel = level;
}

void Light::init(uint8_t xPin, uint8_t yPin, uint8_t direction) {
    mXPin = xPin;
    mYPin = yPin;
    mDirection = direction;
    mInit = true;
}

void Light::show(uint8_t level) {
    write(mLevel > level,mXPin,mDirection);
    write(mLevel > level,mYPin,!mDirection);
    busyLoop();
    tristate(mXPin);
    tristate(mYPin);
}

const uint8_t spread = 30;

void Light::tick(uint32_t time) {
    uint8_t delta = random()%spread;
    if (delta >= spread/2) {
        mLevel += delta - (spread/2);
        if (mLevel > 64) {
            mLevel = 64;
        }
    } else {
        mLevel -= delta;
        if (mLevel > 64) {
            mLevel = 0;
        }
    }
}