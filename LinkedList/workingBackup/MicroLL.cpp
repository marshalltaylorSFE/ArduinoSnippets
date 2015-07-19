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
//  depth 0 is 0 notes.  Shall point to null
//
//
//**********************************************************************//

//Includes
#include "MicroLL.h"
#include "stdint.h"
#include "Arduino.h"

//**********************************************************************//
//  MicroLL Class
//
//  Creates link list
//
//  Construct with passed max depth or use default 4
//
MicroLL::MicroLL( listDepth_t inputDepth )
{
  topObject = &nullObject;  //start pointed to null note
  currentDepth = 0 ;  //Size 0
  maxDepth = inputDepth;  //set max size
  nullObject.eventType = -1;  //define null note

}
MicroLL::MicroLL( void )
{
  topObject = &nullObject;
  currentDepth = 0;
  maxDepth = 4;
  nullObject.eventType = -1;

}

//Pass listObject_t to be pushed to the stack (top)
void MicroLL::pushObject( listObject_t & objectToPush )
{
  //This creates a new object, but then forgets the name
  //and doesn't delete the object.
  //
  //If the stack size is too big, new object won't be accepted
  if ( currentDepth < maxDepth )
  {
    //Make a new object to the list
    listObject_t *newObject = new listObject_t;
    Serial.println("\nMADE A NEW LIST ITEM\n");
    //grow list size
    currentDepth++;
	
	//****CUSTOM OBJECT TYPE CODE****//
    //Set the new note's params
    newObject->eventType = objectToPush.eventType;
    newObject->value = objectToPush.value;
	newObject->data = objectToPush.data;
	newObject->channel = objectToPush.channel;
	newObject->timestamp = objectToPush.timestamp;
	
    //Point the top of stack to the new note
    newObject->lowerObject = topObject;
    topObject = newObject; //equals the address of the new note
  }

}

//returns listObject_t
listObject_t MicroLL::popObject( void )
{
  //Target note variable
  listObject_t * objectToDestroy;

  if (currentDepth > 0) //If there are any objects in the list, go on
  {
    objectToDestroy = topObject;
    //move top pointer
    topObject = objectToDestroy->lowerObject;
    //destruct topObject by topStack
    delete objectToDestroy;
    Serial.println("\nDESTROYED A NOTE\n");
    currentDepth--;

    //If depth now == 0, point top to null
    if (currentDepth == 0)
    {
      topObject = &nullObject;
    }
  }

  return *topObject;
}

//returns listObject_t
listObject_t MicroLL::peekObject( void )
{
  listObject_t * objectToReturn;
  objectToReturn = topObject;
  return *objectToReturn;
}

//returns listObject_t
listObject_t MicroLL::peekObject( listDepth_t inputDepth ) //position 0 = top
{
  listObject_t * objectToReturn;

  if (inputDepth < maxDepth) //Prevent out of range peeks
  {
    objectToReturn = topObject;
    //Iterate to the depth
    for ( uint8_t i = 0; i < inputDepth; i++ )
    {
      objectToReturn = objectToReturn->lowerObject;
    }
  }
  else
  {
    objectToReturn = &nullObject;
  }
  return *objectToReturn;
}

//Pass position, returns void
void MicroLL::dropObject( listDepth_t depthToDrop )
{
  //Check depth
  if ( depthToDrop == 0 )
  {
    //If depth is 0 and there is a note on top, pop it
    if (topObject != &nullObject)
    {
      popObject();
    }

  }
  else if ( depthToDrop >= currentDepth )
  {
    //Too deep!  Do nothing.
  }
  else
  {
    //Ok, good to do it.

    //pointer for note above note to drop
    listObject_t * objectAbove = topObject;
    //pointer for note to drop
    listObject_t * objectToDrop;
    //go to the depth above the one to drop
    for (uint8_t i = 0; i < (depthToDrop - 1); i++ )
    {
      objectAbove = objectAbove->lowerObject;
    }
    //point the note to drop
    objectToDrop = objectAbove->lowerObject;
    //Redirect the note above
    objectAbove->lowerObject = objectToDrop->lowerObject;//objectToDrop->lowerObject;
    //Drop it like it's hot
    delete objectToDrop;
    Serial.println("\nDROPPED AN ITEM\n");
    currentDepth--;
  }

}

int8_t MicroLL::seekObjectbyTimeStamp( listObject_t & ) //pass listObject_t, returns position
{
	return 0;
}

int8_t MicroLL::seekObjectbyNoteValue( listObject_t & noteToSeek ) //pass listObject_t, returns position
{
  //Create temporary note to use for comparison
  listObject_t * tempObject;
  tempObject = topObject;
  int8_t returnVar = -1;

  for (uint8_t i = 0; i < currentDepth; i++)
  {
    //****CUSTOM OBJECT TYPE CODE****//
    //For now, only use the value
    if ( tempObject->value == noteToSeek.value )
    {
      returnVar = i;
    }
    //Walk down into the stack
    tempObject = tempObject->lowerObject;
  }
  return returnVar;
}

//returns depth of stack.
listDepth_t MicroLL::listDepth( void )
{
  return currentDepth;
}

//printfs the stack
void MicroLL::printfMicroLL( void )
{
  listObject_t * tempObject;
  long output;
  tempObject = topObject;
  Serial.println("\n Pos, timestamp, type, channel, value, data, address");
  Serial.println(  "-------------------------");
  //Iterate to the depth
  for ( uint8_t i = 0; i < currentDepth; i++ )
  {
    Serial.print(" ");
    Serial.print(i);
    Serial.print(", ");
    Serial.print(tempObject->timestamp);
    Serial.print(", ");
    Serial.print(tempObject->eventType);
    Serial.print(", ");
    Serial.print(tempObject->channel);
    Serial.print(", ");
    Serial.print(tempObject->value);
    Serial.print(", ");
    Serial.print(tempObject->data);
    Serial.print(", ");
    output = (long)tempObject;
    Serial.println(output, HEX);
    
    //move note
    tempObject = tempObject->lowerObject;

  }
}

