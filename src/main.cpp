#include <FastLED.h>

#define LED_TYPE WS2811
#define COLOR_ORDER GRB

const int LED_PIN      = D1;
const int NUM_LEDS     = 49;
const int BRIGHTNESS   = 20;
const int DELAY_MILLIS = 250;

CRGB leds[NUM_LEDS];

void setup() {
  delay(1000);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

int lit = 0;

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = (i == lit) ? CRGB::Red : CRGB::Black;
  }

  FastLED.show();

  lit += 1;
  if (lit >= NUM_LEDS) {
    lit = 0;
  }

  delay(DELAY_MILLIS);
}
