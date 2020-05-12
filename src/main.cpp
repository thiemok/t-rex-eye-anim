#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "BlinkAnimation.h"
#include "PartyAnimation.h"

#ifdef ARDUINO_AVR_DIGISPARK
    #define P0 0
    #define P1 1
    #define P2 2
    #define P3 3
    #define P4 4
    #define P5 5

    #define NEO_PIXEL_PIN P0
    #define NOISE_PIN P2
    #define SWITCH_PIN P4
#elif defined(ARDUINO_ESP8266_WEMOS_D1MINI)
    #define NEO_PIXEL_PIN D2
    #define NOISE_PIN A0
    #define SWITCH_PIN D6
#else
    #define NEO_PIXEL_PIN 0
    #define NOISE_PIN 1
    #define SWITCH_PIN 2
#endif

#define PIXEL_PER_EYE 4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_PER_EYE * 2, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

BlinkAnimation blink = BlinkAnimation(&pixels);
PartyAnimation party = PartyAnimation(&pixels);


void seedRNG() {
    pinMode(NOISE_PIN, INPUT);
    randomSeed(analogRead(NOISE_PIN));
}

void setupModeSwitch() {
    pinMode(SWITCH_PIN, INPUT);
}

bool isPartyMode() {
    return digitalRead(SWITCH_PIN) == LOW;
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

    blink.setMinSleepBetweenBlink(2)
        ->setMaxSleepBetweenBlink(20)
        ->setEyeColor(pixels.Color(128, 0, 0))
        ->setStepDelay(55);

    party.setStepDelay(125);
    

    if (isPartyMode()) {
        party.setup();
    } else {
        blink.setup();
    }
}

void loop() {
    if (isPartyMode()) {
        party.loop();
    } else {
        blink.loop();
    }
}