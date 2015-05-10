#include "GP2WireDebugger.h"
#include "stdint.h"

GP2WireDebugger myDebugger;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  myDebugger.beginInputs(8, 10);
}

void loop() {
  // put your main code here, to run repeatedly:
  char c = myDebugger.getByte();
  if( c != 0 )
  {
    Serial.print(c);
  }
  else
  {
    Serial.print("\nNull Value\n");
    delay(250);
  }
  delay(1);
  
}

