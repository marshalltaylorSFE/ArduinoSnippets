#ifndef ARDFSTREAM_H
#define ARDFSTREAM_H

class ardfstream
{
  public:
  ardfstream(void);//Construct object and optionally open file (public member function )
  void open();//Open file (public member function )
  void open(const char* s, int);
  int is_open();//Check if a file is open (public member function )
  void close();//Close file (public member function )
  //rdbuf();//Get the associated filebuf object (public member function )
  //operator= //Move assignment (public member function )
  //swap(); //Swap internals (public member function )
  
  int get(void);
  int peek(void);
  int eof(void);
  int read(char* input, int size);
  
  };
#endif

class FakeFile
{
  public:
  FakeFile();
  int get(void);
  int peek(void);
  int eof(void);
  int read(char* input, int size);
  

}