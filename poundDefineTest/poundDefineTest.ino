void setup() {
  // Wait 2 seconds
  delay(5000);
  Serial.begin(9600);
#ifdef AVR
  Serial.println("AVR defined");
#else
  Serial.println("AVR not defined");
#endif

#ifdef __AVR__
  Serial.println("__AVR__ defined");
#else
  Serial.println("__AVR__ not defined");
#endif

#ifdef ARM
  Serial.println("ARM defined");
#else
  Serial.println("ARM not defined");
#endif

#ifdef __MK20DX256__
  Serial.println("__MK20DX256__ defined");
#else
  Serial.println("__MK20DX256__ not defined");
#endif
}

void loop() {
  // put your main code here, to run repeatedly:

}
