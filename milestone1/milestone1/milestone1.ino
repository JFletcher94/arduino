#include <EEPROM.h>

bool waitFor(char k, unsigned int pollTime=200, unsigned long timeOut=60e6) {
  unsigned long timeNow = micros();
  char c = 0;
  while (c != k) {
    delayMicroseconds(pollTime);
    if (micros() - timeNow > timeOut) return false;
    if (Serial.available()) c = Serial.read();
  }
  return true;
}

byte* eRead(int size=EEPROM.length(), int address=0) {
  if (size > EEPROM.length() - address) return 0;
  byte data[EEPROM.length()];
  for (int i = 0; i < size; i++) {
    data[i] = EEPROM.read(i+address);
  }
  return data;
}

bool eWrite(byte *data, int size, int address=0) {
  if (size - address > EEPROM.length()) return false;
  for (int i = 0; i < size; i++) {
    EEPROM.write(i+address, data[i]);
  }
  return true;
}

void setup() {
  Serial.begin(9600); 
  pinMode(9, OUTPUT);

  while (!waitFor('?'));
  Serial.println('K');
  delay(2000);
  
}

void loop() {
  

}
