#include<ESP32Servo.h>

#define SERVO_PIN 21
Servo myServo;

void setup() 
{
  myServo.attach(SERVO_PIN); 
  Serial.begin(115200);
}

void loop()
{ 
  int angle = 0;
  if(Serial.available()){
    angle = Serial.parseInt();
    myServo.write(angle);
  }
  delay(20);
}