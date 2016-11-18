uint8_t values[6];
uint8_t enabled[6];

uint64_t globalTime;

uint8_t outputValues[64];


ISR(TIMER0_OVF_vect) {
    static uint8_t tick = 0;
    DDRB = outputValues[tick++];
    tick&=0x3f;
}

void setup() {
    // Disable pull ups.
    MCUCR |= 1<<PUD;

    DDRB = PB1<<1;
    PORTB = 1<<PB1;


    OCR0A = 64;

    TCCR0A = 0; // 1<<WGM01;
    TCCR0B = 0 << CS02 | 1<<CS01 | 1 << CS00;
    TIMSK = 1 << TOIE0;

    for (uint8_t i=0; i<6; ++i) {
        values[i] = i*3;
        enabled[i] = i!=5;
    }

    for (uint8_t i=0; i<64; ++i) {
        outputValues[i] = i<4 ? 255 : 0;
    }
}

void loop() {
    // values[1]++;
    // if (values[1] > 64) {
    //     values[1] = 0;
    // }
//     PORTB |= 1 << PB1;
}