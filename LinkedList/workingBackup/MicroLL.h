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
#ifndef MICROLL_H_INCLUDED
#define MICROLL_H_INCLUDED

#include "stdint.h"

//Depth into the stack variable
typedef uint8_t listDepth_t;

//Note data type
struct midiEvent
{
  uint32_t timestamp;
  int8_t eventType;
  uint8_t channel;
  uint8_t value;
  uint16_t data;
  

  //A pointer to the lower object
  midiEvent * lowerObject;

};

//Point ListObject_t to custom object type
typedef midiEvent listObject_t;

#define NULLNOTE -1

class MicroLL
{
    listDepth_t maxDepth;
    listDepth_t currentDepth;

  public:
    //A pointer to the upper most note
    listObject_t * topObject;
	//A empty note to point to when the list is empty
    listObject_t nullObject;

  public:
    MicroLL( listDepth_t ); //Construct with passed max depth
    MicroLL( void );
    void pushObject( listObject_t & ); //Pass listObject_t
    listObject_t popObject( void ); //returns listObject_t
    listObject_t peekObject( void );
    listObject_t peekObject( listDepth_t );
    void dropObject( listDepth_t ); //Pass position, returns listObject_t
	int8_t seekObjectbyTimeStamp( listObject_t & ); //pass listObject_t, returns position
	int8_t seekObjectbyNoteValue( listObject_t & ); //pass listObject_t, returns position
    listDepth_t listDepth( void ); //returns depth of stack.
    void printfMicroLL( void );


};

#endif // FILE_H_INCLUDED

