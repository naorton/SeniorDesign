
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
     //Serial.print ("adress found: "),Serial.print (i, DEC),Serial.print (" (0x"),Serial.print (i, HEX),Serial.println (")");
     nbr_module++;
   } 
 }
 delay(500);
// Serial.println ("Scan done");
// Serial.print ("there is "),Serial.print (nbr_module, DEC),Serial.println (" module(s) on the bus");
}

bool scan_16()
{
  int c=0;
  //Serial.print("15\t"); 
  Wire.requestFrom(16, 1);    
    
    while(Wire.available()){
    c = Wire.read(); // receive a byte as character
    //Serial.print(c);         // print the character
    if (c==1) 
      Serial.print("16\t"); 
    }
  if (c==1)
    return true;
  else
    return false;
  }

bool scan_15()
{
  int c=0;
  //Serial.print("15\t"); 
  Wire.requestFrom(15, 1);    
    
    while(Wire.available()){
    c = Wire.read(); // receive a byte as character
    //Serial.print(c);         // print the character
    if (c==1)
      Serial.print("15\t");
    }
  if (c==1)
    return true;
  else
    return false;
  }

bool scan_14()
{
  int c=0;
  //Serial.print("15\t"); 
  Wire.requestFrom(14, 1);    
    
    while(Wire.available()){
    c = Wire.read(); // receive a byte as character
    //Serial.print(c);         // print the character
    if (c==1)
      Serial.print("14\t");
    }
  if (c==1)
    return true;
  else
    return false;
  }

bool scan_13()
{
  int c=0;
  //Serial.print("15\t"); 
  Wire.requestFrom(13, 1);    
    
    while(Wire.available()){
    c = Wire.read(); // receive a byte as character
    //Serial.print(c);         // print the character
    if (c==1)
      Serial.print("13\t"); 
    }
  if (c==1)
    return true;
  else
    return false;
}

void loop()
{
i2c_scan_p();
if (scan_16()==false && scan_15()==false && scan_14==false && scan_13==false){
  Serial.print(99);
}
delay(500);
}
