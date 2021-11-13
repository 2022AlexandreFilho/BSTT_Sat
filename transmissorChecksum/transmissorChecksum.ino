#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <RHReliableDatagram.h>                      // biblioteca Radiohead reliableDatagram
#include <RH_ASK.h>                                  // biblioteca Radiohead ASK
#include <SPI.h>    


#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
#define TX_ADDRESS 1                                 // endereço do transmissor
#define RX_ADDRESS 2     

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

Adafruit_BMP280 bmp; 
 
void setup()
{
  Serial.begin(9600);
  
    rf_driver.init();
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
 
void loop()
{
    String stringTemp = (String)(bmp.readTemperature());
    char Temp[10];
    stringTemp.toCharArray(Temp, 10);
    rf_driver.send((uint8_t *)Temp, strlen(Temp));
    rf_driver.waitPacketSent();

    delay(120);
  
    String stringPressure = (String)(bmp.readPressure());
    char Pressure[10];
    stringPressure.toCharArray(Pressure, 10); 
    rf_driver.send((uint8_t *)Pressure, strlen(Pressure));
    rf_driver.waitPacketSent();

    delay(120);
    
    String stringAlt = (String)(bmp.readAltitude(1018.74)); // Ajusted to local forcast
    char Alt[10];
    stringAlt.toCharArray(Alt, 10);
    rf_driver.send((uint8_t *)Alt, strlen(Alt));
    rf_driver.waitPacketSent();   

    delay(120);

}
