#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

static const int numberofsensors = 30;
bool IsAddressActive[numberofsensors+1];
bool IsSensorActive[numberofsensors+1];

void setup()
{
  lcd.begin(16, 2);
  
  Wire.begin();
  Serial.begin(115200);                    
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
    }
  }
}

void i2c_scan_sensors()
{
  for(int i=1; i<=numberofsensors; i++){
    if(IsAddressActive[i]){
      Wire.requestFrom(i, 1);    
      while(Wire.available()){
        int c = Wire.read(); 
        if(c==1)
          IsSensorActive[i]=true;
        else
          IsSensorActive[i]=false;
      }
    }
  }
}

unsigned long int bitArray2Numeral()
{
   unsigned long int numeral = 0;
   for (int i=1; i<=numberofsensors; i++)
   {
     if (IsSensorActive[i] && IsAddressActive[i]){
       numeral = numeral | (((unsigned long int)1) << (numberofsensors - i));
     }
   }
  return numeral;
}

void bus_Display()
{
  int nbr_module = 0;
 Wire.begin();
 for (int i = 1; i < 127; i++)
 {
   Wire.beginTransmission (i);
   if (Wire.endTransmission () == 0)
   {
     //Serial.print ("adress found: "),Serial.print (i, DEC),Serial.print (" (0x"),Serial.print (i, HEX),Serial.println (")");
     nbr_module++;
   } 
 }
   delay(500);
   lcd.setCursor(0,0);
   lcd.print(nbr_module,DEC);
   lcd.print("-Module(s)."); 
  }


void loop()
{
  bus_Display();

  i2c_scan_sensors();
  if(bitArray2Numeral() != 0){
      Serial.println (bitArray2Numeral());
  }
  delay(125);
}
