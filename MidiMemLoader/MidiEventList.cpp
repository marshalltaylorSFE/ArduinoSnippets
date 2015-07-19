//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sat Feb 14 21:55:38 PST 2015
// Last Modified: Sat Feb 14 21:55:40 PST 2015
// Filename:      midifile/src-library/MidiEventList.cpp
// Website:       http://midifile.sapp.org
// Syntax:        C++11
// vim:           ts=3 expandtab
//
// Description:   A class which stores a MidiEvents for a MidiFile track.
//


#include "MidiEventList.h"

#include <vector>
#include <iostream>

using namespace std;


//////////////////////////////
//
// MidiEventList::MidiEventList -- Constructor.
//

MidiEventList::MidiEventList(void) {
   reserve(1000);
}



//////////////////////////////
//
// MidiEventList::~MidiEventList -- Deconstructor.  Deallocate all stored
//   data.
//

MidiEventList::~MidiEventList() {
   clear();
}



//////////////////////////////
//
// MidiEventList::operator[] --
//

MidiEvent&  MidiEventList::operator[](int index) {
   return *list[index];
}



//////////////////////////////
//
// MidiEventList::back -- Return the last element in the list.
//

MidiEvent& MidiEventList::back(void) {
   return *list.back();
}

// Alias for back:

MidiEvent& MidiEventList::last(void) {
   return back();
}



//////////////////////////////
//
// MidiEventList::getEvent -- The same thing as operator[], for 
//      internal use when operator[] would look more messy.
//   

MidiEvent& MidiEventList::getEvent(int index) {
     return *list[index];
}



//////////////////////////////
//
// MidiEventList::clear -- De-allocate any MidiEvents present in the list
//    and set the size of the list to 0.
//

void MidiEventList::clear(void) {
   for (int i=0; i<list.size(); i++) {
      if (list[i] != NULL) {
         delete list[i];
         list[i] = NULL;
      }
   }
   list.resize(0);
}



//////////////////////////////
//
// MidiEventList::data --
//

MidiEvent** MidiEventList::data(void) {
   return list.data;
}



//////////////////////////////
//
// MidiEventList::reserve --  Pre-allocate space in the list for storing
//     elements.
//

void MidiEventList::reserve(int rsize) {
   if (rsize > list.size()) {
      list.reserve(rsize);
   }
}


//////////////////////////////
//
// MidiEventList::getSize --
//

int MidiEventList::getSize(void) {
   return list.size();
}


int MidiEventList::size(void) {
   return getSize();
}



//////////////////////////////
//
// MidiEventList::append -- add a MidiEvent at the end of the list.  Returns
//     the index of the appended event.
//

int MidiEventList::append(MidiEvent& event) { 
   MidiEvent* ptr = new MidiEvent(event);
   list.push_back(ptr);
   return list.size()-1;
}


int MidiEventList::push(MidiEvent& event) { 
   return append(event);
}


int MidiEventList::push_back(MidiEvent& event) { 
   return append(event);
}


///////////////////////////////////////////////////////////////////////////
//
// protected functions --
//


//////////////////////////////
//
// MidiEventList::detach -- De-allocate any MidiEvents present in the list
//    and set the size of the list to 0.
//


void MidiEventList::detach(void) {
   list.resize(0);
}



//////////////////////////////
//
// MidiEventList::push_back_no_copy -- add a MidiEvent at the end of 
//     the list.  The event is not copied, but memory from the 
//     remote location is used.  Returns the index of the appended event.
//

int MidiEventList::push_back_no_copy(MidiEvent* event) { 
   list.push_back(event);
   return list.size()-1;
}




