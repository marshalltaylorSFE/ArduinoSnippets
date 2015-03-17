// Arduino timer CTC interrupt example
//
// avr-libc library includes
//#include <avr/io.h>
//#include <avr/interrupt.h>
#define LEDPIN 13

//tick variable
long ms_ticks = 0;
int last_input = 0;


void setup()
{
  //Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  // initialize Timer1
  cli();          // disable global interrupts
  TCCR1A = _BV(COM1A0);     // set pin 9 as output enabled
  TCCR1B = 0;     // same for TCCR1B

  // set compare match register to desired timer count:
  OCR1A = 16000;
  pinMode(9, OUTPUT);

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
  int new_input = analogRead(0) + 1;
  //if((new_input > last_input + 2)||(new_input < last_input - 2))
  if((new_input != last_input))
  {
    OCR1A = (float)new_input * (-.29297) + 400; 
    last_input = new_input;
  }
  
  // main program
  if( ms_ticks > 1000 )
  {
    ms_ticks = ms_ticks - 1000;
    // Toggle LED
    digitalWrite( LEDPIN, digitalRead(LEDPIN) ^ 1 );
    //Serial.println(ms_ticks);
  }
}

ISR(TIMER1_COMPA_vect)
{
  ms_ticks++;
  //digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}

