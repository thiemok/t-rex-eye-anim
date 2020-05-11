#include "PartyAnimation.h"

#ifndef DEFAULT_ANIM_STEP_DELAY
    #define DEFAULT_ANIM_STEP_DELAY 100
#endif
#ifndef DEFAULT_ANIM_MIN_STROBES
    #define DEFAULT_ANIM_MIN_STROBES 1
#endif
#ifndef DEFAULT_ANIM_MAX_STROBES
    #define DEFAULT_ANIM_MAX_STROBES 5
#endif
#ifndef DEFAULT_MIN_SLEEP_BETWEEN_ANIM
    #define DEFAULT_MIN_SLEEP_BETWEEN_ANIM 1
#endif
#ifndef DEFAULT_MAX_SLEEP_BETWEEN_ANIM
    #define DEFAULT_MAX_SLEEP_BETWEEN_ANIM 5
#endif
#ifndef INITIAL_BRIGHTNESS_LOWER_BOUND
    #define INITIAL_BRIGHTNESS_LOWER_BOUND 64
#endif 

PartyAnimation::PartyAnimation(Adafruit_NeoPixel* pixels) {
    this->pixels = pixels;

    this->animStepDelay = DEFAULT_ANIM_STEP_DELAY;
    this->minStrobes = DEFAULT_ANIM_MIN_STROBES;
    this->maxStrobes = DEFAULT_ANIM_MAX_STROBES;
    this->minSleepBetweenStrobes = DEFAULT_MIN_SLEEP_BETWEEN_ANIM;
    this->maxSleepBetweenStrobes = DEFAULT_MAX_SLEEP_BETWEEN_ANIM;
}

void PartyAnimation::setup() {
    pixels->clear();
    pixels->show();
}

void PartyAnimation::loop() {
uint8_t strobes = selectNumStrobes();
uint8_t steps = maxStrobes * 2;
uint8_t stepsPerStrobe = steps / strobes;

uint8_t r = selectInitialColorValue();
uint8_t g = selectInitialColorValue();
uint8_t b = selectInitialColorValue();

for (uint8_t i = 0; i < steps; i++) {
    uint8_t partial = i % stepsPerStrobe;
    if (partial == 0) {
        setAllPixels(pixels->Color(r, g, b));
    } else {
        setAllPixels(
            fadeColor(r, g, b, partial, stepsPerStrobe)
        );
    }
    pixels->show();
    delay(animStepDelay);
}

doRandomSleep();
}

PartyAnimation* PartyAnimation::setNeoPixel(Adafruit_NeoPixel* pixels) {
    this->pixels = pixels;
    return this;
}

uint8_t PartyAnimation::getStepDelay() {
    return this->animStepDelay;
}

PartyAnimation* PartyAnimation::setStepDelay(uint8_t delay) {
    this->animStepDelay = delay;
    return this;
}

uint8_t PartyAnimation::getMinStrobes() {
    return this->minStrobes;
}
        
PartyAnimation* PartyAnimation::setMinStrobes(uint8_t strobes) {
    this->minStrobes = strobes;
    return this;
}

uint8_t PartyAnimation::getMaxStrobes() {
    return this->maxStrobes;
}
        
PartyAnimation* PartyAnimation::setMaxStrobes(uint8_t strobes) {
    this->maxStrobes = strobes;
    return this;
}

unsigned long PartyAnimation::getMinSleepBetweenStrobes() {
    return this->minSleepBetweenStrobes;
}

PartyAnimation* PartyAnimation::setMinSleepBetweenStrobes(unsigned long sleep) {
    this->minSleepBetweenStrobes = sleep;
    return this;
}

unsigned long PartyAnimation::getMaxSleepBetweenStrobes() {
    return this->maxSleepBetweenStrobes;
}
        
PartyAnimation* PartyAnimation::setMaxSleepBetweenStrobes(unsigned long sleep) {
    this->maxSleepBetweenStrobes = sleep;
    return this;
}

uint8_t PartyAnimation::selectNumStrobes() {
    return random(minStrobes, maxStrobes);
}

uint8_t PartyAnimation::selectInitialColorValue() {
    return random(INITIAL_BRIGHTNESS_LOWER_BOUND, 255);
}

uint32_t PartyAnimation::fadeColor(
    uint8_t initialR,
    uint8_t initialG,
    uint8_t initialB,
    uint8_t step,
    uint8_t totalSteps) {
        return pixels->Color(
            fadeValue(initialR, step, totalSteps),
            fadeValue(initialG, step, totalSteps),
            fadeValue(initialB, step, totalSteps)
        );
    }

uint8_t PartyAnimation::fadeValue(uint8_t initial, uint8_t step, uint8_t totalSteps) {
    return initial - (step * (initial / totalSteps));
}

void PartyAnimation::setAllPixels(uint32_t c) {
    for (uint8_t i = 0; i < pixels->numPixels(); i++) {
        pixels->setPixelColor(i, c);
    }
    
}

void PartyAnimation::doRandomSleep() {
    double sleepAmount = random(minSleepBetweenStrobes, maxSleepBetweenStrobes) * 1000;
    delay(sleepAmount);
}

