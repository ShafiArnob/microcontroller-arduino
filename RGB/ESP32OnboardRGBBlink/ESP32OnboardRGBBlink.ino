#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN       48
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
}

void loop() {
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(0, 0, 100));
  pixels.show();
  delay(DELAYVAL);

  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  delay(DELAYVAL);

  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(100, 0, 0));
  pixels.show();
  delay(DELAYVAL);
}