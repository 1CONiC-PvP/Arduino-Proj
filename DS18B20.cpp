#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

// Data wire for DS18B20 is plugged into pin 7 on the Arduino
#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// LCD setup (16x2)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Sensor Pins
const int moisturePin = A0;
const int pHSensorPin = A1;

// LED Pins
const int greenLED = 2;
const int yellowLED = 3;
const int redLED = 4;

int moistureValue = 0;
float pHValue = 0;

void setup() {
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Soil Monitor");
  delay(2000);
  lcd.clear();

  // LED setup
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Initialize temperature sensor
  sensors.begin();
}

void loop() {
  // Read soil moisture
  moistureValue = analogRead(moisturePin);

  // Check moisture level and update LEDs
  if (moistureValue > 800) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Moisture: Good   ");
  } 
  else if (moistureValue > 400) {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Moisture: Mod    ");
  } 
  else {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Moisture: Low    ");
  }

  // Read pH level (optional)
  int pHRawValue = analogRead(pHSensorPin);
  pHValue = (pHRawValue * (5.0 / 1023)) * 3.5; 
  lcd.setCursor(0, 1);
  lcd.print("pH: ");
  lcd.print(pHValue, 1);

  // Request temperature from DS18B20
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0); // Get temperature in Celsius

  // Display temperature in serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Display temperature on LCD (alternate display)
  delay(2000); // Display moisture and pH first, then alternate
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  
  delay(2000); // Delay for readability
  lcd.clear(); // Clear LCD to switch back to main display
}
