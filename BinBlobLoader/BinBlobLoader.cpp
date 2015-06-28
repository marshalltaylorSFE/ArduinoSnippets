//#include <stdio.h>
#include "stdint.h"
#include "Arduino.h"

extern uint8_t _binary_D__github_ArduinoSnippits_BinBlobLoader_SourceBlob_bin_start;
extern uint8_t _binary_D__github_ArduinoSnippits_BinBlobLoader_SourceBlob_bin_end;
extern uint8_t _binary_D__github_ArduinoSnippits_BinBlobLoader_SourceBlob_bin_size;
 
void setup()
{
	Serial.begin(9600);
	Serial.println("Program started.");
}
 
void loop()
{
  uint8_t *pblob = &_binary_D__github_ArduinoSnippits_BinBlobLoader_SourceBlob_bin_start;
  while(pblob < &_binary_D__github_ArduinoSnippits_BinBlobLoader_SourceBlob_bin_end)
  {
    Serial.println(*pblob, HEX);
    pblob++;
  }
  pblob = &_binary_D__github_ArduinoSnippits_BinBlobLoader_SourceBlob_bin_start;
  while(pblob < &_binary_D__github_ArduinoSnippits_BinBlobLoader_SourceBlob_bin_end)
  {
    Serial.println((char)*pblob);
    pblob++;
  }
  while(1);
}