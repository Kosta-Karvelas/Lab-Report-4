/*Goal of the Program:
- Read an analog voltage on pin A0 using a potentiometer.
- Display the measured voltage on a standard 16x2 LCD
  wired in 4-bit parallel mode.

Main Theme:
- Using analog input and LCD output for measurement.

*/

#include <LiquidCrystal.h>   // Include the LiquidCrystal library to control the LCD

// Initialize the LCD object using pins: rs, enable, d4, d5, d6, d7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  

const int analogPin = A0;   // Analog pin where potentiometer is connected

void setup() {
  lcd.begin(16, 2);         // Initialize the LCD with 16 columns and 2 rows

  lcd.setCursor(0, 0);      // Set cursor to column 0, row 0
  lcd.print("LCD Voltmeter");// Display startup message
  delay(1500);              // Wait 1.5 seconds to let user read the message
  lcd.clear();              // Clear the LCD for the main display
}

void loop() {
  int rawValue = analogRead(analogPin);          // Read the analog value from A0 (0-1023)
  float voltage = (rawValue * 5.0) / 1023.0;    // Convert the ADC value to actual voltage

  lcd.setCursor(0, 0);                          // Move cursor to first row
  lcd.print("Voltage:       ");                  // Display label, pad spaces to clear old numbers

  lcd.setCursor(0, 1);                          // Move cursor to second row
  lcd.print(voltage, 2);                         // Print voltage with 2 decimal places
  lcd.print(" V");                               // Add voltage unit

  delay(300);                                    // Wait 300ms before next reading
}