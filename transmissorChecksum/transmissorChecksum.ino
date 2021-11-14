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
    delay(270);
    
    String stringTemp = (String)(bmp.readTemperature());
    stringTemp = "A" + stringTemp;
    char Temp[8];
    stringTemp.toCharArray(Temp, 10);
    rf_driver.send((uint8_t *)Temp, strlen(Temp));
    rf_driver.waitPacketSent();

    delay(170);
  
    String stringPressure = (String)(bmp.readPressure());
    stringPressure = "B" + stringPressure;
    char Pressure[8];
    stringPressure.toCharArray(Pressure, 10); 
    rf_driver.send((uint8_t *)Pressure, strlen(Pressure));
    rf_driver.waitPacketSent();

    delay(170);
    
    String stringAlt = (String)(bmp.readAltitude(1018.74));
    stringAlt = "C" + stringAlt;// Ajusted to local forcast
    char Alt[8];
    stringAlt.toCharArray(Alt, 10);
    rf_driver.send((uint8_t *)Alt, strlen(Alt));
    rf_driver.waitPacketSent();   


}
