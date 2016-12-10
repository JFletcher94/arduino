int p = 9; //LED pin
int b = 255; //LED brightness

void setup() {
  Serial.begin(9600);
  pinMode(p, OUTPUT);
  analogWrite(p, b);

  unsigned long t0 = micros();
  unsigned int Vs[512];
  for (int i = 0; i < 512; i++) {
    Vs[i] = analogRead(A0);
  }
  unsigned long t1 = micros();
  Serial.println("time:");
  Serial.println(t1 - t0);
  for (int i = 0; i < 512; i++) {
    Serial.println(Vs[i]);
  }
}

void loop() {
}
