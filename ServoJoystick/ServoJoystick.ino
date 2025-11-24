/*  
Goal:
- Read analog values from a joystick.
- Convert the joystick X-axis value to a servo angle (0°–180°).
- Move a servo smoothly based on joystick position.
- Display readings on Serial Monitor.

Theme:
- Analog input processing
- Joystick control
- Servo movement
- ADC mapping
*/

#include <Servo.h>            // Load the servo library so Arduino can control servos
Servo myservo;                // Create a servo object that will control one servo motor
const int sensorPin = A0;     // Joystick X-axis is connected to analog input A0
int val;                      // This will store the raw joystick reading (0–1023)
float angle;                  // This will store the converted servo angle (0–180°)

void setup() {
  myservo.attach(9);          // Connect the servo signal wire to digital pin 9
  Serial.begin(9600);         // Start Serial Monitor 
}

void loop() {

  val = analogRead(sensorPin);     // Read voltage from joystick (0 = left, 1023 = right)

  angle = map(val, 0, 1023, 0, 180); // Convert joystick value (0–1023) into servo angle (0–180 degrees)
  angle = constrain(angle, 0, 180);// Make sure the angle never goes below 0° or above 180°

  myservo.write(angle);            // Move the servo to the calculated angle

  //  Serial Monitor Output 
  Serial.print("Joystick Value = ");  // Print label
  Serial.println(val);                // Print raw joystick value

  Serial.print("Servo Angle = ");     // Print label
  Serial.println(angle);              // Print the angle we send to the servo

  delay(15);                          // Short delay for smoother servo motion
}