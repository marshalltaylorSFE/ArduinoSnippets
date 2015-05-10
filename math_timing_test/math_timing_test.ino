// Arduino timer CTC interrupt example
//
// avr-libc library includes
//#include <avr/io.h>
//#include <avr/interrupt.h>
#include "math.h"

#define LEDPIN 13

//tick variable
double ms_ticks = 0;


void setup()
{
  Serial.begin(9600);
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
  // Do a control loop test
  Serial.println("\nFirst running an increment only test.\n");

  Serial.println("ms_ticks cleared.");
  volatile float accumulator = 0;
  ms_ticks = 0;
  for( long i = 0; i < 100000; i++ )
  {
    accumulator++;
  }
  Serial.println("100000 cycles complete.");
  Serial.print("Job took ");
  Serial.print(ms_ticks);
  Serial.println("ms.");
  Serial.print("That's like ");
  Serial.print(ms_ticks/100);
  Serial.println(" microseconds each!");
  Serial.print("Or, a frequency of ");
  Serial.print((float)1000000/(float)ms_ticks);
  Serial.println("kHz.");
  Serial.print("Debug chaff: ");
  Serial.print(accumulator, 4);
  Serial.println(".");

  //Now do a math function
  Serial.println("\nRunning a x^3 operation.\n");

  Serial.println("Clearing ms_ticks.");
  accumulator = 0;
  ms_ticks = 0;
  for( long i = 0; i < 100000; i++ )
  {
    accumulator = pow(accumulator, 3.0);
  }
  Serial.println("100000 cycles, captain.");
  Serial.print("Job took ");
  Serial.print(ms_ticks);
  Serial.println("ms.");
  Serial.print("That's like ");
  Serial.print(ms_ticks/100);
  Serial.println(" microseconds each!");
  Serial.print("Or, a frequency of ");
  Serial.print((float)1000000/(float)ms_ticks);
  Serial.println("kHz.");
  Serial.print("Debug chaff: ");
  Serial.print(accumulator, 4);
  Serial.println(".");  

  //OK, now do some real math.
  Serial.println("\nCalculating Envelope amplitude value.\n");

  Serial.println("Clearing ms_ticks.");
  uint8_t x = 34;
  accumulator = 0;
  //for( long j = 0; j < 1000; j++ )
  //{
    //Serial.println("ok,");
    ms_ticks = 0;
    volatile uint8_t maxAmp = 255;
    volatile uint16_t timeVar = 500;
    volatile uint16_t timeScale = 1000;
    volatile int8_t powerScale = -62;

    for( long i = 0; i < 1000; i++ )
    {
      x++;
      accumulator = (uint16_t)(maxAmp*(float)pow(((float)timeVar/(float)timeScale), (exp((double)2*(float)powerScale/127))));
      analogWrite(11, accumulator);
    }
    volatile float debugTemp = (exp((double)2*(float)powerScale/127));
  //}
  Serial.println("1000 cycles, captain.");
  Serial.print("Job took ");
  Serial.print(ms_ticks);
  Serial.println("ms.");
  Serial.print("That's like ");
  Serial.print(ms_ticks);
  Serial.println(" microseconds each!");
  Serial.print("Or, a frequency of ");
  Serial.print((float)1000000/(float)ms_ticks);
  Serial.println("Hz.");
  Serial.print("Debug chaff: ");
  Serial.print(accumulator, 4);
  Serial.print(accumulator, 4);
  Serial.println(".");    

  //tick timer forever
  ms_ticks = 0;
  while(1)
  {
    if( ms_ticks > 1000 )
    {
      ms_ticks = ms_ticks - 1000;
      // Toggle LED
      digitalWrite( LEDPIN, digitalRead(LEDPIN) ^ 1 );
      //Serial.println(ms_ticks);
    }
  }
}

ISR(TIMER1_COMPA_vect)
{
  ms_ticks++;
  //digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}



