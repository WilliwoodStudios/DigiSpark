#ifndef _LIGHT_H
#define _LIGHT_H

#include "Arduino.h"

class Light {
public: 
    Light();
    virtual ~Light();

    void tick(uint32_t time);
    void show(uint8_t level);

    void init(uint8_t xPin, uint8_t yPin, uint8_t direction);

    void setLevel(uint8_t level);
private:
    uint8_t mLevel;

    uint8_t rampStart;
    uint8_t rampEnd;
    uint32_t timeStart;
    uint32_t timeEnd;

    uint8_t mXPin;
    uint8_t mYPin;
    uint8_t mDirection;

    uint8_t mInit;
};

#endif

