#include <EEPROM.h>

void setup() {
  Serial.begin(9600);
  int size = EEPROM.length();
  char data[size];
  for (int i = 0; i < size; i++) {
    data[i] = (char) EEPROM.read(i);
  }
  Serial.print(data);
}

void loop() {
  // put your main code here, to run repeatedly:

}
