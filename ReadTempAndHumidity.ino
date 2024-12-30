/**
 * DHT11 Sensor Reader
 * This sketch reads temperature and humidity data from the DHT11 sensor and prints the values to the serial port.
 * It also handles potential error states that might occur during reading.
 *
 * Author: Dhruba Saha
 * Version: 2.1.0
 * License: MIT
 */

// Include the DHT11 library for interfacing with the sensor.
#include <DHT11.h>

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 7, 6, 5, 4);
int backLight = 13;// pino 13 responsável pelo controle do LED

// Create an instance of the DHT11 class.
// - For Arduino: Connect the sensor to Digital I/O Pin 2.
// - For ESP32: Connect the sensor to pin GPIO2 or P2.
// - For ESP8266: Connect the sensor to GPIO2 or D4.
DHT11 dht11(2);

void setup() {
  // Initialize serial communication to allow debugging and data readout.
  // Using a baud rate of 9600 bps.
  Serial.begin(9600);
  
  // Uncomment the line below to set a custom delay between sensor readings (in milliseconds).
  dht11.setDelay(1000); // Set this to the desired delay. Default is 500ms.

  // Config do LCD
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // Liga backlight. Substituir 'HIGH' por 'LOW' para desligar a luz de fundo.
  lcd.begin(16, 2);//Colunas, linhas. Use 16,2 para display LCD 16x2
  lcd.clear();
  lcd.display();
}

void loop() {
  int temperature = 0;
  int humidity = 0;

  // Attempt to read the temperature and humidity values from the DHT11 sensor.
  int result = dht11.readTemperatureHumidity(temperature, humidity);

  // Check the results of the readings.
  // If the reading is successful, print the temperature and humidity values.
  // If there are errors, print the appropriate error messages.
  if (result == 0) {
    // Serial.print("Temperature: ");
    // Serial.print(temperature);
    // Serial.print(" °C\tHumidity: ");
    // Serial.print(humidity);
    // Serial.println(" %");
    
    lcd.clear();
    lcd.setCursor(0, 0); //Posiciona o cursor na coluna 0, linha 0 (primeira  linha)
    lcd.print("Temp | Humidade"); //Escreve o texto desejado
    
    lcd.setCursor(0, 1);  //Posiciona o cursor para a coluna 0, linha 1  (segunda linha)
    lcd.print(temperature);
    lcd.print(" C | ");
    lcd.print(humidity);
    lcd.print(" %");

  } else {
    // Print error message based on the error code.
    Serial.println(DHT11::getErrorString(result));
  }
}