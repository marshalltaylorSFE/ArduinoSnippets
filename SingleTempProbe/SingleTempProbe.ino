/**************** MAX31855K_Thermocouple_Digitizer_Example.ino *****************
*                                                                             *
* MAX31855K Thermocouple Breakout Example Code                                *
* brent@sparkfun.com                                                          *
* March 26th 2015                                                             *
* https://github.com/sparkfun/MAX31855K_Thermocouple_Digitizer                *
*                                                                             *
* Use the "serial monitor" window to read a temperature sensor.               *
*                                                                             *
* Circuit:                                                                    *
* MAX31855K breakout attached to the following pins                           *
*  SS:   pin 10                                                               *
*  MOSI: pin 11 (NC)                                                          *
*  MISO: pin 12                                                               *
*  SCK:  pin 13                                                               *
*  VCC:  pin 14                                                               *
*  GND:  pin 15                                                               *
*                                                                             *
*                                                                             *
* Development environment specifics:                                          *
* 1.6.4                                                                       *
* Arduino Pro Mini 328 3.3V/8MHz                                              *
*                                                                             *
* This code is beerware; if you see me (or any other SparkFun employee) at    *
* the local, and you've found our code helpful, please buy us a round!        *
* Distributed as-is; no warranty is given.                                    *
******************************************************************************/

#include <SparkFunMAX31855k.h> // Using the max31855k driver
#include <SPI.h>  // Included here too due Arduino IDE; Used in above header
#include <stdint.h>
#include "HOS_char.h"

// Define SPI Arduino pin numbers (Arduino Pro Mini)
// SCK & MISO are defined by Arduiino
const uint8_t VCC = 14; // Powering board straight from Arduino Pro Mini
const uint8_t GND = 15;
uint16_t globalCounter = 0;
float probe1Offset = 0;

// Instantiate an instance of the SparkFunMAX31855k class
SparkFunMAX31855k probe1(10, VCC, GND);
//SparkFunMAX31855k probe2(3, VCC, GND);
//SparkFunMAX31855k probe3(4, VCC, GND);
//SparkFunMAX31855k probe4(5, VCC, GND);

float temperature;
float temperatureRaw;


void setup() {
	Serial.begin(9600);
	Serial.println("\nBeginning...");
	Serial.println("\nEnter a temperature in the form of '12.34' to set the current temperature.  Two dot two characters, no more or less");
	delay(50);  // Let IC stabilize or first readings will be garbage
}

void loop() {

	// Read methods return NAN if they don't have a valid value to return.
	// The following conditionals only print the value if it's not NAN.
	//temperature = probe1.readCJT();
	//if (!isnan(temperature))
	//{
	//	Serial.print("CJT is (˚C): ");
	//	Serial.println(temperature);
	//}

	// Read the temperature in Celsius
	Serial.print(globalCounter);
	Serial.print(",");
	
	// Read the temperature in Celsius
	temperatureRaw = probe1.readTempC();
	temperature = temperatureRaw + probe1Offset;
	if (!isnan(temperature))
	{
		Serial.print(temperature);
		//Serial.print(",");
		Serial.print("\n");
	}
	int i = 0;
	char rxData[6];
	uint8_t newDataFlag = 0;
	while(Serial.available())
	{
		rxData[i] = Serial.read();
		if(i < 5) i++;
		newDataFlag = 1;
	}
	if(newDataFlag)
	{
		float targetTemp = char2hex(rxData[1]) + (char2hex(rxData[0]) * 10) + ((float)char2hex(rxData[4]) + ((float)char2hex(rxData[3]) * 10))/100;
		probe1Offset = targetTemp - temperatureRaw;
		Serial.println(targetTemp);
		Serial.println("New calibration applied!");
		
	}

//	// Read the temperature in Celsius
//	temperature = probe2.readTempC();
//	if (!isnan(temperature))
//	{
//		Serial.print(temperature);
//		Serial.print(",");
//	}
//
//	// Read the temperature in Celsius
//	temperature = probe3.readTempC();
//	if (!isnan(temperature))
//	{
//		Serial.print(temperature);
//		Serial.print(",");
//	}
//
//	// Read the temperature in Celsius
//	temperature = probe4.readTempC();
//	if (!isnan(temperature))
//	{
//		Serial.print(temperature);
//		Serial.print("\n");
//	}

	globalCounter = globalCounter + 5;

	delay(5000);
}