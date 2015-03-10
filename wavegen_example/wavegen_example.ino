#include "wavegen.h"

int stat1led = 7;
int stat2led = 6;

unsigned int wavetable[255];

// -----------------------------------------------------------------------------

void setup()
{
  digitalWrite( stat1led, 1 );
  digitalWrite( stat2led, 1 );
  pinMode(stat1led, OUTPUT);
  pinMode(stat2led, OUTPUT);

  // initialize serial:
  Serial.begin(9600);
  Serial.println("Pulse 80%, 25%");
  for(int i = 0; i < 256; i++)
  {
    wavetable[i] = get_sample( PULSESHAPE, 0.8, 0.25, i ); //shape, amp, duty, sample no.
  }
  
  for(int i = 0; i < 256; i = i + 32)
  {

    Serial.write(hex2char((wavetable[i] & 0xF0) >> 4));
    Serial.write(hex2char(wavetable[i] & 0x0F));
    Serial.print("\n");
  }
  
  Serial.println("Sine 50%");
  for(int i = 0; i < 256; i++)
  {
    wavetable[i] = get_sample( SINESHAPE, 0.5, 1, i ); //shape, amp, duty, sample no.
  }
  
  for(int i = 0; i < 256; i = i + 32)
  {

    Serial.write(hex2char((wavetable[i] & 0xF0) >> 4));
    Serial.write(hex2char(wavetable[i] & 0x0F));
    Serial.print("\n");
  }
  
  Serial.println("Last");
  for(int i = 0; i < 256; i++)
  {
    wavetable[i] = get_sample( PULSESHAPE, 1, 0.5, i ); //shape, amp, duty, sample no.
  }
  
  for(int i = 0; i < 256; i = i + 32)
  {

    Serial.write(hex2char((wavetable[i] & 0xF0) >> 4));
    Serial.write(hex2char(wavetable[i] & 0x0F));
    Serial.print("\n");
  }
  
}

void loop()
{
      
}





// This takes a int input and converts to char
//
// The output will be an char if the int
//  is between zero and 0xF
//
// Otherwise, the output is $.
//
char hex2char(int hexin)
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
