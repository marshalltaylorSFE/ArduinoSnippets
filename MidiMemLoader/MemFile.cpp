#include "stdint.h"
#include "MemFile.h"

MemFile::MemFile(uint8_t* head, uint8_t* end, int size )
{
	fileStartPointer = head;
	fileEndPointer = end;
	fileSize = size;
	fileReadPointer = fileStartPointer;
	
}

uint8_t  MemFile::get( void )
{
	uint8_t returnValue = *fileReadPointer;
	if(fileReadPointer <= fileEndPointer)
	{
		fileReadPointer++;
	}
	
	return returnValue;
}

uint8_t  MemFile::peek( void )
{
	uint8_t returnValue = *fileReadPointer;
	return returnValue;
}

uint8_t  MemFile::eof( void )
{
	uint8_t returnValue = 0;
	
	if(fileReadPointer > fileEndPointer)
	{
		returnValue = 1;
	}
	else
	{
		returnValue = 0;
	}
	
	return returnValue;
}

void MemFile::read(char* input, int size)
{
	for( int i = 0; i < size; i++ )
	{
		*input = get();
		input++;
	}	

}