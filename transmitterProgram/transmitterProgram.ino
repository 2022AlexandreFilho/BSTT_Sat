#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver(2000, 4, 2, 5);

void setup()
{
    Serial.begin(115200);	  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    const char * msg = "hello";

    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(200);
}
