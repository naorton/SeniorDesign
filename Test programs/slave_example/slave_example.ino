

#include "TinyWireS.h"                  // wrapper class for I2C slave routines

#define I2C_SLAVE_ADDR  0x26            // i2c slave address (38)


void setup(){
 
  TinyWireS.begin(I2C_SLAVE_ADDR);  // init I2C Slave mode
  
}


void loop(){
                    
 uint8_t data[] = "Hello ";
  if (TinyWireS.available()){
   TinyWireS.send(data[6]);  

  }

  }





