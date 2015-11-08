#include "TinyWireS.h" 

const int buttonPin = 4;
const int ledPin =  1; 
int buttonState = 0;

enum STATES
{
  buttonHigh,
  buttonLow
};

void setup()                    
{
   pinMode(buttonPin, INPUT);
   pinMode(ledPin, OUTPUT);
   TinyWireS.begin(14);  
   //Serial.begin(9600);
}

void loop()       
{   
    buttonState = digitalRead(buttonPin);
    byte data1 = 1;
    byte data2 = 0;
    STATES state = buttonLow;
    
    while(1)
    {
    
      switch(state)
      {
        case buttonLow:
          digitalWrite(ledPin, LOW);
          TinyWireS.send(data2);
          
          switch(state)
          {
            case buttonLow:
              
              break;
            
            
    
    
    
    
    
    //Serial.println(buttonState);
    if (buttonState == HIGH){
        digitalWrite(ledPin, HIGH);
        TinyWireS.send(data1);
        }
     else{
       digitalWrite(ledPin, LOW);
       TinyWireS.send(data2);
      }
    delay(1000);
}

