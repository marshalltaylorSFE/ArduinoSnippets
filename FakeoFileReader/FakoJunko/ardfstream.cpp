#include "ardfstream.h"

ardfstream::ardfstream(void)//Construct object and optionally open file (public member function )
{
}

void ardfstream::open()//Open file (public member function )
{
}
void ardfstream::open(const char* s, int mode)
{
}

int ardfstream::is_open()//Check if a file is open (public member function )
{
	return 0;
}

void ardfstream::close()//Close file (public member function )
{
}

//rdbuf();//Get the associated filebuf object (public member function )
//operator= //Move assignment (public member function )
//swap(); //Swap internals (public member function )

int  ardfstream::get( void )
{
	return 0;
}

int  ardfstream::peek( void )
{
	return 0;
}

int  ardfstream::eof( void )
{
	return 0;
}

int ardfstream::read(char* input, int size)
{
	return 0;
}


FakeFile::FakeFile()
{
}
int  FakeFile::get( void )
{
	return 0;
}

int  FakeFile::peek( void )
{
	return 0;
}

int  FakeFile::eof( void )
{
	return 0;
}

int FakeFile::read(char* input, int size)
{
	return 0;
}