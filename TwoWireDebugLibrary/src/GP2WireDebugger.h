#include "stdint.h"

//Define the states of the machine
enum bitStates_t
{
  BEGIN_WAIT,
  CLK_CHANGED,
  CLK_WAIT,
  EXITING
};

class GP2WireDebugger
{
  public:
  uint8_t clockPin;
  uint8_t dataPin;
  
  uint8_t clockLine;
  uint8_t dataLine;
  
  GP2WireDebugger( void );
  void beginInputs( uint8_t, uint8_t );
  void beginOutputs( uint8_t, uint8_t );
  void sendByte( uint8_t );
  uint8_t getByte( void );
  void sendDebugString( char* );
  char hex2char( int );
  
};
