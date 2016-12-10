#include <EEPROM.h>

char waitFor(char *k, int size, unsigned int pollTime=200, unsigned long timeOut=60e6) {
  unsigned long timeNow = micros();
  char c = 0;
  int i = 0;
  while (c != k[i]) {
    delayMicroseconds(pollTime);
    if (Serial.available()) c = Serial.read();
    if (micros() - timeNow > timeOut) return 0;
    if (++i >= size) i = 0;
  }
  return k[i];
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

void eClear() {
  Serial.begin(9600);
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 255);
  }
}

void serReadStr() {
  eClear();
  String str = Serial.readString();
  int len = str.length();
  byte data[len];
  for (int i = 0; i < len; i++) {
    data[i] = (byte) str[i];
  }
  eWrite(data, len);
}

void serWriteStr() {
  byte *data = eRead();
  char data2[EEPROM.length()];
  int i;
  for (i = 0; i < EEPROM.length(); i++) {
    if ((int) data[i] == 255) break;
    data2[i] = (char) data[i];
  }
  data2[i++] = 0;
  String str = ((String)data2).substring(0, i);
  Serial.println(str);
}

void setup() {
  Serial.begin(9600); 
  pinMode(9, OUTPUT);

  char k[1] = {'?'};
  while (!waitFor(k, 1));
  Serial.println('K');
  delay(2000);
  
}

void loop() {
  char k[2] = {'P', 'G'};
  char c = 0;
  do {
    c = waitFor(k, 2);
  } while (c == 0);
  Serial.println('K');
  delay(2000);
  if (c == 'P') serReadStr();
  else if (c == 'G') serWriteStr();

}
