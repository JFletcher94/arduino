
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

float getPhoto(int na = 15, int dta = 136) {
  int n; 
  unsigned long dt;
  float vS = 0;

  for (n = 0, dt = micros(); n < na; n++) {
    while (micros() - dt < dta);
    dt = micros();
    vS += analogRead(A0);
  }
  return (vS/na);
}

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  
  while (!waitFor('?'));
  Serial.println('K');
  delay(2000);
  unsigned int Vs[256];
  for (int outV = 0; outV < 256; outV++) {
    analogWrite(9, outV);
    delay(100);
    Vs[outV] = getPhoto();
  }
  
  while (!waitFor('g'));
  Serial.println('K');
  delay(2000);
  for (int i = 0; i < 256; i++) {
    Serial.println(Vs[i]);
  }
}

void loop() {
  

}
