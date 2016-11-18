int8_t values[6];

uint64_t time;

uint8_t outputValues[64];


ISR(TIMER0_COMPA_vect) {
    static int8_t tick = 0;
    static uint64_t globalTime = 0;
    ++globalTime;
    time = globalTime;
    ++tick;
    tick&=0x3f;
    DDRB = outputValues[tick];
}

void updateTable() {
    for (int i=0; i<64; ++i) {
        uint8_t toSet = 0;
        for (int j=0; j<6; ++j) {
            if (values[j]>i) {
                toSet |= 1<<j;
            }
        }
        outputValues[i] = toSet;
    }
}

void setup() {
    // Disable pull ups.
    MCUCR |= 1<<PUD;

    for (uint8_t i=0; i<6; ++i) {
        values[i] = 1;
    }

    updateTable();

    DDRB = 255;
    PORTB = 0;

    OCR0A = 128;

    TCCR0A = 1<<WGM01;
    TCCR0B = 1 << CS02 | 0 <<CS01 | 1 << CS00;
    TIMSK = 1 << OCIE0A;

}

void loop() {
    if (time % 1024 == 0) {
        for (uint8_t i=0; i<6; ++i) {
            int8_t toAdd = rand()%11 - 5;
            values[i] += toAdd;
            if (values[i] > 64) {
                values[i] = 64;
            } else if (values[i] < 10) {
                values[i] = 10;
            }
        }
        updateTable();
    }
}