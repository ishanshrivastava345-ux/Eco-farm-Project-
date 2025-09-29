#include <Adafruit_LiquidCrystal.h>

// Create LCD object (Adafruit shield or parallel wiring)
Adafruit_LiquidCrystal lcd_1(0);

const int tempPin = A0;       // TMP36 middle pin to A0
const int humidPin = A2;      // Potentiometer wiper pin to A2
const int buzzerPin = 8;      // Sound system / speaker pin

float temperatureC;
int humidity;

void setup() {
  pinMode(tempPin, INPUT);
  pinMode(humidPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  lcd_1.begin(16, 2);  // Initialize LCD 16x2
}

void loop() {
  // ---- Temperature Reading (TMP36) ----
  int sensorValue = analogRead(tempPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  temperatureC = (voltage - 0.5) * 100.0;

  // ---- Humidity Reading (Potentiometer) ----
  int humidValue = analogRead(humidPin);       // Range: 0–1023
  humidity = map(humidValue, 0, 1023, 0, 100); // Convert to percentage (0–100%)

  // ---- Serial Monitor Output ----
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // ---- LCD Output ----
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("T:");
  lcd_1.print(temperatureC, 1);
  lcd_1.print("C");

  lcd_1.setCursor(8, 0);
  lcd_1.print("H:");
  lcd_1.print(humidity);
  lcd_1.print("%");

  lcd_1.setCursor(0, 1);
  lcd_1.print("Smart Growth Sys");

  // ---- Sound System Control ----
  if (temperatureC > 30.0 && humidity < 40) {
    digitalWrite(buzzerPin, HIGH); // Play sound/music if hot & dry
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  delay(1000);
}
