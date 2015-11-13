#include "TinyWireS.h" 

const int buttonPin = 4;
const int ledPin =  1; 
int buttonState = 0;

enum STATES
{
  buttonHigh,
  buttonLow,
  buttonDebounce
};

void setup()                    
{
   pinMode(buttonPin, INPUT);
   pinMode(ledPin, OUTPUT);
   TinyWireS.begin(20);  
   //Serial.begin(9600);
}

void loop()       
{   
    
    byte data1 = 1;
    byte data2 = 0;
    STATES state = buttonLow;
    
    while(1)
    {
      buttonState = digitalRead(buttonPin);
      
      switch(state)
      {
        case buttonLow:
          if(buttonState == LOW){
           digitalWrite(ledPin,LOW);
          }
          else if(buttonState ==HIGH){ 
            state = buttonDebounce;
          }
          break;
        case buttonDebounce:
          if(buttonState == LOW){
            state = buttonLow;
            }
          else{
            digitalWrite(ledPin, HIGH);
            TinyWireS.send(data1);
            state = buttonHigh;
            }
            break;

        case buttonHigh:
          if(buttonState == LOW){
            state = buttonLow;
          }
          else{
            }
            break;
          }
          }   
}

