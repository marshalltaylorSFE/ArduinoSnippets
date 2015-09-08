#include <MIDI.h>

#include <SoftwareSerial.h>
SoftwareSerial softSerial(2,3);
MIDI_CREATE_INSTANCE(SoftwareSerial, softSerial, midiA);

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
	Serial.print("0x");
    Serial.print(channel, HEX);
	Serial.print(" 0x");
    Serial.print(pitch, HEX);
	Serial.print(" 0x");
    Serial.print(velocity, HEX);
	Serial.print("\n");
	
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
	Serial.print("0x");
    Serial.print(channel, HEX);
	Serial.print(" 0x");
    Serial.print(pitch, HEX);
	Serial.print(" 0x");
    Serial.print(velocity, HEX);
	Serial.print("\n");
	
}

void setup()
{
	pinMode(3, OUTPUT);
	Serial.begin(9600);
	midiA.turnThruOn();
    midiA.setHandleNoteOn(handleNoteOn);  // Put only the name of the function
    midiA.setHandleNoteOff(handleNoteOff);

    // Initiate MIDI communications, listen to all channels
    midiA.begin(MIDI_CHANNEL_OMNI);
}

void loop()
{
    midiA.read();
}