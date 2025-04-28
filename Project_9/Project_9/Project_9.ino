#define SWITCHPIN 2
#define MOTORPIN 9

int switchState = 0;

void setup() {
  pinMode(MOTORPIN, OUTPUT);
  pinMode(SWITCHPIN, INPUT);
}

void loop(){
  switchState = digitalRead(SWITCHPIN);

  if (switchState == HIGH) {
  digitalWrite(MOTORPIN, HIGH);
  }
  else {
    digitalWrite(MOTORPIN, LOW);
  }
}