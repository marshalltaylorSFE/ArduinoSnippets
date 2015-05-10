//**********************************************************************//
//  BEERWARE LICENSE
//
//  This code is free for any use provided that if you meet the author
//  in person, you buy them a beer.
//
//  This license block is BeerWare itself.
//
//  Written by:  Marshall Taylor
//  Created:  March 21, 2015
//
//**********************************************************************//

//This is a kind of asyncronous thing

#define LEDPIN 13
#include "timerModule.h"
#include "stdint.h"

//Globals
TimerClass msTimerA( 20 );
TimerClass msTimerB( 21 );
TimerClass msTimerC( 10 );

uint16_t msTicks = 0;
uint8_t msTicksMutex = 1; //start locked out

float sCount = 0;
uint8_t msTensCount = 0;

#define MAXINTERVAL 2000

void setup() {
  Serial.begin(115200);  //A real man's baud

  pinMode(LEDPIN, OUTPUT);

  // initialize Timer1
  {
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

}


int i = 0;
int intervalSeed = 20;
void loop()
{
  // main program
  
  if( msTicksMutex == 0 )  //Only touch the timers if clear to do so.
  {
    msTimerA.update(msTicks);
    msTimerB.update(msTicks);
    msTimerC.update(msTicks);
    
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
  if(msTimerC.flagStatus() == PENDING)
  {
    Serial.println(sCount, 2);
    sCount = sCount + 0.01;
    msTensCount++;
  }
  i++;
  delay(1);
  if(i > 100)
  {
    i = 0;
    msTimerA.setInterval(intervalSeed);
    intervalSeed++;
    msTimerB.setInterval(intervalSeed);

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


