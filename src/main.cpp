#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(8, D2, NEO_GRB + NEO_KHZ800);

void disableWifi() {
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);
}

void setup() {
    /* Setup serial for debug */
    Serial.begin(115200);

    disableWifi();

    pixels.begin();
}

void loop() {
    Serial.print("Low");
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.setPixelColor(1, pixels.Color(0, 0, 0));
    pixels.setPixelColor(2, pixels.Color(0, 0, 0));
    pixels.setPixelColor(3, pixels.Color(0, 0, 0));
    pixels.setPixelColor(4, pixels.Color(0, 0, 0));
    pixels.setPixelColor(5, pixels.Color(0, 0, 0));
    pixels.setPixelColor(6, pixels.Color(0, 0, 0));
    pixels.setPixelColor(7, pixels.Color(0, 0, 0));
    pixels.show();

    delay(2000);

    Serial.print("High");
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.setPixelColor(1, pixels.Color(255, 0, 0));
    pixels.setPixelColor(2, pixels.Color(255, 0, 0));
    pixels.setPixelColor(3, pixels.Color(255, 0, 0));
    pixels.setPixelColor(4, pixels.Color(255, 0, 0));
    pixels.setPixelColor(5, pixels.Color(255, 0, 0));
    pixels.setPixelColor(6, pixels.Color(255, 0, 0));
    pixels.setPixelColor(7, pixels.Color(255, 0, 0));
    pixels.show();

    ESP.deepSleep(10e6, RF_DISABLED);
}