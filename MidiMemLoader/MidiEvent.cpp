//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sat Feb 14 21:40:14 PST 2015
// Last Modified: Sat Feb 14 23:33:51 PST 2015
// Filename:      midifile/src/MidiEvent.cpp
// Website:       http://midifile.sapp.org
// Syntax:        C++11
// vim:           ts=3 expandtab
//
// Description:   A class which stores a MidiMessage and a timestamp
//                for the MidiFile class.
//

#include "MidiEvent.h"
#include <stdlib.h>

using namespace std;


//////////////////////////////
//
// MidiEvent::MidiEvent -- Constructor classes
//

MidiEvent::MidiEvent(void) : MidiMessage() {
   clearVariables();
}


MidiEvent::MidiEvent(int command) : MidiMessage(command)  {
   clearVariables();
}


MidiEvent::MidiEvent(int command, int p1) : MidiMessage(command, p1) {
   clearVariables();
}


MidiEvent::MidiEvent(int command, int p1, int p2) 
      : MidiMessage(command, p1, p2) {
   clearVariables();
}


MidiEvent::MidiEvent(int aTime, int aTrack, vector<uchar>& message)
      : MidiMessage(message) {
   tick  = aTime;
   track = aTrack;
   eventlink = NULL;
}


MidiEvent::MidiEvent(const MidiEvent& mfevent) {
   tick  = mfevent.tick;
   track = mfevent.track;
   eventlink = NULL;
   this->resize(mfevent.size());
   for (int i=0; i<this->size(); i++) {
      (*this)[i] = mfevent[i];
   }
}



//////////////////////////////
//
// MidiEvent::~MidiEvent -- MidiFile Event destructor
//

MidiEvent::~MidiEvent() {
   tick  = -1;
   track = -1;
   this->resize(0);
   eventlink = NULL;
}


//////////////////////////////
//
// MidiEvent::clearVariables --  Clear everything except MidiMessage data.
//

void MidiEvent::clearVariables(void) {
   tick  = 0;
   track = 0;
   seconds = 0.0;
   eventlink = NULL;
}


//////////////////////////////
//
// MidiEvent::operator= -- Copy the contents of another MidiEvent.
//

MidiEvent& MidiEvent::operator=(MidiEvent& mfevent) {
   if (this == &mfevent) {
      return *this;
   }
   tick  = mfevent.tick;
   track = mfevent.track;
   eventlink = NULL;
   this->resize(mfevent.size());
   for (int i=0; i<this->size(); i++) {
      (*this)[i] = mfevent[i];
   }
   return *this;
}


MidiEvent& MidiEvent::operator=(MidiMessage& message) {
   if (this == &message) {
      return *this;
   }
   clearVariables();
   this->resize(message.size());
   for (int i=0; i<this->size(); i++) {
      (*this)[i] = message[i];
   }
   return *this;
}


MidiEvent& MidiEvent::operator=(vector<uchar>& bytes) {
   clearVariables();
   this->resize(bytes.size());
   for (int i=0; i<this->size(); i++) {
      (*this)[i] = bytes[i];
   }
   return *this;
}


MidiEvent& MidiEvent::operator=(vector<char>& bytes) {
   clearVariables();
   setMessage(bytes);
   return *this;
}


MidiEvent& MidiEvent::operator=(vector<int>& bytes) {
   clearVariables();
   setMessage(bytes);
   return *this;
}



