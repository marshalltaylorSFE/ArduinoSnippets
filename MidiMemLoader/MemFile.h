#ifndef _MEMFILE_H_INCLUDED
#define _MEMFILE_H_INCLUDED

#include "stdint.h"

class MemFile
{
public:
	MemFile(uint8_t* head, uint8_t* end, int size );

	uint8_t get(void);
	uint8_t peek(void);
	uint8_t eof(void);
	void read(char* input, int size);
	
	uint8_t * fileStartPointer;
	uint8_t * fileEndPointer;
	int fileSize;
	uint8_t * fileReadPointer;

};

#endif
