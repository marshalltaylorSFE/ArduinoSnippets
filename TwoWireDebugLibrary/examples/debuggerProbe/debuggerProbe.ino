#include "GP2WireDebugger.h"
#include "stdint.h"

GP2WireDebugger myDebugger;

void setup() {
  // put your setup code here, to run once:
  myDebugger.beginOutputs(8, 10);//Clock, data
  pinMode(13, OUTPUT);
  Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  myDebugger.sendByte('*');
  uint8_t myByte = 0xAE;
  myDebugger.sendByte(myDebugger.hex2char((myByte >> 4) & 0x0F));
  myDebugger.sendByte(myDebugger.hex2char((myByte) & 0x0F));
  sendDebugString("\nTest message.\n");
  delay(1000);
  
}

void sendDebugString( char* stringInput )
{
  uint8_t i = 0;
  while( stringInput[i] != 0x00 )
  {
    myDebugger.sendByte( stringInput[i] );
    delay(20);
    i++;
  }

}