#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <RHReliableDatagram.h>                      // biblioteca Radiohead reliableDatagram
#include <RH_ASK.h>                                  // biblioteca Radiohead ASK
#include <SPI.h>                                     // biblioteca SPI

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
#define TX_ADDRESS 1                                 // endereço do transmissor
#define RX_ADDRESS 2                                 // endereço do recept


Adafruit_BMP280 bmp; 

RH_ASK driver;                                       // instância RH ASK
RHReliableDatagram gerente(driver, TX_ADDRESS);      // configurando o gerenciador

uint8_t count = 1;  
// contador

void setup()
{
  Serial.begin(9600);                                // inicializa console serial 9600 bps
  if (!gerente.init())                               // se a inicialização do gerenciador falhar
    Serial.println("Falha na inicializacao");        // print na console serial

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
    Serial.print(bmp.readTemperature());
    String stringTemp = (String)(bmp.readTemperature());
    char Temp[50];
    stringTemp.toCharArray(Temp, 50);
    driver.send((uint8_t *)Temp, strlen(Temp));
    driver.waitPacketSent();
    !gerente.sendtoWait(Temp, sizeof(Temp), RX_ADDRESS);

    String stringPressure = (String)(bmp.readPressure());
    char Pressure[50];
    stringPressure.toCharArray(Pressure, 50); 
    driver.send((uint8_t *)Pressure, strlen(Pressure));
    driver.waitPacketSent();
    !gerente.sendtoWait(Pressure, sizeof(Pressure), RX_ADDRESS);

    String stringAlt = (String)(bmp.readAltitude(1021.74)); // Ajusted to local forcast
    char Alt[50];
    stringAlt.toCharArray(Alt, 50);
    driver.send((uint8_t *)Alt, strlen(Alt));
    driver.waitPacketSent();
    !gerente.sendtoWait(Alt, sizeof(Alt), RX_ADDRESS);


    delay(250);                                             // atraso 0,25 segundo
}
