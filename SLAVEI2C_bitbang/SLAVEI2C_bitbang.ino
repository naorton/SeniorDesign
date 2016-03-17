//#include <TinyWireS.h>

// Port for the I2C
#define I2C_DDR DDRB
#define I2C_PIN PINB
#define I2C_PORT PORTB
// Pins to be used in the bit banging
#define I2C_CLK 4
#define I2C_DAT 1
// Function calls for setting I2C pins hi or low
#define I2C_DATA_HI() I2C_DDR &= ~( 1 << I2C_DAT );
#define I2C_DATA_LO() I2C_DDR |=  ( 1 << I2C_DAT );
#define I2C_CLOCK_HI() I2C_DDR &= ~( 1 << I2C_CLK );
#define I2C_CLOCK_LO() I2C_DDR |=  ( 1 << I2C_CLK );
bool I2C_started = false;

#define busID 3 // eBus address ID
//#define triggerPin 3 // Pin on the attiny85 used for sensor trigger
//bool triggerState = true; // Boolean variable passed to master to indicate state of sensor 
#define ledPin 3 // Pin on the attiny85 used for sensor trigger led notification
//#define ledPinb 2
#define statemaxCount 50 // Delay between state change
int stateCount = 0; // Counter used in state change

void setup()                    
{
   //pinMode(triggerPin, INPUT); // Attiny 85 trigger pin set as input
   //digitalWrite(triggerPin, HIGH); // Attiny 85 trigger pin set high, grounding pin triggers state change
  I2C_Init();
  pinMode(ledPin, OUTPUT); // Attiny85 pin set as output, used for LED notification
  //pinMode(ledPinb, OUTPUT);
  digitalWrite(ledPin, LOW);
  //digitalWrite(ledPinb, LOW);
  //TinyWireS.begin(busID); // Open connection on bus as slave
  //TinyWireS.onRequest(requestEvent); // Method used on requestFrom call from master
}

//void requestEvent()
//{
//  if(triggerState)
//    TinyWireS.send('0');
//  else
//    TinyWireS.send('1');
//}

void loop()       
{
  I2C_Write_Byte(1,0,9);
  unsigned char c = I2C_Read_Byte(0,1);
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPinb, LOW);
  delay(10000);
}

// Inits bitbanging port, must be called before using the functions below
//
void I2C_Init()
{
  I2C_PORT &= ~( ( 1 << I2C_DAT ) | ( 1 << I2C_CLK ) );

  I2C_CLOCK_HI();
  I2C_DATA_HI();
  I2C_delay();
}

bool I2C_Start_Cond(void)
{
  if(I2C_started)
  {
    // If started, do a restart condition.  Set SDA to 1
    I2C_DATA_HI();
    I2C_delay();

    // Clock stretching.
    int count = 0;
    while ((I2C_PIN & (1 << I2C_CLK)) == 0 && (count < statemaxCount))
      count++;
    if(count == statemaxCount)
      return false;

    I2C_delay();
  }

  // SCL is high, set SDA from 1 to 0
  I2C_DATA_LO();
  I2C_delay();
  I2C_CLOCK_LO();
  I2C_delay();

  I2C_started = true;

  return true;
}

bool I2C_Stop_Cond(void)
{
  // Set SDA to 0
  I2C_DATA_LO();
  I2C_delay();

  // Clock stretching.
  int count = 0;
  while ((I2C_PIN & (1 << I2C_CLK)) == 0 && (count < statemaxCount))
    count++;
  if(count == statemaxCount)
    return false;
      
  // Stop bit setup time, minimum 4 microseconds
  I2C_delay();

  // SCL is high, set SDA from 0 to 1
  I2C_DATA_HI();
  I2C_delay();

  I2C_started = false;

  return true;
}

// Write a bit to I2C bus
bool I2C_Write_Bit(bool b)
{
  if(b)
  {
    I2C_DATA_HI();
  }
  else
  {
    I2C_DATA_LO();
  }

  // SDA change propagation delay
  I2C_delay();

  // Set SCL high to indicate a new valid SDA value is available
  I2C_CLOCK_HI();

  // Wait for SDA value to be read by the slave, minimum of 4 microseconds for standard mode
  I2C_delay();

  // Clock stretching.
  int count = 0;
  while ((I2C_PIN & (1 << I2C_CLK)) == 0 && (count < statemaxCount))
    count++;
  if(count == statemaxCount)
    return false;
      
  // Clear the SCL to low in preparation for next change
  I2C_CLOCK_LO();

  return true;
}

// Read a bit from I2C bus
bool I2C_Read_Bit(void)
{
  bool b;

  // Let the slave drive data
  I2C_DATA_HI();

  // Wait for SDA value to be written by slave, minimum of 4 microseconds for standard mode
  I2C_delay();

  // Set SCL high to indicate a new valid SDA value is available
  I2C_CLOCK_HI();

  // Clock stretching.
  int count = 0;
  while ((I2C_PIN & (1 << I2C_CLK)) == 0 && (count < statemaxCount))
    count++;

  // Wait for SDA value to be read by the slave, minimum of 4 microseconds for standard mode
  I2C_delay();

  // SCL is high, read out bit
  //b = I2C_PIN;  
  b = (I2C_PIN & (1 << I2C_DAT));

  // Set SCL low in preparation for next operation
  I2C_CLOCK_LO();
  I2C_delay();

  return b;
}

// Write a byte to I2C bus.  Return 0 if ack by the slave.
bool I2C_Write_Byte(bool send_start, bool send_stop, unsigned char c)
{
  bool nack;
  
  if(send_start)
  {
    I2C_Start_Cond();
  }

  for ( char i=0;i<8;i++)
  {
    I2C_Write_Bit((c & 128) != 0);
    c<<=1;
  }

  nack = I2C_Read_Bit();
  
  if(send_stop)
  {
    I2C_Stop_Cond();
  }

  return nack;
}

// Read a byte from I2C bus
unsigned char I2C_Read_Byte(bool nack, bool send_stop)
{
  unsigned char res = 0;

  for ( char i=0;i<8;i++)
  {
    res = (res << 1) | I2C_Read_Bit();   
  }

  I2C_Write_Bit(nack);

  if(send_stop)
  {
    I2C_Stop_Cond();
  }

  return res;
}

void I2C_delay(void)
{
  //delay(1000);
  delayMicroseconds(5);
}
