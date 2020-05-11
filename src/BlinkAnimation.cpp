#include "BlinkAnimation.h"

#ifndef DEFAULT_MIN_SLEEP_BETWEEN_ANIM
    #define DEFAULT_MIN_SLEEP_BETWEEN_ANIM 1
#endif
#ifndef DEFAULT_MAX_SLEEP_BETWEEN_ANIM
    #define DEFAULT_MAX_SLEEP_BETWEEN_ANIM 5
#endif
#ifndef DEFAULT_ANIM_STEP_DELAY
    #define DEFAULT_ANIM_STEP_DELAY 120
#endif
#ifndef EYES_CLOSED_DURATION
    #define EYES_CLOSED_DURATION 10
#endif
#ifndef EYE_LEFT
    #define EYE_LEFT 0
#endif
#ifndef EYE_RIGHT
    #define EYE_RIGHT 1
#endif

BlinkAnimation::BlinkAnimation(Adafruit_NeoPixel* pixels) {
    this->pixels = pixels;

    this->minSleepBetweenBlink = DEFAULT_MIN_SLEEP_BETWEEN_ANIM;
    this->maxSleepBetweenBlink = DEFAULT_MAX_SLEEP_BETWEEN_ANIM;
    this->eyeColor = pixels->Color(255, 255, 255);
    this->animStepDelay = DEFAULT_ANIM_STEP_DELAY;
}

void BlinkAnimation::setup() {
    openEyes();
}

void BlinkAnimation::loop() {
    closeRandomEye();
    delay(EYES_CLOSED_DURATION * animStepDelay);
    openEyes();

    doRandomSleep();
}

BlinkAnimation* BlinkAnimation::setNeoPixel(Adafruit_NeoPixel* pixels) {
    this->pixels = pixels;
}

unsigned long BlinkAnimation::getMinSleepBetweenBlink() {
    return this->minSleepBetweenBlink;
}

BlinkAnimation* BlinkAnimation::setMinSleepBetweenBlink(unsigned long sleep) {
    this->minSleepBetweenBlink = sleep;
    return this;
}

unsigned long BlinkAnimation::getMaxSleepBetweenBlink() {
    return this->maxSleepBetweenBlink;
}
        
BlinkAnimation* BlinkAnimation::setMaxSleepBetweenBlink(unsigned long sleep) {
    this->maxSleepBetweenBlink = sleep;
    return this;
}

uint32_t BlinkAnimation::getEyeColor() {
    return this->eyeColor;
}

BlinkAnimation* BlinkAnimation::setEyeColor(uint32_t color) {
    this->eyeColor = color;
    return this;
}

uint8_t BlinkAnimation::getStepDelay() {
    return this->animStepDelay;
}

BlinkAnimation* BlinkAnimation::setStepDelay(uint8_t delay) {
    this->animStepDelay = delay;
    return this;
}

void BlinkAnimation::openEyes() {
    uint16_t pixelPerEye = pixels->numPixels() / 2;
    uint8_t startIndexLeft = pixelPerEye - 1;
    uint8_t startIndexRight = (pixelPerEye * 2) - 1;

    pixels->setPixelColor(startIndexLeft, eyeColor);
    pixels->setPixelColor(startIndexRight, eyeColor);
    pixels->show();
    delay(animStepDelay);

    pixels->setPixelColor(startIndexLeft - 1, eyeColor);
    pixels->setPixelColor(startIndexLeft - 2, eyeColor);
    pixels->setPixelColor(startIndexRight - 1, eyeColor);
    pixels->setPixelColor(startIndexRight - 2, eyeColor);
    pixels->show();
    delay(animStepDelay);

    pixels->setPixelColor(startIndexLeft - 3, eyeColor);
    pixels->setPixelColor(startIndexRight - 3, eyeColor);
    pixels->show();
}

void BlinkAnimation::closeRandomEye() {
    uint8_t eye = random(EYE_RIGHT + 2);

    if (eye > EYE_RIGHT) {
        closeBothEyes();
    } else {
        closeEye(eye);
    }
}

void BlinkAnimation::closeBothEyes() {
    uint8_t startIndexLeft = 0;
    uint8_t startIndexRight = pixels->numPixels() / 2;

    pixels->setPixelColor(startIndexLeft, LOW);
    pixels->setPixelColor(startIndexRight, LOW);
    pixels->show();
    delay(animStepDelay);

    pixels->setPixelColor(startIndexLeft + 1, LOW);
    pixels->setPixelColor(startIndexLeft + 2, LOW);
    pixels->setPixelColor(startIndexRight + 1, LOW);
    pixels->setPixelColor(startIndexRight + 2, LOW);
    pixels->show();
    delay(animStepDelay);

    pixels->setPixelColor(startIndexLeft + 3, LOW);
    pixels->setPixelColor(startIndexRight + 3, LOW);
    pixels->show();
}

void BlinkAnimation::closeEye(uint8_t eye) {
    if (eye > EYE_RIGHT) {
        return;
    }

    uint8_t startIndex = eye * (pixels->numPixels() / 2);

    pixels->setPixelColor(startIndex, LOW);
    pixels->show();
    delay(animStepDelay);

    pixels->setPixelColor(startIndex + 1, LOW);
    pixels->setPixelColor(startIndex + 2, LOW);
    pixels->show();
    delay(animStepDelay);

    pixels->setPixelColor(startIndex + 3, LOW);
    pixels->show();
}

void BlinkAnimation::doRandomSleep() {
    double sleepAmount = random(minSleepBetweenBlink, maxSleepBetweenBlink) * 1000;
    delay(sleepAmount);
}
