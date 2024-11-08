#include <LiquidCrystal.h> // Include library for LCD

// Pin setup for soil moisture and pH sensors
const int moisturePin = A0;      // Analog pin for soil moisture sensor
const int pHSensorPin = A1;      // Analog pin for pH sensor (optional)

// LED pin setup
const int greenLED = 2;          // Green LED for healthy moisture
const int yellowLED = 3;         // Yellow LED for moderate moisture
const int redLED = 4;            // Red LED for dry soil

// LCD setup (16x2)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Adjust pins if needed

// Variables for sensor readings
int moistureValue = 0; // Stores moisture sensor reading
float pHValue = 0;     // Stores pH sensor reading (if used)

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set up LED pins as outputs
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Initialize the LCD
  lcd.begin(16, 2);         // Set LCD to 16x2 characters
  lcd.print("Soil Monitor"); // Initial message
  delay(2000);               // Display the message briefly
  lcd.clear();
}

void loop() {
  // Read moisture sensor value
  moistureValue = analogRead(moisturePin);
  Serial.print("Soil Moisture Level: ");
  Serial.println(moistureValue);

  // Check moisture level and update LEDs
  if (moistureValue > 800) {
    digitalWrite(greenLED, HIGH);    // Optimal moisture
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Moisture: Good    ");
  }
  else if (moistureValue > 400) {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);   // Moderate moisture
    digitalWrite(redLED, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Moisture: Moderate");
  }
  else {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);      // Low moisture
    lcd.setCursor(0, 0);
    lcd.print("Moisture: Low     ");
  }

  // Optional: Read and display pH sensor value
  int pHRawValue = analogRead(pHSensorPin);
  pHValue = (pHRawValue * (5.0 / 1023)) * 3.5; // Adjust calculation based on pH sensor range
  Serial.print("Soil pH Level: ");
  Serial.println(pHValue);

  lcd.setCursor(0, 1);
  lcd.print("pH: ");
  lcd.print(pHValue, 1);  // Print pH with 1 decimal place
  lcd.print("          "); // Clear remaining spaces if needed

  delay(1000); // Delay for readability
}
