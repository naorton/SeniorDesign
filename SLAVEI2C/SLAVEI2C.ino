#include <TinyWireS.h>
//fuck off
const int busID = 14;
const int triggerPin = 3;
bool triggerState = true;
const int ledPin =  1; 
const int statemaxCount = 10000;
int stateCount = 0;


void setup()                    
{
   pinMode(triggerPin, INPUT);
   digitalWrite(triggerPin, HIGH);
   pinMode(ledPin, OUTPUT);
   TinyWireS.begin(busID);
   TinyWireS.onRequest(requestEvent);
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
