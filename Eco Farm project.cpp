#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// LCD settings (16x2 I2C at address 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT sensor
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// LED pins
#define GREEN_LED 8
#define RED_LED 9
#define YELLOW_LED 10

// Variables
int h;  // humidity
int t;  // temperature

void setup() {
  Serial.begin(9600);
  Serial.println("Temperature and Humidity Sensor Test");

  dht.begin();
  lcd.init();        
  lcd.backlight();   

  // LED setup
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);

  // Turn LEDs ON initially
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, HIGH);
  digitalWrite(YELLOW_LED, HIGH);
}

void loop() {
  // Read sensor data
  h = dht.readHumidity();
  t = dht.readTemperature();

  // Print to Serial
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %, Temp: ");
  Serial.print(t);
  Serial.println(" °C");

  // Print on LCD
  lcd.setCursor(0, 0);
  lcd.print(" Simple Circuits ");

  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(t);
  lcd.print("C ");

  lcd.setCursor(8, 1);
  lcd.print("H:");
  lcd.print(h);
  lcd.print("%");

  delay(1000);
}
