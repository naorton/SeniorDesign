#include <Wire.h>

static const int numberofsensors = 30; //  Number of sensors used in the array
bool IsAddressActive[numberofsensors+1]; // Boolean array that stores if address on bus is responding
bool IsSensorActive[numberofsensors+1]; // Boolean array that stores if the sensor has been triggered
String sensorState; // String containing the state of all sensors (eg. ten sensors with 9 active, 0000000010)

void setup()
{
  delay(2000); // Delay processing for 1 second
  Serial.begin(115200);
  
  // Zero out arrays
  for (int i=1; i<=numberofsensors; i++){
    IsAddressActive[i]=false;
    IsSensorActive[i]=false;
  }
  
  // Scan bus for all active addresses and mark them with '1' in array
  i2c_scan_bus();
}

// Scan bus for all active addresses and mark them with '1' in array
void i2c_scan_bus()
{
  Wire.begin(); // Open master connection on I2C bus
  for (byte i=1; i<=numberofsensors; i++)
  {
    // Begin transmission on the bus to search for active addresses
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
      IsAddressActive[i]=true;
  }
}

// Scan bus for triggered sensors and mark with '1' in array
void i2c_scan_sensors()
{
  for(int i=1; i<=numberofsensors; i++){
    if(IsAddressActive[i]){
      Wire.requestFrom(i, 1); // Start a request for state of sensor
      while(Wire.available()){
        char c = Wire.read(); // receive a byte as character
        if(c == '1')
          IsSensorActive[i]=true;
        else
          IsSensorActive[i]=false;
      }
    }
  }
}

// Method builds a string of bits from array to be sent on the usb serial bus
String bitArray2String()
{
   String string;
   for (int i=1; i<=numberofsensors; i++)
   {
     if (IsSensorActive[i] && IsAddressActive[i])
       string = string + "1";
     else
       string = string + "0";
   }
   return string;
}

void loop()
{
  String string = bitArray2String(); 
  i2c_scan_sensors();
  if(sensorState != string){
    Serial.println(string); // String with active sensors sent to usb serial bus
    sensorState = string;
  }
  delay(125); // One-sixteenth of a second delay
}
