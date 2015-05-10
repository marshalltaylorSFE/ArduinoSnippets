// SPI Master Probe

//These pins must be set as input
//SPI pin numbers:
//SCK   13  // Serial Clock.
//MISO  12  // Master In Slave Out.
//MOSI  11  // Master Out Slave In.
//SS    10  // Slave Select
#define SSalt 8

// Include SPI (Serial Peripheral Interface) library.
#include <SPI.h>

// The setup() function runs after reset.
void setup()
{
  // Initialize SPI.
  // SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin();
  //Do the alt pin too
  pinMode(SSalt, OUTPUT);
  
  // Slow down the master a bit
  //SPI.setClockDivider(SPI_CLOCK_DIV8);
}

void loop()
{
  sendDebugByte('A');
  sendDebugString("\nHoly Hell!\n");
  
  delay(1000);

}

void sendDebugString( char* stringInput )
{
  uint8_t i = 0;
  while( stringInput[i] != 0x00 )
  {
    sendDebugByte( stringInput[i] );
    i++;
  }

}


void sendDebugByte( uint8_t charInput )
{

  // Select and wait for slave.
  digitalWrite(SSalt, LOW);
  delay(30);
  
  //Send data
  SPI.transfer(charInput);
  // Wait for slave.
  delay(30);
  // Disable slave.
  digitalWrite(SSalt, HIGH);     
  // Debounce master button.
  delay(10);

}

