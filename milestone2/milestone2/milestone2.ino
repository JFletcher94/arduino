#include <EEPROM.h>
const int EELEN = EEPROM.length();

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

byte* eRead(int size=EELEN, int address=0) {
  //read EEPROM; all memory read as byte array
  if (size > EELEN - address) return 0;
  byte data[EELEN];
  for (int i = 0; i < size; i++) {
    data[i] = EEPROM.read(i+address);
  }
  return data;
}

bool eWrite(byte *data, int size, int address=0) {
  //write to EEPROM
  if (size - address > EELEN) return false;
  eClear();
  for (int i = 0; i < size; i++) {
    EEPROM.write(i+address, data[i]);
  }
  return true;
}

void eClear() {
  //clear EEPROM ("empty" value is 255)
  for (int i = 0; i < EELEN; i++) {
    EEPROM.write(i, 255);
  }
}

String serReadStr() {
  //read string from serial. Format:
  //{x|y|...} 
  //x, y represent 16 characters
  delay(100);
  String str = "";
  char c = 0;
  while (c != '{') {
    if (Serial.available()) c = Serial.read();
  }
  while (c != '}') {
    if (Serial.available()) {
      c = Serial.read();
      if (c == '|') Serial.print('K');
      else if (c != '}') str += c;
    }
  }
  return str;
}

void serWriteStr(String str) {
  //prints string to Serial surrounded by { and }
  Serial.print("{" + str + "}");
}

String getEEAsStr() {
  //print string to Serial
  byte *data = eRead();
  char data2[EELEN];
  int i;
  for (i = 0; i < EELEN; i++) {
    if ((int) data[i] == 255) break;
    data2[i] = (char) (data[i] + 32);
  }
  data2[i++] = 0;
  return ((String)data2).substring(0, i);
}

String strFromByteArray(byte *data) {
  //get String from byte array;
  //because its main use is EEPROM, string limited
  //to EEPROM.length()
  char data2[EELEN+1];
  int i;
  for (i = 0; i < EELEN; i++) {
    if ((int) data[i] == 255) break;
    data2[i] = (char) data[i];
  }
  data2[i++] = 0;
  String str = ((String)data2).substring(0, i);
  return str;
}

String encrypt(String str) {
  //encrypt string using Vigenere cipher
  //allowed ASCII range: 32 - 122 (space - z); size: 91
  int len;
  if (str.length() < EELEN) len = str.length();
  else len = EELEN;
  byte cypher[len];
  char encrypted[str.length()+1];
  for (int i = 0; i < len; i++) {
    cypher[i] = random(91);
  }
  for (int i = 0; i < str.length(); i++) {
    encrypted[i] = (str.charAt(i)-32 + cypher[i%len])%91 + 32;
  }
  encrypted[str.length()] = 0;
  eWrite(cypher, len);
  return (String) encrypted;
}

String decrypt(String str) {
  //decrypt string using Vigenere cipher
  //allowed ASCII range: 32 - 122 (space - z); size: 91
  byte *data = eRead();
  int i = 0;
  while (data[i] != 255) {
    i++;
  }
  if (i == 0) return "";
  int len = str.length();
  char decrypted[len+1];
  for (int j = 0; j < len; j++) {
    decrypted[j] = (char)((91 + str.charAt(j)-32 - data[j%i])%91 + 32);
  }
  decrypted[len] = 0;
  return (String) decrypted;
}

void startup() {
  //"reset" serial communication; read through buffer
  char k[1] = {'?'};
  while (!waitFor(k, 1));
  Serial.println('K');
}

void setup() {
  Serial.begin(9600); 
  randomSeed(analogRead(0));
  
  pinMode(9, OUTPUT);
  startup();
  
}

void loop() {
  char k[4] = {'P', 'G', 'Q', '?'};
  char c = 0;
  while (c == 0) {
    c = waitFor(k, 4);
  } 
  Serial.print('K');
  if (c == '?') return; //re-sync communication if necessary
  if (c == 'P') serWriteStr(encrypt(serReadStr()));
  else if (c == 'G') serWriteStr(decrypt(serReadStr()));
  startup();

}
