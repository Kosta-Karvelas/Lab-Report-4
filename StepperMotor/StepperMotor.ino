/*  
  Goal:
    - Use a joystick to control the speed and direction of a stepper motor.
    - Use non-blocking code (no delay) for smooth stepping.
  
  Theme:
    Analog input → real-time motor control.
*/

#include <Stepper.h>        // Include the Stepper motor library

// Number of steps per revolution for 28BYJ-48 internal motor
const int STEPS_PER_REV = 32;

// Gear ratio inside the motor is 1/64
const int GEAR_RATIO = 64;

// Total steps for one full rotation of the shaft
const int TOTAL_STEPS = STEPS_PER_REV * GEAR_RATIO;

// Create Stepper object (pin order IN1, IN3, IN2, IN4 — common ULN2003 order)
// Change order ONLY if your ULN2003 board labels pins in a different sequence
Stepper motor(STEPS_PER_REV, 8, 10, 9, 11);

// Joystick analog pins
const int joyX = A1;   // X-axis → direction
const int joyY = A0;   // Y-axis → speed

// Timer variables for non-blocking stepping
unsigned long previousMillis = 0;

// Time between steps (ms) — controls smoothness
const int stepInterval = 10;

void setup() {
  Serial.begin(9600);        // Start Serial Monitor for debugging
}

void loop() {
  unsigned long currentMillis = millis();    // Current time check

  // Read joystick values (0–1023)
  int xVal = analogRead(joyX);               // X-axis → left/right → direction
  int yVal = analogRead(joyY);               // Y-axis → up/down → speed

  // Determine direction
  int direction = 0;                         // Default: STOP
  if (xVal < 450) direction = -1;            // Joystick left → rotate CCW
  else if (xVal > 550) direction = 1;        // Joystick right → rotate CW

  // Convert joystick Y movement to speed
  // Up (low value) = fast   |   Down (high value) = slow
  int speed = map(yVal, 0, 1023, 600, 0);    // 0 = fastest RPM

  // Non-blocking timing → step only when interval has passed
  if (currentMillis - previousMillis >= stepInterval) {

    previousMillis = currentMillis;          // Update timer

    if (direction != 0) {                    // Only move if joystick is off-center
      motor.setSpeed(speed);                 // Set the RPM
      motor.step(direction);                 // Move 1 step in chosen direction
    }
  }

  // Debugging output
  Serial.print("X: "); Serial.print(xVal);
  Serial.print(" | Y: "); Serial.print(yVal);
  Serial.print(" | Speed: "); Serial.print(speed);
  Serial.print(" | Direction: ");
  if (direction == 1) Serial.println("CW");
  else if (direction == -1) Serial.println("CCW");
  else Serial.println("STOP");
}