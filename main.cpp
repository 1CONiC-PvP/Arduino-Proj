#include <LiquidCrystal.h>

// LCD Pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(10, 8, 2, 3, 0, 7); // Updated LCD pin connections

// Soil Moisture Sensor Pins
const int moistureAnalogPin = A3; // Connected to A0 on sensor
const int moistureDigitalPin = 11; // Connected to D0 on sensor

// LED Pins
const int greenLED = 5;
const int yellowLED = 9;
const int redLED = 6;

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

  // Set up LED pins
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Set up digital moisture pin
  pinMode(moistureDigitalPin, INPUT);
}

void loop() {
  // Read soil moisture analog value
  moistureValue = analogRead(moistureAnalogPin);
  int moisturePercent = map(moistureValue, 0, 1023, 0, 100);

  // Read digital moisture status (0 if below threshold, 1 if above)
  digitalMoistureStatus = digitalRead(moistureDigitalPin);

  // Display moisture percentage on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moisturePercent);
  lcd.print("%   "); // Extra spaces to clear previous characters
  
  // Display condition on the LCD and control LEDs based on analog reading
  if (moisturePercent > 70) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Status: Good    ");
  } 
  else if (moisturePercent > 40) {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Status: Moderate");
  } 
  else {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Status: Low     ");
  }

  // Print moisture reading to the Serial Monitor for debugging
  Serial.print("Moisture Level (Analog): ");
  Serial.print(moisturePercent);
  Serial.println("%");

  // Print digital moisture status to the Serial Monitor
  Serial.print("Moisture Status (Digital): ");
  Serial.println(digitalMoistureStatus ? "Dry" : "Wet");

  delay(2000); // Delay between readings for stability
}
