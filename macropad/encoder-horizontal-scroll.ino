#include <Keyboard.h>
#include <Mouse.h>

// Rotary encoder pins
const int encoderPinA = 2;
const int encoderPinB = 3;
const int encoderButton = 4; // Optional: encoder push button

// Variables for encoder state
volatile int encoderPos = 0;
volatile int lastEncoderA = 0;
bool buttonPressed = false;
bool lastButtonState = false;

// Scroll sensitivity (adjust as needed)
const int scrollThreshold = 1; // How many encoder steps before scrolling
int scrollCounter = 0;

void setup() {
  // Initialize pins
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderButton, INPUT_PULLUP);
  
  // Attach interrupts for encoder
  attachInterrupt(digitalPinToInterrupt(encoderPinA), readEncoder, CHANGE);
  
  // Initialize HID
  Keyboard.begin();
  Mouse.begin();
  
  // Initialize serial for debugging (optional)
  Serial.begin(9600);
  Serial.println("Side Scroll Wheel Ready");
  
  // Read initial state
  lastEncoderA = digitalRead(encoderPinA);
}

void loop() {
  // Handle encoder rotation for horizontal scrolling
  if (abs(scrollCounter) >= scrollThreshold) {
    if (scrollCounter > 0) {
      // Scroll right - send Shift + Scroll Down
    Keyboard.press(KEY_LEFT_SHIFT);

      Mouse.move(0, 0, 1); // Scroll down with horizontal effect
      Serial.println("Scroll Right");
    Keyboard.release(KEY_LEFT_SHIFT);

      scrollCounter -= scrollThreshold;
    } else {
      // Scroll left - send Shift + Scroll Up  
    Keyboard.press(KEY_LEFT_SHIFT);

      Mouse.move(0, 0, -1); // Scroll up with horizontal effect
      Serial.println("Scroll Left");
    Keyboard.release(KEY_LEFT_SHIFT);

      scrollCounter += scrollThreshold;
    }
  }
  
  // Handle encoder button press (optional feature)
  bool currentButtonState = !digitalRead(encoderButton);
  if (currentButtonState && !lastButtonState) {
    // Button pressed - send middle mouse click
    Mouse.click(MOUSE_MIDDLE);
    Serial.println("Middle Click");
    delay(50); // Debounce
  }
  lastButtonState = currentButtonState;
  
  delay(1); // Small delay for stability
}

// Interrupt service routine for encoder
void readEncoder() {
  int encoderA = digitalRead(encoderPinA);
  int encoderB = digitalRead(encoderPinB);
  
  // Determine direction based on state changes
  if (encoderA != lastEncoderA) {
    if (encoderA == encoderB) {
      scrollCounter++; // Clockwise
    } else {
      scrollCounter--; // Counter-clockwise
    }
  }
  lastEncoderA = encoderA;
}

// Alternative method using keyboard shortcuts for horizontal scroll
void sendHorizontalScroll(bool scrollRight) {
  if (scrollRight) {
    // Method 1: Shift + Mouse Wheel (works in many applications)
    Keyboard.press(KEY_LEFT_SHIFT);
    Mouse.move(0, 0, 1);
    Keyboard.release(KEY_LEFT_SHIFT);
    
    // Method 2: Alternative keyboard shortcuts (uncomment if needed)
    // Keyboard.press(KEY_LEFT_CTRL);
    // Keyboard.press(KEY_RIGHT_ARROW);
    // Keyboard.releaseAll();
  } else {
    // Scroll left
    Keyboard.press(KEY_LEFT_SHIFT);
    Mouse.move(0, 0, -1);
    Keyboard.release(KEY_LEFT_SHIFT);
    
    // Alternative method:
    // Keyboard.press(KEY_LEFT_CTRL);
    // Keyboard.press(KEY_LEFT_ARROW);
    // Keyboard.releaseAll();
  }
}