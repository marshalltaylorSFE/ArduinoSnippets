// SPI Slave Demo
//
// Slave toggles slave LED upon receipt of cmdBtn master command code.
//
// Communication Protocol:
// Slave acknowledges SS (Slave Select) by sending -1 slave response code and receiving 
// master command code. On subsequent SS slave sends master command code or -1 slave 
// response code indicating an unrecognized command has been received. Additional SS's 
// may be needed to transfer additional data to/from Slave depending on the master command
// code.
//
// Master command codes:
// cmdBtn.
// Inform slave of a master button press.
//
// SPI pin numbers:
// SCK   13  // Serial Clock.
// MISO  12  // Master In Slave Out.
// MOSI  11  // Master Out Slave In.
// SS    10  // Slave Select
#define SSalt 8

// Include SPI (Serial Peripheral Interface) library. Does not support SPI Slave.
#include <SPI.h>
boolean SSlast = LOW;         // SS last flag.
//Initialize SPI slave.
void SlaveInit(void) {
  // Initialize SPI pins.
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, INPUT);
  pinMode(SSalt, INPUT);
  // Enable SPI as slave.
  SPCR = (1 << SPE);
}
// SPI Transfer.
byte SPItransfer(byte value) {
  SPDR = value;
  while(!(SPSR & (1<<SPIF)));
  delay(10);
  return SPDR;
}
// The setup() function runs after reset.
void setup() {
  // Initialize serial for troubleshooting.
  Serial.begin(57600);
  // Initialize SPI Slave.
  SlaveInit();
  Serial.println("Slave Initialized");
}
// The loop function runs continuously after setup().
void loop() {
  // Slave Enabled?
  if (!digitalRead(SSalt)) {
    // Yes, first time?
    if (SSlast != LOW) {
      // Yes, take MISO pin.
      pinMode(MISO, OUTPUT);
      // Write -1 slave response code and receive master command code
      byte rx = SPItransfer(255);
      Serial.print((char)rx);

      // Update SSlast.
      SSlast = LOW;
    }
  }
  else {
    // No, first time?
    if (SSlast != HIGH) {
      // Yes, release MISO pin.
      pinMode(MISO, INPUT);
      // Update SSlast.
      SSlast = HIGH;
    }
  }
}

