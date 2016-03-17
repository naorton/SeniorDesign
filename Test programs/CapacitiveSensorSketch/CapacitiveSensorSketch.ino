#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */
int RED_PIN = 1;
int csTolerance = 1000;

CapacitiveSensor cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

void setup()                    
{
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);   // turn off autocalibrate on channel 1 - just as an example
   pinMode(RED_PIN, OUTPUT);
   Serial.begin(9600);
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

    if(total1>csTolerance){
      digitalWrite(RED_PIN, LOW);
    } else{
      digitalWrite(RED_PIN, HIGH);
      }
    
    Serial.print(total1);                  // print sensor output 1
    Serial.print("\t\n");

    delay(100);                             // arbitrary delay to limit data to serial port 
}
