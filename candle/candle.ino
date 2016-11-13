#include "light.h"
#include "util.h"


uint8_t xPins[] = {1<<PB0,1<<PB2};
uint8_t yPins[] = {1<<PB3,1<<PB4};

const uint8_t MAX_LEVEL = 64;

#define LIGHT_COUNT 8

Light lights[LIGHT_COUNT];

uint32_t time = 0;
uint8_t light = 0;

void tick() {
    uint8_t val = (PORTB & (1<<PB1)) != 0;
    val = !val;
    if (val) {
        PORTB |= 1<< PB1;
    } else {
        PORTB &= ~(1<<PB1);
    }
    // time++;
    for (uint8_t i=0; i<LIGHT_COUNT; ++i) {
        lights[i].tick(time);
    }
    // light = !light;
    // if (light) {
    //     PORTB |= 1<<PB1;
    // } else {
    //     PORTB &= ~(1<<PB1);
    // }
}

ISR(TIMER0_OVF_vect)
{
    tick();
}


// Cameron voltage: 2.1 @ 20mA
// Rob voltage: 2 @ 15ma


void setup() {
    TCCR0A = 0; // (1 << WGM01);             //CTC mode
    TCCR0B = (5 << CS00);              // div 1024
    // OCR0A = 255; // F_CPU/8 * 0.000050 - 1;    // 50us compare value
    //    TIMSK |= (1<<OCIE0A);              //if you want interrupt

    // TIMSK |= (1<<TOIE0);

    // Disable pull ups.
    MCUCR |= 1<<PUD;

    DDRB |= (1 << PB1);
    PORTB |= (1 << PB1);

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
                light.setLevel(lightIndex); // MAX_LEVEL);
                ++lightIndex;
            }
        }
    }
}

uint32_t iterations = 0;
void loop() {
    ++iterations;
    if (iterations == 10) {
        iterations = 0;
        tick();
    }
    for (uint8_t brightness = 0; brightness < MAX_LEVEL; ++ brightness) {
        for (uint8_t i =0; i < LIGHT_COUNT; ++i) {
            lights[i].show(brightness);
        }
    }
}