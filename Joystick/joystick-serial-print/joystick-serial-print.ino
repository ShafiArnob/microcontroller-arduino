#define VRX_PIN  4
#define VRY_PIN  3 

#define LEFT_THRESHOLD  1000
#define RIGHT_THRESHOLD 4000


#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02


int valueX = 0 ; 
int valueY = 0 ; 
int command = COMMAND_NO;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read X and Y analog values
  valueX = analogRead(VRX_PIN);
  valueY = analogRead(VRY_PIN);

  Serial.println("X - ");
  Serial.println(valueX);
  Serial.println("\t");
  Serial.println("Y - ");
  Serial.println(valueY);

  delay(1000);
}