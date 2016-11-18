const uint8_t PIN_COUNT = 5;

int8_t values[PIN_COUNT];
float offsets[PIN_COUNT];
float skews[PIN_COUNT];
float harmonic[PIN_COUNT][3];

uint64_t time;

ISR(TIMER0_COMPA_vect) {
    static int8_t tick = 0;
    static uint64_t globalTime = 0;
    ++globalTime;
    time = globalTime;
    ++tick;
    tick&=0x3f;
    uint8_t mask = 1;
    uint8_t toWrite = 0;
    for (uint8_t i=0; i<PIN_COUNT; ++i) {
        if (values[i] > tick) {
            toWrite |= mask;
        }
        mask <<= 1;
    }
    DDRB = toWrite;
}

float findHarmonic(float center) {
    return center * (1.0 + (rand()%21-10)/100);
}

void setup() {
    for (uint8_t i=0; i<PIN_COUNT; ++i) {
        values[i] = 1;
        offsets[i] = rand()%1000/1000.0 * 6;
        skews[i] = (100+(rand()%21-10))/100.0;
        for (uint8_t j=0; j<3; ++j) {
            harmonic[i][j] = findHarmonic(2<<j);
        }
    }

    // Disable pull ups.
    MCUCR |= 1<<PUD;

    DDRB = 0;
    PORTB = 0;

    OCR0A = 128;

    TCCR0A = 1<<WGM01;
    TCCR0B = 1 << CS02 | 0 <<CS01 | 1 << CS00;
    TIMSK = 1 << OCIE0A;

}

float angle;
float twoPi = 3.141597 * 2;

uint8_t generateValueForAngle(float angle,uint8_t which) {
    float toReturn = 0.6 * sin(angle);
    toReturn += 0.1 * sin(angle * harmonic[which][0]);
    toReturn += 0.1 * sin(angle * harmonic[which][1]);
    toReturn += 0.2 * sin(angle * harmonic[which][2]);
    toReturn *= 32;
    toReturn += 32;
    return toReturn;
}

void loop() {
    if (time % 1024 == 0) {
        angle += 0.08;
        if (angle > twoPi) {
            angle -= twoPi;
        }

        for (uint8_t i=0; i<PIN_COUNT; ++i) {
            values[i] = generateValueForAngle((angle+offsets[i])*skews[i],i);
        }
    }
}