#include <Arduino.h>
#include <WS2812FX.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#define LED_COUNT 1
#define LED_PIN 12

// WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);


U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   // EastRising 0.42" OLED

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void setup() {
  // put your setup code here, to run once:
  Wire.setSDA(22);
  Wire.setSCL(23);
  Wire.begin();  
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();
  u8g2_prepare();
  u8g2.drawStr( 0, 0, "ASCII page--");
  u8g2.drawStr( 0, 8, "ASCII page--");
  u8g2.sendBuffer();
  delay(100);
}
