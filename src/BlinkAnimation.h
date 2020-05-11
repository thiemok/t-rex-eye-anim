#ifndef BLINK_ANIMATION_H
#define BLINK_ANIMATION_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class BlinkAnimation {

    public:
        BlinkAnimation(Adafruit_NeoPixel* pixels);

        void setup();
        void loop();

        BlinkAnimation* setNeoPixel(Adafruit_NeoPixel* pixels);

        unsigned long getMinSleepBetweenBlink();
        BlinkAnimation* setMinSleepBetweenBlink(unsigned long sleep);

        unsigned long getMaxSleepBetweenBlink();
        BlinkAnimation* setMaxSleepBetweenBlink(unsigned long sleep);

        uint32_t getEyeColor();
        BlinkAnimation* setEyeColor(uint32_t color);

        uint8_t getStepDelay();
        BlinkAnimation* setStepDelay(uint8_t delay);

    private:
        void openEyes();
        void closeRandomEye();
        void closeBothEyes();
        void closeEye(uint8_t eye);
        void doRandomSleep();

        Adafruit_NeoPixel* pixels;
        unsigned long minSleepBetweenBlink;
        unsigned long maxSleepBetweenBlink;
        uint32_t eyeColor;
        uint8_t animStepDelay;
};

#endif
