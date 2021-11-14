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
String msg1;
char msg2;
String msg3;
 
void setup()
{
    // Initialize ASK Object
    rf_driver.init();
    // Setup Serial Monitor
    Serial.begin(9600);

//    for(int i = 0; i<10; i++){
//      n = 0;
//      while (n < 1000){
//         buflen = sizeof(buf);                           // determina o tamanho do buffer
//          if (rf_driver.recv(buf, &buflen)){
//              String m = (String)((char*)buf);
//              m.remove(10);
//              n = m.toFloat();
//          }}}
        
}
 
void loop()
{
// Set buffer to size of expected message
    buflen = sizeof(buf);      // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {

      msg1 = (String)((char*)buf);
      msg2 = msg1.charAt(0);
      msg1.remove(0,1);
      
      if (msg2 == 'C'){  
        Serial.print("Altitude: ");               // print na console serial
        msg1.remove(5);
        Serial.print(msg1);   
        Serial.println(" m ");   
      }

      else if (msg2 == 'A'){
        Serial.print("Temperature: ");               // print na console serial                      // print do endereço do transmissor em Hexadecimal
        msg1.remove(5);
        Serial.print(msg1); 
        Serial.println(" °C ");   
      }

      else if (msg2 == 'B'){
        Serial.print("Pressure: ");               // print na console serial
        msg1.remove(10);
        Serial.print(msg1);
        Serial.println(" b "); 
      }

      total ++;
      }
      // Message received with valid checksum      
    
}
