#include <CapacitiveSensor.h>
//#include "TinyDebugSerial.h"
#include "TinyWireS.h"   

int RED_PIN = 0;

CapacitiveSensor   cs_4_1 = CapacitiveSensor(4,1);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
                        
void setup()                    
{
   cs_4_1.set_CS_AutocaL_Millis(0xFFFFFFFF);        // turn off autocalibrate on channel 1 - just as an example
   TinyWireS.begin(17);  
   Serial.begin(9600);
}

void loop()       
{
    long start = millis();
    long total1 =  cs_4_1.capacitiveSensor(30);    
    byte data1 = 1;
    byte data2 = 0;
    
    if(total1>50){
        digitalWrite(RED_PIN,HIGH);
    
        TinyWireS.send(data1);
        }
       
     else{
     digitalWrite(RED_PIN,LOW);
       TinyWireS.send(data2);
      }
    Serial.print(total1);                  // print sensor output 1
    Serial.print("\t\n");

    delay(1000);                             // arbitrary delay to limit data to serial port 
}

