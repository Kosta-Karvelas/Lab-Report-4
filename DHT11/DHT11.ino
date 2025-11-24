/*
Goal:
The goal of this program is to tead the temperature and humidity from a DHT11 sensor
and display the readings on a 16x2 LCD.

Main Theme:
Displaying real-time results on an LCD from a sensor
*/

#include <LiquidCrystal.h>  // LCD library
#include "DHT.h"             // DHT sensor library

// LCD pin connections
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  // Initialize LCD object

// DHT11 sensor settings
#define DHTPIN 8           // Digital pin connected to DHT11
#define DHTTYPE DHT11      // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);  // Initialize DHT sensor object

// Variables to store readings
float hum;   // Humidity value
float temp;  // Temperature value

void setup() {
  lcd.begin(16, 2);   // Initialize LCD with 16 columns and 2 rows
  dht.begin();         // Initialize DHT11 sensor
}

void loop() {
  hum = dht.readHumidity();       // Read humidity from DHT11
  temp = dht.readTemperature();   // Read temperature in Celsius from DHT11

  // Check if sensor reading failed
  if (isnan(hum) || isnan(temp)) {
    lcd.setCursor(0, 0);          // Move cursor to first row
    lcd.print("Sensor Error   ");  // Display error message
    lcd.setCursor(0, 1);          // Move cursor to second row
    lcd.print("Check DHT11   ");  // Suggest checking sensor connection
    delay(1000);                   // Wait 1 second before retrying
    return;                        // Skip the rest of loop
  }

  // Display temperature
  lcd.setCursor(0, 0);            // Move cursor to first row
  lcd.print("Temp: ");             // Label
  lcd.print(temp, 1);              // Print temperature with 1 decimal place
  lcd.print(" C   ");              // Add extra spaces to clear leftover characters

  // Display humidity
  lcd.setCursor(0, 1);            // Move cursor to second row
  lcd.print("Hum:  ");             // Label
  lcd.print(hum, 1);               // Print humidity with 1 decimal place
  lcd.print(" %   ");              // Add extra spaces to clear leftover characters

  delay(1000);                     // DHT11 updates once per second
}



