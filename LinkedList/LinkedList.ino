//**********************************************************************//
//  BEERWARE LICENSE
//
//  This code is free for any use provided that if you meet the author
//  in person, you buy them a beer.
//
//  This license block is BeerWare itself.
//
//  Written by:  Marshall Taylor
//  Created:  420, 2015
//
//  The sketch outputs a series of operations on the pile to the serial
//  terminal.
//
//**********************************************************************//

//Includes
#include "MicroLL.h"

//instantiates MicroLL constructed to max depth of (n) stored notes
MicroLL myNotePile(100);

int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop()
{
  //This used to provide test note.  Can be controlled by midi
  listObject_t myPNote;
  Serial.println(freeRam());

  while (1)
  {
    myPNote.value = 24;
    myPNote.data = 64;
    Serial.print("Pushing note.\n");
    myNotePile.pushObject( myPNote );
    myNotePile.printfMicroLL();

    myPNote.value = 12;
    myPNote.data = 32;
    Serial.print("Pushing note.\n");
    myNotePile.pushObject( myPNote );
    myNotePile.printfMicroLL();

    Serial.print("dropping object number 2.\n");
    myNotePile.dropObject(2);
    myNotePile.printfMicroLL();
	
    myPNote.value = 19;
    myPNote.data = 40;
    Serial.print("Pushing note.\n");
    myNotePile.pushObject( myPNote );
    myNotePile.printfMicroLL();

    Serial.println(freeRam());

	Serial.print("dropping object number 2.\n");
    myNotePile.dropObject(2);
    myNotePile.printfMicroLL();

    Serial.print("Pushing 10 notes.\n");
    for ( int i = 1; i < 10; i++)
    {
      myPNote.value = i;
      myNotePile.pushObject( myPNote );
    }
    myNotePile.printfMicroLL();

    Serial.println(freeRam());
	
    Serial.print("dropping object number 5.\n");
    myNotePile.dropObject(5);
    myNotePile.printfMicroLL();
    Serial.println(freeRam());

	myPNote.value = 24;
    myPNote.data = 64;
    Serial.print("Pushing note.\n");
    myNotePile.pushObject( myPNote );
    myNotePile.printfMicroLL();
	Serial.println(freeRam());

    Serial.print("Pushing 10 more notes.\n");
    for ( int i = 10; i < 20; i++)
    {
      myPNote.value = i;
      myNotePile.pushObject( myPNote );
    }
    myNotePile.printfMicroLL();

    Serial.println(freeRam());
    
	while(1);
	
    Serial.print("Seeking notevalue 19.\n");
    Serial.print("Depth: ");
    Serial.println(myNotePile.seekObjectbyNoteValue( myPNote ));
    myNotePile.printfMicroLL();

    Serial.print("dropping 19.\n");
    myNotePile.dropObject(myNotePile.seekObjectbyNoteValue( myPNote ));
    myNotePile.printfMicroLL();

    Serial.print("attempt to pop 10 off\n");
    for ( int i = 0; i < 10; i++ )
    {
      //myNotePile.popObject();
    }
    myNotePile.printfMicroLL();

    Serial.print("seeking notevalue 24\n");
    myPNote.value = 24;
    Serial.print("Depth: ");
    Serial.println(myNotePile.seekObjectbyNoteValue( myPNote ));

    Serial.println(freeRam());

    delay(5000);

  }

}



