#define HOSTNAME "utt-3-hoop" // utt-3-hoop.local
#define DEBUG_PORT Serial

// #define WIFI_ENABLED

#ifdef WIFI_ENABLED
#include <WiFiSetup.h>
#include <Debuggy.h>
#endif

#include <FastLED.h>
#define LED_TYPE WS2811
#define COLOR_ORDER GRB

const int LED_PIN       = D3;
const int LEDS_PER_HOOP = 49;
const int NUM_HOOPS     = 3;
const int NUM_LEDS      = NUM_HOOPS * LEDS_PER_HOOP;
const int BRIGHTNESS    = 255;

const int DELAY         = 1000;

CRGB leds[NUM_LEDS];

void FillAllHoopsFromBaseColorIndex(uint8_t colorIndex);
void FillHoopFromColorIndex(uint8_t hoopIndex, uint8_t colorIndex);

void setup() {
  delay(500);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(115200);

#ifdef WIFI_ENABLED
  initWiFiManager();
  initOTA();
  initTelnetDebug();
#endif
}

void loop() {
  static uint8_t baseColorIndex = 0;
  FillAllHoopsFromBaseColorIndex(baseColorIndex);
  FastLED.show();
  FastLED.delay(DELAY);
  baseColorIndex += 1;

#ifdef WIFI_ENABLED
  ArduinoOTA.handle();
#endif
}

void FillAllHoopsFromBaseColorIndex(uint8_t colorIndex) {
  for (int i = 0; i < NUM_HOOPS; i++) {
    uint8_t startColorIndex = (i * 85) + colorIndex;
    FillHoopFromColorIndex(i, startColorIndex);
  }
}

void FillHoopFromColorIndex(uint8_t hoopIndex, uint8_t colorIndex) {
  float newColorIndex = colorIndex;
  float colorIndexIncrement = 3;

  for (int i = 0; i < LEDS_PER_HOOP; i++) {
    int ledIndex = (hoopIndex * LEDS_PER_HOOP) + i;
    leds[ledIndex] = ColorFromPalette(RainbowColors_p, int(newColorIndex),
                                      BRIGHTNESS, LINEARBLEND);
    if (i < LEDS_PER_HOOP / 2) {
      newColorIndex += colorIndexIncrement;
    } else {
      newColorIndex -= colorIndexIncrement;
    }
  }
}
