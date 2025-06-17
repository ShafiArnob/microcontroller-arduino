#include <Keyboard.h>

// Pin definitions for switches
const int switch1Pin = 2;
const int switch2Pin = 3;
const int switch3Pin = 4;
const int switch4Pin = 5;
const int switch5Pin = 6;

// Pin definitions for rotary encoder (scroll wheel)
const int encoderPinA = 7;
const int encoderPinB = 8;
const int encoderButtonPin = 9;

// Variables for switch states
bool switch1State = false;
bool switch2State = false;
bool switch3State = false;
bool switch4State = false;
bool switch5State = false;

bool lastSwitch1State = false;
bool lastSwitch2State = false;
bool lastSwitch3State = false;
bool lastSwitch4State = false;
bool lastSwitch5State = false;

// Variables for encoder
int lastEncoderA = HIGH;
int lastEncoderB = HIGH;
bool encoderButtonState = false;
bool lastEncoderButtonState = false;

// Debounce timing
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  // Initialize serial for debugging
  Serial.begin(9600);
  
  // Initialize keyboard
  Keyboard.begin();
  
  // Set up switch pins as inputs with pullup resistors
  pinMode(switch1Pin, INPUT_PULLUP);
  pinMode(switch2Pin, INPUT_PULLUP);
  pinMode(switch3Pin, INPUT_PULLUP);
  pinMode(switch4Pin, INPUT_PULLUP);
  pinMode(switch5Pin, INPUT_PULLUP);
  
  // Set up encoder pins
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderButtonPin, INPUT_PULLUP);
  
  // Read initial encoder state
  lastEncoderA = digitalRead(encoderPinA);
  lastEncoderB = digitalRead(encoderPinB);
  
  Serial.println("Macropad initialized!");
}

void loop() {
  // Read current switch states (inverted because of pullup resistors)
  switch1State = !digitalRead(switch1Pin);
  switch2State = !digitalRead(switch2Pin);
  switch3State = !digitalRead(switch3Pin);
  switch4State = !digitalRead(switch4Pin);
  switch5State = !digitalRead(switch5Pin);
  
  // Handle switch presses
  handleSwitchPress(1, switch1State, lastSwitch1State);
  handleSwitchPress(2, switch2State, lastSwitch2State);
  handleSwitchPress(3, switch3State, lastSwitch3State);
  handleSwitchPress(4, switch4State, lastSwitch4State);
  handleSwitchPress(5, switch5State, lastSwitch5State);
  
  // Update last switch states
  lastSwitch1State = switch1State;
  lastSwitch2State = switch2State;
  lastSwitch3State = switch3State;
  lastSwitch4State = switch4State;
  lastSwitch5State = switch5State;
  
  // Handle encoder rotation
  // handleEncoder();
  
  // Handle encoder button press
  // handleEncoderButton();
  
  delay(5); // Small delay for stability
}

void handleSwitchPress(int switchNum, bool currentState, bool lastState) {
  if (currentState && !lastState) { // Switch just pressed
    Serial.print("Switch ");
    Serial.print(switchNum);
    Serial.println(" pressed");
    
    switch(switchNum) {
      case 1:
        // Copy (Ctrl+C)
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('c');
        delay(10);
        Keyboard.releaseAll();
        break;
        
      case 2:
        // Paste (Ctrl+V)
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('v');
        delay(10);
        Keyboard.releaseAll();
        break;
        
      case 3:
        // Undo (Ctrl+Z)
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('z');
        delay(10);
        Keyboard.releaseAll();
        break;
        
      case 4:
        // Save (Ctrl+S)
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('s');
        delay(10);
        Keyboard.releaseAll();
        break;
        
      case 5:
        // Alt+Tab (Window switcher)
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_TAB);
        delay(10);
        Keyboard.releaseAll();
        break;
    }
  }
}

void handleEncoder() {
  int currentA = digitalRead(encoderPinA);
  int currentB = digitalRead(encoderPinB);
  
  // Check if encoder A pin changed
  if (currentA != lastEncoderA) {
    // If A changed from HIGH to LOW
    if (currentA == LOW) {
      // Check direction based on B pin
      if (currentB == HIGH) {
        // Clockwise rotation - Volume Up
        Keyboard.press(KEY_F3); // Or use volume up key
        delay(10);
        Keyboard.release(KEY_F3);
        Serial.println("Encoder: Clockwise (Volume Up)");
      } else {
        // Counter-clockwise rotation - Volume Down
        Keyboard.press(KEY_F2); // Or use volume down key
        delay(10);
        Keyboard.release(KEY_F2);
        Serial.println("Encoder: Counter-clockwise (Volume Down)");
      }
    }
  }
  
  lastEncoderA = currentA;
  lastEncoderB = currentB;
}

void handleEncoderButton() {
  encoderButtonState = !digitalRead(encoderButtonPin); // Inverted due to pullup
  
  if (encoderButtonState && !lastEncoderButtonState) {
    // Encoder button pressed - Mute toggle
    Keyboard.press(KEY_F1); // Or use mute key
    delay(10);
    Keyboard.release(KEY_F1);
    Serial.println("Encoder button pressed (Mute)");
  }
  
  lastEncoderButtonState = encoderButtonState;
}

// Alternative function keys for volume control (uncomment if needed)
/*
void handleEncoder() {
  int currentA = digitalRead(encoderPinA);
  int currentB = digitalRead(encoderPinB);
  
  if (currentA != lastEncoderA) {
    if (currentA == LOW) {
      if (currentB == HIGH) {
        // Clockwise - Page Up
        Keyboard.press(KEY_PAGE_UP);
        delay(10);
        Keyboard.release(KEY_PAGE_UP);
        Serial.println("Encoder: Page Up");
      } else {
        // Counter-clockwise - Page Down
        Keyboard.press(KEY_PAGE_DOWN);
        delay(10);
        Keyboard.release(KEY_PAGE_DOWN);
        Serial.println("Encoder: Page Down");
      }
    }
  }
  
  lastEncoderA = currentA;
  lastEncoderB = currentB;
}
*/