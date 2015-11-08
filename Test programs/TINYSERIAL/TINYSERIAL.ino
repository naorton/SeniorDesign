#include <CapacitiveSensor.h>
#include "TinyDebugSerial.h"

CapacitiveSensor   cs_4_1 = CapacitiveSensor(4,1);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired


void setup() {
  
  cs_4_1.set_CS_AutocaL_Millis(0xFFFFFFFF); 
  Serial.begin(9600);
  
}

void loop() {
  
    long start = millis();
    long total1 =  cs_4_1.capacitiveSensor(30);
    Serial.print(total1);                  // print sensor output 1
    Serial.print("\t\n");

    delay(500); 
    
}
