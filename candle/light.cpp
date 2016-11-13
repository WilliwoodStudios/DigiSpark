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

void Light::tick(uint32_t time) {
    --mLevel;
    if (mLevel==0) {
        mLevel = 64;
    }
}