/*
Goal of the Program: 
The goal of this program is to read a voltage coming from the arduino through A0 
(potentiometer)and converting it to OHMs using OHM's law and displaying the 
value on an LCD.

Main theme:
Using analog inputs to measure resistance and LCD output for measurement. 
*/

#include <LiquidCrystal.h>    // Include the LiquidCrystal library to control a 16x2 LCD

// Initialize the LCD object using pins: rs, enable, d4, d5, d6, d7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    

byte ohmSymbol[8] = { // Custom character for the ohm (Ω) symbol
  B00000, 
  B01110, 
  B10001, 
  B10001, 
  B10001, 
  B01010, 
  B11011, 
  B00000 
};  

const int analogPin = A0;   // Analog pin where the unknown resistor is connected
const float Vcc = 5.0;      // Supply voltage for the voltage divider
const float Rknown = 220.0; // Known resistor in series (Ohms)

void setup() {
  Serial.begin(9600);       // Initialize serial communication for debugging
  lcd.begin(16, 2);         // Initialize LCD with 16 columns and 2 rows
  lcd.createChar(0, ohmSymbol); // Create custom ohm symbol at character location 0
  lcd.print("Ohm Meter");   // Display initial message
  delay(1000);              // Wait 1 second to allow user to read
  lcd.clear();              // Clear LCD for measurements
}

void loop() {
  int sensorValue = analogRead(analogPin);    // Read analog value from A0 (0–1023)
  float VA = sensorValue * (Vcc / 1023.0);    // Convert ADC value to measured voltage
  float I = (Vcc - VA) / Rknown;              // Calculate current through known resistor using Ohm's law

  // Print debug info to Serial Monitor
  Serial.print("ADC=");       //Print what's in brackets in serial moitor
  Serial.print(sensorValue); //Print the sensor value in serial moitor
  Serial.print("  VA=");     //Print what's in brackets in serial moitor
  Serial.print(VA, 2);      // Print voltage with 2 decimal places
  Serial.print("V  I=");    // Print "V I= " in the serial monitor
  Serial.println(I, 6);     // Print current with 6 decimal places

  lcd.setCursor(0, 0);      // Move cursor to first row

  if (VA > 4.95) {          // If measured voltage is near Vcc, the resistor is effectively open
    lcd.print("No resistor   "); // Display message for open circuit
  } 
  else { 
    float R = VA / I;       // Calculate unknown resistor value using Ohm's law
    lcd.print("R = ");       //Prints "R = " on LCD
    lcd.print(R, 1);        // Display resistance with 1 decimal place
    lcd.write(byte(0));      // Print custom ohm symbol
    lcd.print("      ");     // Clear any leftover characters from previous readings
  } 

  delay(500);                // Wait 0.5 seconds before next reading
}


