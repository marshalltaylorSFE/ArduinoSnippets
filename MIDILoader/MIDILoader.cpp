//#include <stdio.h>
#include "stdint.h"
#include "Arduino.h"

#define _midi1_start _binary_D__github_ArduinoSnippits_MIDILoader_midi1_mid_start
#define _midi1_end _binary_D__github_ArduinoSnippits_MIDILoader_midi1_mid_end
#define _midi1_size _binary_D__github_ArduinoSnippits_MIDILoader_midi1_mid_size



extern uint8_t _midi1_start;
extern uint8_t _midi1_end;
extern uint8_t _midi1_size;
 
void setup()
{
	Serial.begin(9600);
	Serial.println("Program started.");
}
 
void loop()
{
  uint8_t *pblob = &_midi1_start;
  while(pblob < &_midi1_end)
  {
    Serial.println(*pblob, HEX);
    pblob++;
  }
  pblob = &_midi1_start;
  while(pblob < &_midi1_end)
  {
    Serial.println((char)*pblob);
    pblob++;
  }
  while(1);
}