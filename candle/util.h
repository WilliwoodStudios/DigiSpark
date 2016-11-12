#ifndef _UTIL_H
#define _UTIL_H

#include "Arduino.h"

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

inline void busyLoop() {
    
}

#endif