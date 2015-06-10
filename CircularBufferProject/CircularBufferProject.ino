//**********************************************************************//
//  BEERWARE LICENSE
//
//  This code is free for any use provided that if you meet the author
//  in person, you buy them a beer.
//
//  This license block is BeerWare itself.
//
//  Written by:  Marshall Taylor
//  Created:  June 9, 2015
//
//  This sketch creates a circular buffer and excercises it.
//  Note that the size is limited to a hard coded array allocation
//  within the CircularBuffer.h file.
//
//  TODO: Dynamically allocate memory.
//
//**********************************************************************//

#include "CircularBuffer.h"

CircularBuffer myBuffer(10);

void setup()
{
  Serial.begin(9600);
  
}

void loop()
{
  Serial.print("\nReading Empty Buffer\n");
  Serial.println(myBuffer.read(0));
  Serial.println(myBuffer.read(1));
  Serial.println(myBuffer.read(2));
  
  Serial.print("\nWriting some bytes\n");
  myBuffer.write(1);
  myBuffer.write(2);
  myBuffer.write(3);
  myBuffer.write(4);
  myBuffer.write(5);
  myBuffer.write(6);
  myBuffer.write(7);
  myBuffer.write(8);
  //myBuffer.write(9);
  //myBuffer.write(10);
  //myBuffer.write(11);
  //myBuffer.write(12);
  //myBuffer.write(13);
  
  Serial.print("\nReading up to offset 13\n");
  Serial.println(myBuffer.read(0));
  Serial.println(myBuffer.read(1));
  Serial.println(myBuffer.read(2));
  Serial.println(myBuffer.read(3));
  Serial.println(myBuffer.read(4));
  Serial.println(myBuffer.read(5));
  Serial.println(myBuffer.read(6));
  Serial.println(myBuffer.read(7));
  Serial.println(myBuffer.read(8));
  Serial.println(myBuffer.read(9));
  Serial.println(myBuffer.read(10));
  Serial.println(myBuffer.read(11));
  Serial.println(myBuffer.read(12));
  Serial.println(myBuffer.read(13));
  
  Serial.print("\nwhile(1); caught.\n");
  while(1);
}