// Arduino timer CTC interrupt example
//
// avr-libc library includes
//#include <avr/io.h>
//#include <avr/interrupt.h>
#define LEDPIN 13
#include "timerModule.h"
#include "stdint.h"

//Globals
TimerClass msTimerA( 20 );
TimerClass msTimerB( 21 );

uint16_t msTicks = 0;
uint8_t msTicksMutex = 1; //start locked out

#define MAXINTERVAL 2000

void setup()
{
  //Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  // initialize Timer1
  cli();          // disable global interrupts
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B

  // set compare match register to desired timer count:
  OCR1A = 16000;

  // turn on CTC mode:
  TCCR1B |= (1 << WGM12);

  // Set CS10 and CS12 bits for 1 prescaler:
  TCCR1B |= (1 << CS10);


  // enable timer compare interrupt:
  TIMSK1 |= (1 << OCIE1A);

  // enable global interrupts:
  sei();
}

void loop()
{
  // main program
  
  if( msTicksMutex == 0 )  //Only touch the timers if clear to do so.
  {
    msTimerA.update(msTicks);
    msTimerB.update(msTicks);
    //Done?  Lock it back up
    msTicksMutex = 1;
  }  //The ISR should clear the mutex.
  
  
  if(msTimerA.flagStatus() == PENDING)
  {
    digitalWrite( LEDPIN, digitalRead(LEDPIN) ^ 1 );
  }
  if(msTimerB.flagStatus() == PENDING)
  {
    digitalWrite( LEDPIN, digitalRead(LEDPIN) ^ 1 );
  }


}


ISR(TIMER1_COMPA_vect)
{
  uint32_t returnVar = 0;
  if(msTicks >= ( MAXTIMER + MAXINTERVAL ))
  {
    returnVar = msTicks - MAXTIMER;

  }
  else
  {
    returnVar = msTicks + 1;
  }
  msTicks = returnVar;
  msTicksMutex = 0;  //unlock
}


