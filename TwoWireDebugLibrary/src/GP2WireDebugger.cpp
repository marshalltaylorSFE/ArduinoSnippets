#include "Arduino.h"
#include "GP2WireDebugger.h"
#include "stdint.h"

uint8_t clockPin = 3;
uint8_t dataPin = 4;

uint8_t clockLine = 1;
uint8_t dataLine = 1;


GP2WireDebugger::GP2WireDebugger( void )
{
  clockPin = 3;
  dataPin = 4;

  clockLine = 1;
  dataLine = 1;

}

void GP2WireDebugger::beginInputs( uint8_t clockPinInput, uint8_t dataPinInput )
{
  clockPin = clockPinInput;
  dataPin = dataPinInput;

  pinMode( clockPin, INPUT );
  pinMode( dataPin, INPUT );

}

void GP2WireDebugger::beginOutputs( uint8_t clockPinInput, uint8_t dataPinInput )
{
  clockPin = clockPinInput;
  dataPin = dataPinInput;

  pinMode( clockPin, OUTPUT );
  pinMode( dataPin, OUTPUT );

}


void GP2WireDebugger::sendByte( uint8_t byteInput )
{
  //Variables
  int8_t currentBit = 7;
  //uint8_t pendingBits = 1;
  //digitalWrite(13, 1);
  while( currentBit >= 0 )
  {
    //Load the data bit
    dataLine = ( byteInput >> currentBit ) & 0x01;
    digitalWrite( dataPin, dataLine );
    //Serial.print( dataLine );
    //Dec the bit counter
    currentBit--;
    //Change the clock line
    clockLine ^= 0x01;
    digitalWrite( clockPin, clockLine );
    //Wait for a bit (the debugger should read here)
    delay(4);
  }
  //digitalWrite(13, 0);
}

uint8_t GP2WireDebugger::getByte( void )
{
  bitStates_t fsm_state = BEGIN_WAIT;
  uint8_t readingByte = 1;
  uint8_t bitCounter = 0;
  //Memorize the clock state on entry
  uint8_t lastClockLine = digitalRead( clockPin );
  uint8_t newClockLine;
  uint8_t outputByte = 0x00;
  uint8_t loopCounter = 0;
  
  //Do stuff
  while ( readingByte )
  {
    //Hit the state machine
    switch (fsm_state)
    {
      case BEGIN_WAIT:
        newClockLine = digitalRead( clockPin );
        if( newClockLine != lastClockLine )
        {
          fsm_state = CLK_CHANGED;
          lastClockLine = newClockLine;
        }
        break;
      case CLK_CHANGED:
        if( bitCounter < 8 )
        {
          //Record the bit
          outputByte = (outputByte & 0xFE) | digitalRead( dataPin );
          //shift
          bitCounter++;
          if( bitCounter >= 8 )
          {
            //Leave
            fsm_state = EXITING;
          }
          else
          {
            fsm_state = CLK_WAIT;
            outputByte = outputByte << 1;
            loopCounter = 0;
          }
        }
        break;
      case CLK_WAIT:
        newClockLine = digitalRead( clockPin );
        if( newClockLine != lastClockLine )
        {
          fsm_state = CLK_CHANGED;
          lastClockLine = newClockLine;
        }
        else
        {
          loopCounter++;
          delay(1);
          if(loopCounter > 50 )
          {
            readingByte = 0;
          }
        }
        break;
      case EXITING:
        delay(1);
        readingByte = 0;
        break;
      default:
        break;
    }
  }
  return outputByte;
  
}

void GP2WireDebugger::sendDebugString( char* stringInput )
{
  uint8_t i = 0;
  while( stringInput[i] != 0x00 )
  {
    sendByte( stringInput[i] );
    delay(20);
    i++;
  }

}

// This takes a int input and converts to char
//
// The output will be an char if the int
//  is between zero and 0xF
//
// Otherwise, the output is $.
//
char GP2WireDebugger::hex2char(int hexin)
{
  int charout;
  charout = 0x24; // default $ state
  if(hexin >= 0x00)
  {
    if(hexin <= 0x09)
    {
      charout = hexin + 0x30;
    }
  }
  if(hexin >= 0x0A)
  {
    if(hexin <= 0x0F)
    {
      charout = hexin -10 + 0x41;
    }
  }  
  return charout;
}