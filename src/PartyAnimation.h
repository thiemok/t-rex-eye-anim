#ifndef PARTY_ANIMATION_H
#define PARTY_ANIMATION_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

struct color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class PartyAnimation {

    public:
        PartyAnimation (Adafruit_NeoPixel* p);

        void setup();
        void loop();

        PartyAnimation* setNeoPixel(Adafruit_NeoPixel* p);

        uint8_t getStepDelay();
        PartyAnimation* setStepDelay(uint8_t delay);

        uint8_t getMinStrobes();
        PartyAnimation* setMinStrobes(uint8_t strobes);

        uint8_t getMaxStrobes();
        PartyAnimation* setMaxStrobes(uint8_t strobes);

    private:
        uint8_t selectNumStrobes();
        color selectInitialColor();
        uint32_t fadeColor(
            color color,
            uint8_t step,
            uint8_t totalSteps);
        uint8_t fadeValue(uint8_t initial, uint8_t step, uint8_t totalSteps);
        void setAllPixels(uint32_t c);

        Adafruit_NeoPixel* pixels;
        uint8_t animStepDelay;
        uint8_t minStrobes;
        uint8_t maxStrobes;
    
};

#endif
