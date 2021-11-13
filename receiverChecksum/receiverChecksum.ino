// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
uint8_t buflen;

int total = 0;
float n = 5;
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
 
void setup()
{
    // Initialize ASK Object
    rf_driver.init();
    // Setup Serial Monitor
    Serial.begin(9600);

    for(int i = 0; i<10; i++){
      while (n < 1000){
         buflen = sizeof(buf);                           // determina o tamanho do buffer
          if (rf_driver.recv(buf, &buflen)){
              String m = (String)((char*)buf);
              m.remove(10);
              n = m.toFloat();
          }}}
        
}
 
void loop()
{
    // Set buffer to size of expected message
    buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {

      if (total%3==0){  
        Serial.print("Altitude: ");               // print na console serial
        String string = (String)((char*)buf);
        string.remove(5);
        Serial.print(string);   
        Serial.println(" m ");   
      }

      else if (total%3==1){
        Serial.print("Temperature: ");               // print na console serial                      // print do endereço do transmissor em Hexadecimal
        String string = (String)((char*)buf);
        string.remove(5);
        Serial.print(string); 
        Serial.println(" °C ");   
      }

      else if (total%3==2){
        Serial.print("Pressure: ");               // print na console serial
        String string = (String)((char*)buf);
        string.remove(10);
        Serial.print(string);
        Serial.println(" b "); 
      }

      total ++;
      // Message received with valid checksum      
    }
}
