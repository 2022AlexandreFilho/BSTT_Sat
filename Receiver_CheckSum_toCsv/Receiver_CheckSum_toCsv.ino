// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
uint8_t buflen;

int total = 0;
float n = 0;
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

      while (n < 5){
         buflen = sizeof(buf);                           // determina o tamanho do buffer
          if (rf_driver.recv(buf, &buflen)){
             msg1 = (String)((char*)buf);
             msg2 = msg1.charAt(0);
             if (msg2 == 'C'){
                n++;
          }}}

        
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
      
      if (msg2 == 'C'){             // print na console serial
        msg1.remove(5);
 //       msg3 = msg1.toFloat();
        Serial.print(msg1);
        Serial.println(";");

   
      }

      else if (msg2 == 'A'){
              // print na console serial                      // print do endereço do transmissor em Hexadecimal
        msg1.remove(5);
//        msg3 = msg1.toFloat();
        Serial.print(msg1);
        Serial.print(";");

      }

      else if (msg2 == 'B'){        // print na console serial
        msg1.remove(10);
 //       msg3 = msg1.toFloat();
        Serial.print(msg1);
        Serial.print(";");

      }

      }
      // Message received with valid checksum      
    
}
