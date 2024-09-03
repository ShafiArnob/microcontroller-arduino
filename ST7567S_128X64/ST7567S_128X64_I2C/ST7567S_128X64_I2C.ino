
#include <U8g2lib.h>



#define u8g2_PIN_NONE 100

U8G2_ST7567_ENH_DG128064I_F_SW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);




void setup()
{
    u8g2.setI2CAddress (0x7E);  //(0x3F * 2);
    u8g2.begin();
    u8g2.clearBuffer(); // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); 
    u8g2.drawStr(0, 10, "NTP clock by niq_ro."); // write something to the internal memory
    u8g2.sendBuffer(); // transfer internal memory to the display
    delay(1000);
    u8g2.clearBuffer();          // clear the internal memory
   
}


void loop() {
    u8g2.setFont(u8g2_font_ncenB08_tr); 
    u8g2.drawStr(0, 10, "Hello World"); // write something to the internal memory
    u8g2.sendBuffer(); // transfer internal memory to the display
    delay(2000);
    u8g2.clearBuffer();
} 
