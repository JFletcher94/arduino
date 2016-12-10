int p = 9; //port

void setup() {
  pinMode(p, OUTPUT);
}

void loop() {
  digitalWrite(p, 0);
  delay(1000);
  digitalWrite(p, 1);
  delay(1000);
  digitalWrite(p, 2);
  delay(1000);
  digitalWrite(p, 4);
  delay(1000);
  digitalWrite(p, 8);
  delay(1000);
  digitalWrite(p, 16);
  delay(1000);
  digitalWrite(p, 32);
  delay(1000);
  digitalWrite(p, 64);
  delay(1000);
  digitalWrite(p, 128);
  delay(1000);
  digitalWrite(p, 255);
  delay(1000);
}

