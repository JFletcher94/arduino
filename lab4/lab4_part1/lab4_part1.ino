int p = 9; //LED pin
int b = 255; //LED brightness


bool waitFor(char k, unsigned int pollTime=200, unsigned long timeOut=60e6) {
  unsigned long timeNow = micros();
  char c = 0;
  while (c != k) {
    delayMicroseconds(pollTime);
    if (Serial.available()) c = Serial.read();
    if (micros() - timeNow > timeOut) return false;
  }
  return true;
}

void setup() {
  Serial.begin(9600);
  pinMode(p, OUTPUT);
  
  while (!waitFor('?'));
  
  digitalWrite(p, b);
  Serial.print('K');
}

void loop() {
}

