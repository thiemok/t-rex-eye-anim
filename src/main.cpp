#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "BlinkAnimation.h"

#define P0 0
#define P1 1
#define P2 2
#define P3 3
#define P4 4
#define P5 5

#define PIXEL_PER_EYE 4

BlinkAnimation* blink;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_PER_EYE * 2, P0, NEO_GRB + NEO_KHZ800);

void seedRNG() {
    pinMode(P2, INPUT);
    randomSeed(analogRead(P2));
}

void setupModeSwitch() {
    pinMode(P4, INPUT);
}

bool isPartyMode() {
    return digitalRead(P4) == LOW;
}

void partyLoop() {

}

void partySetup() {

}

void setup() {
    /* Setup serial for debug */
    Serial.begin(115200);

    pixels.begin();

    seedRNG();

    setupModeSwitch();

    pixels.clear();
    pixels.setBrightness(128);
    pixels.show();

    blink = &BlinkAnimation(&pixels);
    blink->setMinSleepBetweenBlink(2)
        ->setMaxSleepBetweenBlink(20)
        ->setEyeColor(pixels.Color(128, 0, 0))
        ->setStepDelay(55);
    

    if (isPartyMode()) {
        partySetup();
    } else {
        blink->setup();
    }
}

void loop() {
    if (isPartyMode()) {
        partyLoop();
    } else {
        blink->loop();
    }
}