int p = 9; //port
int len = 100; //length of morse unit

void setup() {
  pinMode(p, OUTPUT);
}

void loop() {
  char s[] = "the sixth of january nineteen hundred and ninety four ";
  morse(s);
  delay(len*7);
}

void morse (char *s) {
  int i = 0;
  while (s[i] != 0) {
    letter(s[i++]);
  }
}

void letter(char c) {
  if (c > 64 && c < 90) c += 32;
  if (c == 'a') {
    dot(); dash();
  }
  else if (c == 'b') { 
    dash(); dot(); dot(); dot();
  }
  else if (c == 'c') { 
    dash(); dot(); dash(); dot();
  }
  else if (c == 'd') { 
    dash(); dot(); dot();
  }
  else if (c == 'e') { 
    dot();
  }
  else if (c == 'f') { 
    dot(); dot(); dash(); dot();
  }
  else if (c == 'g') { 
    dash(); dash(); dot(); 
  }
  else if (c == 'h') { 
    dot(); dot(); dot(); dot(); 
  }
  else if (c == 'i') { 
    dot(); dot(); 
  }
  else if (c == 'j') { 
    dot(); dash(); dash(); dash(); 
  }
  else if (c == 'k') { 
    dash(); dot(); dash(); 
  }
  else if (c == 'l') { 
    dot(); dash(); dot(); dot(); 
  }
  else if (c == 'm') { 
    dash(); dash(); 
  }
  else if (c == 'n') { 
    dash(); dot(); 
  }
  else if (c == 'o') { 
    dash(); dash(); dash(); 
  }
  else if (c == 'p') { 
    dot(); dash(); dash(); dot(); 
  }
  else if (c == 'q') { 
    dash(); dash(); dot(); dash(); 
  }
  else if (c == 'r') { 
    dot(); dash(); dot(); 
  }
  else if (c == 's') { 
    dot(); dot(); dot(); 
  }
  else if (c == 't') { 
    dash(); 
  }
  else if (c == 'u') { 
    dot(); dot(); dash(); 
  }
  else if (c == 'v') { 
    dot(); dot(); dot(); dash(); 
  }
  else if (c == 'w') { 
    dot(); dash(); dash(); 
  }
  else if (c == 'x') { 
    dash(); dot(); dot(); dash(); 
  }
  else if (c == 'y') { 
    dash(); dot(); dash(); dash(); 
  }
  else if (c == 'z') { 
    dash(); dash(); dot(); dot(); 
  }
  else if (c == '1') { 
    dot(); dash(); dash(); dash(); dash(); 
  }
  else if (c == '2') { 
    dot(); dot(); dash(); dash(); dash(); 
  }
  else if (c == '3') { 
    dot(); dot(); dot(); dash(); dash(); 
  }
  else if (c == '4') { 
    dot(); dot(); dot(); dot(); dash(); 
  }
  else if (c == '5') { 
    dot(); dot(); dot(); dot(); dot(); 
  }
  else if (c == '6') { 
    dash(); dot(); dot(); dot(); dot(); 
  }
  else if (c == '7') { 
    dash(); dash(); dot(); dot(); dot(); 
  }
  else if (c == '8') { 
    dash(); dash(); dash(); dot(); dot(); 
  }
  else if (c == '9') { 
    dash(); dash(); dash(); dash(); dot(); 
  }
  else if (c == '0') { 
    dash(); dash(); dash(); dash(); dash(); 
  }
  else if (c == ' ') {
    delay(len*4);
  }
  delay(len*2);
}

void dot() {
  digitalWrite(p, HIGH);
  delay(len);
  digitalWrite(p, LOW);
  delay(len);
}

void dash() {
  digitalWrite(p, HIGH);
  delay(len*3);
  digitalWrite(p, LOW);
  delay(len);
}
