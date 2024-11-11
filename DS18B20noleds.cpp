#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// LCD Pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(10, 8, 2, 3, 0, 7); // Updated LCD pin connections

// Soil Moisture Sensor Pins
const int moistureAnalogPin = A3; // Connected to A0 on sensor
const int moistureDigitalPin = 11; // Connected to D0 on sensor

// DS18B20 Temperature Sensor
const int tempPin = 12; // DS18B20 DQ connected to D12 with 4.7K pull-up resistor
OneWire oneWire(tempPin); // Set up a oneWire instance to communicate with DS18B20
DallasTemperature sensors(&oneWire); // Pass oneWire reference to DallasTemperature

int moistureValue = 0;
int digitalMoistureStatus = 0;

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.begin(16, 2); // Set up the LCD with 16 columns and 2 rows
  lcd.print("Soil Monitor");  // Display initial message
  delay(2000); // Delay to let the message show
  lcd.clear(); // Clear the LCD for upcoming readings

  // Set up digital moisture pin
  pinMode(moistureDigitalPin, INPUT);

  // Start DS18B20 sensor
  sensors.begin();
}

void loop() {
  // Read soil moisture analog value
  moistureValue = analogRead(moistureAnalogPin);
  int moisturePercent = map(moistureValue, 0, 1023, 0, 100);

  // Read digital moisture status (0 if below threshold, 1 if above)
  digitalMoistureStatus = digitalRead(moistureDigitalPin);

  // Request temperature from DS18B20
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0); // Get temperature in Celsius from first sensor

  // Display moisture percentage on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moisturePercent);
  lcd.print("%   "); // Extra spaces to clear previous characters
  
  // Display temperature on LCD
  lcd.setCursor(0, 1); 
  lcd.print("Temp: ");
  lcd.print(temperatureC);
  lcd.print(" C   ");

  // Print moisture reading and temperature to the Serial Monitor for debugging
  Serial.print("Moisture Level (Analog): ");
  Serial.print(moisturePercent);
  Serial.println("%");

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" *C");

  // Print digital moisture status to the Serial Monitor
  Serial.print("Moisture Status (Digital): ");
  Serial.println(digitalMoistureStatus ? "Dry" : "Wet");

  delay(2000); // Delay between readings for stability
}
