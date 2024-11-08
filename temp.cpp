#include <DHT.h>               // Include DHT library
#include <LiquidCrystal.h>      // Include library for LCD

// Define the DHT sensor type and pin
#define DHTPIN 7                // DHT sensor connected to digital pin 7
#define DHTTYPE DHT11           // Use DHT11 or DHT22 depending on your sensor
DHT dht(DHTPIN, DHTTYPE);       // Initialize DHT sensor

// Pin setup for soil moisture and pH sensors
const int moisturePin = A0;     // Analog pin for soil moisture sensor
const int pHSensorPin = A1;     // Analog pin for pH sensor (optional)

// LED pin setup
const int greenLED = 2;         // Green LED for healthy moisture
const int yellowLED = 3;        // Yellow LED for moderate moisture
const int redLED = 4;           // Red LED for dry soil

// LCD setup (16x2)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Variables for sensor readings
int moistureValue = 0; // Stores moisture sensor reading
float pHValue = 0;     // Stores pH sensor reading (if used)
float temperature = 0; // Stores temperature reading
float humidity = 0;    // Stores humidity reading

void setup() {
  Serial.begin(9600);
  
  // Set up LED pins as outputs
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.print("Soil Monitor");
  delay(2000);
  lcd.clear();

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Read soil moisture
  moistureValue = analogRead(moisturePin);
  Serial.print("Soil Moisture Level: ");
  Serial.println(moistureValue);

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
  pHValue = (pHRawValue * (5.0 / 1023)) * 3.5; // Adjust as per sensor
  Serial.print("Soil pH Level: ");
  Serial.println(pHValue);
  lcd.setCursor(0, 1);
  lcd.print("pH: ");
  lcd.print(pHValue, 1);

  // Read temperature and humidity from DHT sensor
  temperature = dht.readTemperature(); // Temperature in Celsius
  humidity = dht.readHumidity();       // Humidity in percentage
  
  // Display temperature and humidity in serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Display temperature and humidity on LCD (alternate display)
  delay(2000); // Display moisture and pH first, then alternate
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
  
  delay(2000); // Delay for readability
  lcd.clear(); // Clear LCD to switch back to main display
}
