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
MicroLL::MicroLL( listIdemNumber_t inputNumber )
{
  startObjectPtr = &nullObject;  //start pointed to null note
  currentPosition = 0 ;  //Size 0
  maxLength = inputNumber;  //set max size
  nullObject.eventType = 0xAA;  //define null note

}
MicroLL::MicroLL( void )
{
  startObjectPtr = &nullObject;
  currentPosition = 0;
  maxLength = 50;
  nullObject.eventType = 0xAA;
  

}

//Pass listObject_t to be pushed to the stack (top)
void MicroLL::pushObject( listObject_t & objectToPush )
{
  //This creates a new object, but then forgets the name
  //and doesn't delete the object.
  //
  //If the stack size is too big, new object won't be accepted
  if ( currentPosition < maxLength )
  {
    //Make a new object to the list
    listObject_t *newObject = new listObject_t;
    Serial.print("\nMADE A NEW LIST ITEM\n");
	
    //Point the start to the new note if this is the first one
	if( currentPosition == 0 )
	{
	  startObjectPtr = newObject;
	}
	else
	{
	  //Otherwise set the previous note to this new address
	  listObject_t * previousObjectPtr = readObject( currentPosition - 1 );
	  previousObjectPtr->nextObject = newObject;
	}

    //grow list size
    currentPosition++;
	
	//****CUSTOM OBJECT TYPE CODE****//
    //Set the new note's params
    newObject->eventType = objectToPush.eventType;
    newObject->value = objectToPush.value;
	newObject->data = objectToPush.data;
	newObject->channel = objectToPush.channel;
	newObject->timeStamp = objectToPush.timeStamp;
	
    newObject->nextObject = &nullObject;
    
  }

}

// //returns listObject_t
// listObject_t MicroLL::popObject( void )
// {
  // //Target note variable
  // listObject_t * objectToDestroy;

  // if (currentPosition > 0) //If there are any objects in the list, go on
  // {
    // objectToDestroy = nextObject;
    // //move top pointer
    // nextObject = objectToDestroy->nextObject;
    // //destruct nextObject by topStack
    // delete objectToDestroy;
    // Serial.println("\nDESTROYED A NOTE\n");
    // currentPosition--;

    // //If depth now == 0, point top to null
    // if (currentPosition == 0)
    // {
      // nextObject = &nullObject;
    // }
  // }

  // return *nextObject;
// }

// //returns listObject_t
// listObject_t MicroLL::readObject( void )
// {
  // listObject_t * objectToReturn;
  // objectToReturn = nextObject;
  // return *objectToReturn;
// }

//returns listObject_t
listObject_t * MicroLL::readObject( listIdemNumber_t inputNumber ) //position 0 = top
{
  listObject_t * objectToReturn;

  if (inputNumber < maxLength) //Prevent out of range peeks
  {
    objectToReturn = startObjectPtr;
    //Iterate to the depth
    for ( uint8_t i = 0; i < inputNumber; i++ )
    {
      objectToReturn = objectToReturn->nextObject;
    }
  }
  else
  {
    objectToReturn = &nullObject;
  }
  return objectToReturn;
}

//Pass position, returns void
void MicroLL::dropObject( listIdemNumber_t positionToDrop )
{
  //pointer for object to drop
  listObject_t * objectToDrop;
  listObject_t * tempObjectPtr;

  if ( positionToDrop >= currentPosition )
  {
    //Too deep!  Do nothing.
  }
  else
  {
    //Ok, good to do it.
	//Go to the object before positionToDrop
    if ( positionToDrop == 0 )
    {
		//Save the start object
		objectToDrop = startObjectPtr;
  	
		//Move startObjectPtr
		startObjectPtr = startObjectPtr->nextObject;
    }
    else
	{
		//go to the position before the one to drop
		tempObjectPtr = startObjectPtr;
		for (uint8_t i = 0; i < (positionToDrop - 1); i++ )
		{
			tempObjectPtr = tempObjectPtr->nextObject;
		}
		//Point out the drop target
		objectToDrop = tempObjectPtr->nextObject;
		//move the older object to skip
		tempObjectPtr->nextObject = objectToDrop->nextObject;
	}
    //Drop it like it's hot
    delete objectToDrop;
    Serial.println("\nDROPPED AN ITEM\n");
    currentPosition--;
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
  tempObject = startObjectPtr;
  int8_t returnVar = -1;

  for (uint8_t i = 0; i < currentPosition; i++)
  {
    //****CUSTOM OBJECT TYPE CODE****//
    //For now, only use the value
    if ( tempObject->value == noteToSeek.value )
    {
      returnVar = i;
    }
    //Walk down the list
    tempObject = tempObject->nextObject;
  }
  return returnVar;
}

//returns depth of stack.
listIdemNumber_t MicroLL::listLength( void )
{
  return currentPosition;
}

//printfs the stack
void MicroLL::printfMicroLL( void )
{
  listObject_t * tempObject;
  long output;
  tempObject = startObjectPtr;
  Serial.println("\n Pos, timeStamp, type, channel, value, data, address, nextObjectAddress");
  Serial.println(  "-------------------------");
  //Iterate to the depth
  for ( uint8_t i = 0; i < currentPosition; i++ )
  {
    Serial.print(" ");
    Serial.print(i);
    Serial.print(", ");
    Serial.print(tempObject->timeStamp);
    Serial.print(", 0x");
    Serial.print(tempObject->eventType, HEX);
    Serial.print(", ");
    Serial.print(tempObject->channel);
    Serial.print(", ");
    Serial.print(tempObject->value);
    Serial.print(", ");
    Serial.print(tempObject->data);
    Serial.print(", ");
    output = (long)tempObject;
    Serial.print(output, HEX);
    Serial.print(", ");
    output = (long)tempObject->nextObject;
    Serial.println(output, HEX);    
    //move note
    tempObject = tempObject->nextObject;

  }
}

