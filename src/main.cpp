#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define P0 0
#define P2 2

#define EYE_LEFT 0
#define EYE_RIGHT 1

#define PIXEL_PER_EYE 4

#define ANIM_STEP_DELAY 65
#define EYES_CLOSED_DURATION 5 * ANIM_STEP_DELAY

#define MIN_SLEEP_BETWEEN_ANIM 2
#define MAX_SLEEP_BETWEEN_ANIM 20

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(8, P0, NEO_GRB + NEO_KHZ800);
uint32_t eyeColor = pixels.Color(64, 0, 0);
uint32_t ledOff = pixels.Color(0, 0, 0);

void seedRNG() {
    pinMode(P2, INPUT);
    randomSeed(analogRead(P2));
}

void openEyes() {
    uint8_t startIndexLeft = PIXEL_PER_EYE - 1;
    uint8_t startIndexRight = (PIXEL_PER_EYE * 2) - 1;

    pixels.setPixelColor(startIndexLeft, eyeColor);
    pixels.setPixelColor(startIndexRight, eyeColor);
    pixels.show();
    delay(ANIM_STEP_DELAY);

    pixels.setPixelColor(startIndexLeft - 1, eyeColor);
    pixels.setPixelColor(startIndexLeft - 2, eyeColor);
    pixels.setPixelColor(startIndexRight - 1, eyeColor);
    pixels.setPixelColor(startIndexRight - 2, eyeColor);
    pixels.show();
    delay(ANIM_STEP_DELAY);

    pixels.setPixelColor(startIndexLeft - 3, eyeColor);
    pixels.setPixelColor(startIndexRight - 3, eyeColor);
    pixels.show();
}

void closeEye(uint8_t eye) {
    if (eye > EYE_RIGHT) {
        return;
    }

    uint8_t startIndex = eye * PIXEL_PER_EYE;

    pixels.setPixelColor(startIndex, ledOff);
    pixels.show();
    delay(ANIM_STEP_DELAY);

    pixels.setPixelColor(startIndex + 1, ledOff);
    pixels.setPixelColor(startIndex + 2, ledOff);
    pixels.show();
    delay(ANIM_STEP_DELAY);

    pixels.setPixelColor(startIndex + 3, ledOff);
    pixels.show();
}

void closeBothEyes() {
    uint8_t startIndexLeft = EYE_LEFT * PIXEL_PER_EYE;
    uint8_t startIndexRight = EYE_RIGHT * PIXEL_PER_EYE;

    pixels.setPixelColor(startIndexLeft, ledOff);
    pixels.setPixelColor(startIndexRight, ledOff);
    pixels.show();
    delay(ANIM_STEP_DELAY);

    pixels.setPixelColor(startIndexLeft + 1, ledOff);
    pixels.setPixelColor(startIndexLeft + 2, ledOff);
    pixels.setPixelColor(startIndexRight + 1, ledOff);
    pixels.setPixelColor(startIndexRight + 2, ledOff);
    pixels.show();
    delay(ANIM_STEP_DELAY);

    pixels.setPixelColor(startIndexLeft + 3, ledOff);
    pixels.setPixelColor(startIndexRight + 3, ledOff);
    pixels.show();
}

void closeRandomEye() {
    uint8_t eye = random(EYE_RIGHT + 2);

    if (eye > EYE_RIGHT) {
        closeBothEyes();
    } else {
        closeEye(eye);
    }
}

void doRandomSleep() {
    double sleepAmount = random(MIN_SLEEP_BETWEEN_ANIM, MAX_SLEEP_BETWEEN_ANIM) * 1000;
    delay(sleepAmount);
}

void setup() {
    /* Setup serial for debug */
    Serial.begin(115200);

    pixels.begin();

    seedRNG();
    pixels.clear();
    pixels.setBrightness(64);
    pixels.show();

    openEyes();
}

void loop() {
    closeRandomEye();
    delay(EYES_CLOSED_DURATION);
    openEyes();

    doRandomSleep();
}