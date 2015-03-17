#include "chartools.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Serial.println("Testing serial monitor...\n");
  int myInteger = 0xF1AB;
  char myString[9];
  hexString(myString, myInteger, 4);
  Serial.println(myString);
}

void loop() 
{

  
}
