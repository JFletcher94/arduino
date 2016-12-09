#include <EEPROM.h>

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 255);
  }
  Serial.print("EEPROM cleared");
}

void loop() {
  // put your main code here, to run repeatedly:

}
