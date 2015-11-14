#include <Wire.h>

static const int numberofsensors = 30;
bool IsAddressActive[numberofsensors+1];
bool IsSensorActive[numberofsensors+1];
unsigned long int sensorState = 0;

void setup()
{
  delay(2000);
  Serial.begin(115200);
  //Serial.println("Begin Setup...");
  // Initialize the boolean arrays
  for (int i=1; i<=numberofsensors; i++){
    IsAddressActive[i]=false;
    IsSensorActive[i]=false;
  }
  i2c_scan_bus();
}

void i2c_scan_bus()
{
  Wire.begin();
  for (byte i=1; i<=numberofsensors; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
    {
      IsAddressActive[i]=true;
      //Serial.print("Address:");
      //Serial.println(i);
    }
  }
}

void i2c_scan_sensors()
{
  for(int i=1; i<=numberofsensors; i++){
    if(IsAddressActive[i]){
      Wire.requestFrom(i, 1);
      while(Wire.available()){
        char c = Wire.read(); // receive a byte as character
        if(c == '1')
          IsSensorActive[i]=true;
        else
          IsSensorActive[i]=false;
      }
      //Wire.endTransmission();
    }
  }
}

unsigned long int bitArray2Numeral()
{
   unsigned long int numeral = 0;
   for (int i=30; i>0; i--)
   {
     if (IsSensorActive[i] && IsAddressActive[i]){
       numeral = numeral | (((unsigned long int)1) << (i - 1));
     }
   }
  return numeral;
}

void loop()
{  
  unsigned long int numeral = bitArray2Numeral();
  i2c_scan_sensors();
  if(sensorState != numeral){
    Serial.println(numeral, BIN);
    sensorState = numeral;
  }
  delay(125);
}
