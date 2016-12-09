float Pmax = -0.0075;
float Imax = -0.001;

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
  
  float Vset = 690.;
  float P = Pmax/10.;
  float out = 0.;
  float I = Imax/10.;
  float es = 0.;

  int kmax = 200;
  float Vs[kmax];
  float outs[kmax];
  for (int k = 0; k < kmax; k++) {
    analogWrite(9, out);
    delay(100);
    float  V = getPhoto(30, 136);
    Vs[k] = V;
    float e = Vset - V;
    es += e;
    out = P*e + I*es;
    if (out < 0) out = 0;
    else if (out > 255) out = 255;
    outs[k] = out;
  }
  
  while (!waitFor('g'));
  Serial.println('K');
  delay(2000);
  
  for (int i = 0; i < kmax; i++) {
    Serial.println(Vs[i]);
  }

  while (!waitFor('g'));
  Serial.println('K');
  delay(5000);
    
  for (int i = 0; i < kmax; i++) {
    Serial.println(outs[i]);
  }
}

void loop() {
  

}
