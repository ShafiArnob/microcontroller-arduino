#define VRX_PIN  17
#define VRY_PIN  18


int valueX = 0 ; 
int valueY = 0 ; 

int mapAndAdjustJoystickDeadBandValues(int value, bool reverse)
{
  if (value >= 2200)
  {
    value = map(value, 2200, 4095, 127, 254);
  }
  else if (value <= 1800)
  {
    value = (value == 0 ? 0 : map(value, 1800, 0, 127, 0));  
  }
  else
  {
    value = 127;
  }

  if (reverse)
  {
    value = 254 - value;
  }
  Serial.println(value);  
  return value;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read X and Y analog values
  valueX = mapAndAdjustJoystickDeadBandValues(analogRead(VRX_PIN), false);
  valueY = mapAndAdjustJoystickDeadBandValues(analogRead(VRY_PIN), false);

  Serial.println("X - ");
  Serial.println(valueX);
  Serial.println("\t");
  Serial.println("Y - ");
  Serial.println(valueY);

  delay(60);
}