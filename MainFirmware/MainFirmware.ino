#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp; 

int value1 = analogRead(A0);
int value2= analogRead(A0);
int difference = 0;
int lightning = -1;

void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT); 
  Serial.println(F("BMP280 test"));

  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     
                  Adafruit_BMP280::SAMPLING_X2,     
                  Adafruit_BMP280::SAMPLING_X16,    
                  Adafruit_BMP280::FILTER_X16,     
                  Adafruit_BMP280::STANDBY_MS_500);
                  
}


void loop() {
  lightningCount();
  readSensors();
}

void lightningCount() {
  difference = value2 - value1;
  if (difference > 100) {
    lightning++;
    
  }
  Serial.println(lightning);
  value1 = value2;
  value2 = analogRead(A0);
}

void readSensors() {
  /* This block prints the 
  temperature on the screen */
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

  /* This block prints the 
  pressure on the screen */
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

  /* This block prints the 
  altitude on the screen */
    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(2000);
}
