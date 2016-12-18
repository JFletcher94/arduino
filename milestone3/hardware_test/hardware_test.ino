void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
}

void loop() {
  delay(1000);
  Serial.print(analogRead(A5));
  Serial.print(" | ");
  Serial.print(analogRead(A4));
  Serial.print(" | ");
  Serial.print(analogRead(A3));
  Serial.print(" | ");
  Serial.print(analogRead(A2));
  Serial.println("");

}
