#include "light.h"

uint8_t xPins[] = {1<<PB0,1<<PB2};
uint8_t yPins[] = {1<< PB3,1<<PB4};

const uint8_t MAX_LEVEL = 64;

#define LIGHT_COUNT 8

Light lights[LIGHT_COUNT];

inline void tristate(uint8_t pin) {
    DDRB &= ~pin;
}

inline void write(uint8_t enable, uint8_t pin, uint8_t value) {
    DDRB |= pin;
    if (value) {
        PORTB |= pin;
    } else {
        PORTB &= ~pin;
    }
}

uint32_t time = 0;

void tick() {
    time++;
    for (uint8_t i=0; i<LIGHT_COUNT; ++i) {
        lights[i].tick(time);
    }
}

void setup() {
    // Disable pull ups.
    MCUCR |= 1<<PUD;

    tristate(1<<PB0);
    tristate(1<<PB2);
    tristate(1<<PB3);
    tristate(1<<PB4);

    uint8_t lightIndex = 0;

    for (uint8_t direction = 0; direction < 2; ++direction) {
        for (uint8_t x=0; x<2; ++x) {
            for (uint8_t y =0; y<2; ++y) {
                Light & light = lights[lightIndex];
                light.init(xPins[x],yPins[y],direction);
            }
            ++lightIndex;
        }
    }
}

inline void busyLoop() {
    for (int i=0; i<1000; ++i) {
        // NOP
    }
}

void loop() {
    for (uint8_t brightness = 0; brightness < MAX_LEVEL; ++ brightness) {
        for (uint8_t i =0; i < LIGHT_COUNT; ++i) {
            lights[i].show(brightness);
        }
    }
}