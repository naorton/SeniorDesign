#include <TinyWireS.h>

const int busID = 4; // Bus address ID
const int triggerPin = 3; // Pin on the attiny85 used for sensor trigger
bool triggerState = true; // Boolean variable passed to master to indicate state of sensor 
const int ledPin =  1; // Pin on the attiny85 used for sensor trigger led notification
const int statemaxCount = 10000; // Delay between state change
int stateCount = 0; // Counter used in state change

void setup()                    
{
   pinMode(triggerPin, INPUT); // Attiny 85 trigger pin set as input
   digitalWrite(triggerPin, HIGH); // Attiny 85 trigger pin set high, grounding pin triggers state change
   pinMode(ledPin, OUTPUT); // Attiny85 pin set as output, used for LED notification
   TinyWireS.begin(busID); // Open connection on bus as slave
   TinyWireS.onRequest(requestEvent); // Method used on requestFrom call from master
}

void requestEvent()
{
  if(triggerState)
    TinyWireS.send('0');
  else
    TinyWireS.send('1');
}

void loop()       
{   
   if (digitalRead(triggerPin) == LOW){
     if(stateCount < statemaxCount)
       stateCount++;
     if(stateCount == statemaxCount){
       digitalWrite(ledPin, HIGH);
       triggerState = false;
     }  
   }
   else{
     if(stateCount > 0)
       stateCount--;
     if(stateCount == 0){
       digitalWrite(ledPin, LOW);
       triggerState = true;
     }
   }
}
