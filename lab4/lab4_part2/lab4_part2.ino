

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

int p = 9; //LED pin
int b = 128; //LED brightness

void setup() {
  Serial.begin(9600);
  pinMode(p, OUTPUT);
  while (!waitFor('?'));
  Serial.print('K');
  analogWrite(p, b);
}

void loop() {
  while (!waitFor('g'));
  unsigned long t0 = micros();
  unsigned int Vs[512];
  for (int i = 0; i < 512; i++) {
    Vs[i] = analogRead(A0);
  }
  unsigned long t1 = micros();
  Serial.println(t1 - t0);
  for (int i = 0; i < 512; i++) {
    Serial.println(Vs[i]);
  }
}


  /*
  while (!waitFor('?')) {
  }
  Serial.print('K');
  */
