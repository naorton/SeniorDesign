
#include "Wire.h"

void setup()
{
 Wire.begin();
 Serial.begin(115200);                    
 Serial.println ("IC2 master starting");
}


void i2c_scan_p()
{
 Serial.println ();
 //Serial.println ("Scanning");
 int nbr_module = 0;
 Wire.begin();
 for (byte i = 1; i < 127; i++)
 {
   Wire.beginTransmission (i);
   if (Wire.endTransmission () == 0)
   {
     Serial.print ("adress found: "),Serial.print (i, DEC),Serial.print (" (0x"),Serial.print (i, HEX),Serial.println (")");
     nbr_module++;
   } 
 }
 delay(500);
// Serial.println ("Scan done");
 Serial.print ("there is "),Serial.print (nbr_module, DEC),Serial.println (" module(s) on the bus");
}

void scan_15()
{
  Serial.print("15\t"); 
  Wire.requestFrom(15, 1);    
    
    while(Wire.available()){
    int c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
    }
  
  }

void scan_14()
{
   Serial.print("\n14\t"); 
  Wire.requestFrom(14, 1);    
    
    while(Wire.available()){
    int c = Wire.read(); // receive a byte as character
    Serial.print(c );         // print the character
    }
  }

void scan_13()
{
  Serial.print("\n13\t"); 
  Wire.requestFrom(13, 1);    
    
    while(Wire.available()){
    int c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
    }
  
  }

void scan_16()
{
  Serial.print("\n16\t"); 
  Wire.requestFrom(16, 1);    
    
    while(Wire.available()){
    int c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
    }
  
  }

void loop()
{
i2c_scan_p();
scan_15();
scan_14();
scan_13();
scan_16();
delay(500);
}
