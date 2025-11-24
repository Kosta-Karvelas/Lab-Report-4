/*
Goal:
The goal of this program is to use an ultrasonic sensor to measur distance the 
something and to display the distaance onto an LCD.

Theme:
- Sensor measurement and LCD text display
*/

#include <LiquidCrystal.h>  // Include the LCD library to control a 16x2 LCD

// Ultrasonic sensor pins
const int Trig = 8;  // Trigger pin sends a pulse to start measurement
const int Echo = 9;  // Echo pin receives the reflected pulse

// LCD pins (RS, EN, D4, D5, D6, D7)
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  // Create an LCD object to control the display

// Variables to store measurement results
float distance;  // Distance in centimeters
float duration;  // Time for pulse to travel to object and back (microseconds)

void setup() {
  Serial.begin(9600);        // Start serial communication
  pinMode(Trig, OUTPUT);     // Set the Trig pin as output to send pulses
  pinMode(Echo, INPUT);      // Set the Echo pin as input to receive pulses
  lcd.begin(16, 2);          // Start the 16x2 LCD screen
}

void loop() {
  //  Ultrasonic Trigger Pulse 
  digitalWrite(Trig, 0);            // Ensure Trig is LOW (0) before starting the pulse
  delayMicroseconds(2);             // Wait 2 microseconds
  digitalWrite(Trig, 1);            // Set Trig HIGH (1) for 10 microseconds to send pulse
  delayMicroseconds(10);            // Keep HIGH (1) for 10 microseconds
  digitalWrite(Trig, 0);            // Set Trig TO 0 again to finish pulse

  //  Measure Echo Duration 
  duration = pulseIn(Echo, 1);      // Read how long Echo pin stays HIGH (1) (time for pulse to return)

  // Calculate Distance 
  distance = (duration / 2.0) * 0.0343;  // Convert time to distance in cm

  // Display Results on LCD 
  if (distance >= 400 || distance <= 2) {  // Check if distance is out of sensor range
    lcd.clear();                            // Clear previous display
    lcd.setCursor(0, 0);                    // Set cursor to first row
    lcd.print("Out of range");              // Display message
  } else {                                  // Valid distance measurement
    lcd.clear();                            // Clear previous display
    lcd.setCursor(0, 0);                    // First row
    lcd.print("Distance = ");               // Label
    lcd.setCursor(0, 1);                    // Move to second row
    lcd.print(distance, 1);                 // Print distance with 1 decimal place
    lcd.print(" cm");                       // Add unit
  }

  delay(100);  // Wait 100ms before next measurement to control update rate
}