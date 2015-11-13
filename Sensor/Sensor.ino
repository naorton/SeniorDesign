#include "TinyWireS.h" 

const int buttonPin = 4;
const int ledPin =  1; 
int buttonState = 0;

enum STATES
{
  buttonHigh,
  buttonLow,
  buttonIdle,
  buttonDebounce
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
    
      switch(state){
        
        case buttonLow:
          digitalWrite(ledPin, LOW);
          TinyWireS.send(data2);
          if (buttonState == LOW){
            
          }
          if (buttonState == HIGH) state = buttonDebounce;
          break;
        case buttonDebounce:
          
          
          
            
            
    
    
    
    
    
    //Serial.println(buttonState);
    if (buttonState == HIGH){
        digitalWrite(ledPin, HIGH);
        TinyWireS.send(data1);
        }
     else{
       
      }
    delay(1000);
}

