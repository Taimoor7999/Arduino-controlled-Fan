#include <DHT.h>                  // Library for DHT Sensor 
#include <LiquidCrystal_I2C.h>    // Library for LCD Display

#define DHTPIN 7                  // DHT11 sensor data pin
#define DHTTYPE DHT11             // DHT sensor type
#define ROOM_TEMPERATURE 28       // Room Temperature 
#define TEMPERATURE_THRESHOLD 33  // Temperature threshold at which fan starts 

int pin = 8;                         // Pin connected to the fan relay
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 column and 2 rows for LCD
DHT dht(DHTPIN, DHTTYPE);            // Initialize DHT sensor object

void setup() {
  Serial.begin(9600);             // Initialize serial communication at 9600 baud rate
  dht.begin();                    // Initialize DHT sensor
  lcd.init();                     // Initialize LCD
  lcd.backlight();                // Turn on LCD backlight
  pinMode(pin, OUTPUT);           // Set the fan pin as an output
}

void loop() {
  delay(2000);                                // Delay between readings (adjust as needed)
  float temperature = dht.readTemperature();  // Read temperature in Celsius from DHT sensor
  Serial.print("Temperature: ");              // Print temperature to serial monitor
  Serial.print(temperature);
  Serial.println(" °C");
  lcd.clear();                                // Clear LCD display
  lcd.setCursor(0, 1);                        // Set cursor to the second line of LCD

  if (isnan(temperature)) {                   // Check if temperature reading is valid
    Serial.println("Failed to read temperature from DHT sensor!");  
    return;
  }

  if (temperature > TEMPERATURE_THRESHOLD) {  // If temperature exceeds threshold, turn on fan
    lcd.begin(16, 2);                         // Initialize LCD with 16 columns and 2 rows
    lcd.setCursor(0, 0);                      // Set cursor to first line of LCD
    lcd.print("Temperature:");                // Display temperature label
    lcd.print(temperature);                   // Display temperature value
    lcd.setCursor(0, 1);                      // Set cursor to second line of LCD
    lcd.print("Fan ON");                      // Indicate fan is turned on
    digitalWrite(pin, HIGH);                  // Turn on fan
  } else {                                    // If temperature is below threshold, turn off fan
    lcd.begin(16, 2);                         // Initialize LCD with 16 columns and 2 rows
    lcd.setCursor(0, 0);                      // Set cursor to first line of LCD
    lcd.print("Temperature:");                // Display temperature label
    lcd.print(temperature);                   // Display temperature value
    lcd.setCursor(0, 1);                      // Set cursor to second line of LCD
    lcd.print("Fan OFF");                     // Indicate fan is turned off
    digitalWrite(pin, LOW);                   // Turn off fan
  }
}
