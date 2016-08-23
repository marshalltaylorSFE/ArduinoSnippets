#include <Wire.h>

#define latchClockPin 2
#define nResetPin 3
#define nOutputEnablePin 4

// Global variables

void setup()
{
	delay(1000);
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Started");
  digitalWrite(nResetPin, 1);
  digitalWrite(nOutputEnablePin, 0);
  Wire.beginTransmission(0xF0); // transmit to device #8
  Wire.write(0xFE);
  Wire.write(0xFD);
  Wire.write(0xFB);
  Wire.write(0xF7);
  Wire.write(0xEF);
  Wire.write(0xDF);
  Wire.write(0xBF);
  Wire.endTransmission();    // stop transmitting
  digitalWrite(latchClockPin, 1);
  delay(10);
  digitalWrite(latchClockPin, 0);
   Serial.println("End of Begin"); 
}

void loop()
{
	delay(1000);
  Wire.beginTransmission(0xF0); // transmit to device #8
  Wire.write(0xFE);
  Wire.write(0xFD);
  Wire.write(0xFB);
  Wire.write(0xF7);
  Wire.write(0xEF);
  Wire.write(0xDF);
  Wire.write(0xBF);
  Wire.endTransmission();    // stop transmitting
  digitalWrite(latchClockPin, 1);
  delay(10);
  digitalWrite(latchClockPin, 0);
   Serial.println("End of Begin"); 
}