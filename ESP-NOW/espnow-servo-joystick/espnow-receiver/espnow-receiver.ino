#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

#define SIGNAL_TIMEOUT 1000  // This is signal timeout in milli seconds. We will reset the data if no signal

unsigned long lastRecvTime = 0;

struct PacketData{
  byte lxAxisValue;
  byte lyAxisValue;
 
  byte switch1Value;
};

PacketData receiverData;

Servo servo1;

int   led1 = 8;

//Assign default input received values
void setInputDefaultValues(){
  // The middle position for joystick. (254/2=127)
  receiverData.lxAxisValue = 127;
  receiverData.lyAxisValue = 127;
  
  receiverData.switch1Value = LOW;
}

void mapAndWriteValues(){
  servo1.write(map(receiverData.lxAxisValue, 0, 254, 0, 180));  
  digitalWrite(led1, receiverData.switch1Value);
}

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  if (len == 0){
    return;
  }
  memcpy(&receiverData, incomingData, sizeof(receiverData));
  mapAndWriteValues();  
  lastRecvTime = millis(); 
}

void setUpPinModes(){
  servo1.attach(21);
  pinMode(led1, OUTPUT);
  setInputDefaultValues();
  mapAndWriteValues();
}

void setup(){
  setUpPinModes();
 
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}
 


void loop(){
  //Check Signal lost.
  unsigned long now = millis();
  if ( now - lastRecvTime > SIGNAL_TIMEOUT ) {
    setInputDefaultValues();
    mapAndWriteValues();  
  }
}