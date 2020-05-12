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
#ifndef INITIAL_BRIGHTNESS_LOWER_BOUND
    #define INITIAL_BRIGHTNESS_LOWER_BOUND 64
#endif 
#ifndef FADE_HEADROOM
    #define FADE_HEADROOM 4
#endif

PartyAnimation::PartyAnimation(Adafruit_NeoPixel* p) {
    pixels = p;

    animStepDelay = DEFAULT_ANIM_STEP_DELAY;
    minStrobes = DEFAULT_ANIM_MIN_STROBES;
    maxStrobes = DEFAULT_ANIM_MAX_STROBES;
}

void PartyAnimation::setup() {
    pixels->clear();
    pixels->show();
}

void PartyAnimation::loop() {
    uint8_t strobes = selectNumStrobes();
    uint8_t steps = maxStrobes * FADE_HEADROOM;
    uint8_t stepsPerStrobe = steps / strobes;

    color color = selectInitialColor();

    for (uint8_t i = 0; i < steps; i++) {
        uint8_t partial = i % stepsPerStrobe;
        if (partial == 0) {
            setAllPixels(pixels->Color(color.r, color.g, color.b));
        } else {
            setAllPixels(
                fadeColor(color, partial, stepsPerStrobe)
            );
        }
        pixels->show();
        delay(animStepDelay);
    }
}

PartyAnimation* PartyAnimation::setNeoPixel(Adafruit_NeoPixel* p) {
    pixels = p;
    return this;
}

uint8_t PartyAnimation::getStepDelay() {
    return animStepDelay;
}

PartyAnimation* PartyAnimation::setStepDelay(uint8_t delay) {
    animStepDelay = delay;
    return this;
}

uint8_t PartyAnimation::getMinStrobes() {
    return minStrobes;
}
        
PartyAnimation* PartyAnimation::setMinStrobes(uint8_t strobes) {
    minStrobes = strobes;
    return this;
}

uint8_t PartyAnimation::getMaxStrobes() {
    return maxStrobes;
}
        
PartyAnimation* PartyAnimation::setMaxStrobes(uint8_t strobes) {
    maxStrobes = strobes;
    return this;
}

uint8_t PartyAnimation::selectNumStrobes() {
    return random(minStrobes, maxStrobes);
}

color PartyAnimation::selectInitialColor() {
    color c;

    c.r = random(0, 255);
    c.g = random(0, 255 - c.r);
    c.b = 255 - (c.r + c.g);

    
    return c;
}

uint32_t PartyAnimation::fadeColor(
    color color,
    uint8_t step,
    uint8_t totalSteps) {
        return pixels->Color(
            fadeValue(color.r, step, totalSteps),
            fadeValue(color.g, step, totalSteps),
            fadeValue(color.b, step, totalSteps)
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
