#include <EEPROM.h>

char waitFor(char *k, int size, unsigned int pollTime=200, unsigned long timeOut=60e6) {
  //can wait for multiple inputs
  unsigned long timeNow = micros();
  char c = 0;
  int i = 0;
  for(;;) {
    delayMicroseconds(pollTime);
    if (Serial.available()) c = Serial.read();
    if (c == k[i]) return c;
    if (micros() - timeNow > timeOut) return 0;
    if (++i >= size) i = 0;
  }
}

byte* eRead(int size=EEPROM.length(), int address=0) {
  //read EEPROM; all memory read as byte array
  if (size > EEPROM.length() - address) return 0;
  byte data[EEPROM.length()];
  for (int i = 0; i < size; i++) {
    data[i] = EEPROM.read(i+address);
  }
  return data;
}

bool eWrite(byte *data, int size, int address=0) {
  //write to EEPROM
  if (size - address > EEPROM.length()) return false;
  for (int i = 0; i < size; i++) {
    EEPROM.write(i+address, data[i]);
  }
  return true;
}

void eClear() {
  //clear EEPROM ("empty" value is 255)
  Serial.begin(9600);
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 255);
  }
}

void serReadStr() {
  //read string from serial. Format:
  //<x|x|...> 
  //x represents 16 characters
  Serial.println("ser read start");
  delay(100);
  eClear();
  String str = "";
  char c = "";
  while (c != '<') {
    if (Serial.available()) c = Serial.read();
  }
  while (c != '>') {
    if (Serial.available()) {
      c = Serial.read();
      if (c == '|') Serial.print('K');
      else str += c;
    }
  }
  int len = str.length() - 1;
  byte data[len];
  for (int i = 0; i < len; i++) {
    data[i] = (byte) str[i];
  }
  eWrite(data, len); //temporary, for milestone 1
}

void serWriteStr() {
  //print string to Serial
  byte *data = eRead();
  String str = strFromByteArray(data);
  str = "<" + str + ">";
  Serial.println(str);
}

String strFromByteArray(byte *data) {
  //get String from byte array;
  //because its main use is EEPROM, string limited
  //to EEPROM.length()
  char data2[EEPROM.length()];
  int i;
  for (i = 0; i < EEPROM.length(); i++) {
    if ((int) data[i] == 255) break;
    data2[i] = (char) data[i];
  }
  data2[i++] = 0;
  String str = ((String)data2).substring(0, i);
  return str;
}

void startup() {
  //"reset" serial communication; read through buffer
  char k[1] = {'?'};
  while (!waitFor(k, 1));
  Serial.println('K');
}

void setup() {
  Serial.begin(9600); 
  pinMode(9, OUTPUT);

  startup();
  
}

void loop() {
  char k[4] = {'P', 'G', 'Q', '?'};
  char c = 0;
  while (c == 0) {
    c = waitFor(k, 4);
  } 
  Serial.print(c);
  Serial.print('K');
  if (c == '?') return; //re-sync communication if necessary
  if (c == 'P') serReadStr();
  else if (c == 'G') serWriteStr();
  startup();

}
