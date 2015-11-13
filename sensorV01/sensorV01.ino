#include "TinyWireS.h" 

const int buttonPin = 4;
const int ledPin =  1; 
int buttonState = 0;

void setup()                    
{
   pinMode(buttonPin, INPUT);
   pinMode(ledPin, OUTPUT);
   TinyWireS.begin(1);  
   //Serial.begin(9600);
}

void loop()       
{   
    buttonState = digitalRead(buttonPin);
    byte data1 = 1;
    byte data2 = 0;

    //Serial.println(buttonState);
    if (buttonState == HIGH){
        digitalWrite(ledPin, HIGH);
        TinyWireS.send(data1);
        }
     else{
         digitalWrite(ledPin, LOW);
         TinyWireS.send(data2);
      }
    delay(125);
}
