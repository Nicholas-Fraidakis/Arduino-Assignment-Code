/*
  This project is made public under the zlib License

  Copyright (c) 2025 Nicholas Fraidakis

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

void SetLongViaMsg(long * target, const char * msg, long min, long max) {
  Serial.print("SetLongViaMsg Prompt: ");
  Serial.println(msg);

  delay(100);

  *target = Serial.parseInt();

  
  *target = *target > max ? max : *target;
  *target = *target < min ? max : *target;
  
  Serial.println(*target);
}

long controlPin[2] = {2, 3};
long enablePin = 9;
long directionSwitchPin = 4;
long onOffSwitchStateSwitchPin = 5;
long potPin = A0;

void parsePins(void) {
  SetLongViaMsg(
    controlPin, 
    "Enter target first control pin, Is Digital Pin Number, [Enter 2 if unsure]",
    0, 13
  );

  SetLongViaMsg(
    controlPin+1, 
    "Enter target second control pin, Is Digital Pin Number, [Enter 3 if unsure]",
    0, 13
  );

  SetLongViaMsg(
    &enablePin, 
    "Enter target enabled pin, Is Digital Pin Number, [Enter 9 if unsure]",
    0, 13
  );

  SetLongViaMsg(
    &directionSwitchPin, 
    "Enter target direction switch pin, Is Digital Pin Number, [Enter 4 if unsure]",
    0, 13
  );

  SetLongViaMsg(
    &onOffSwitchStateSwitchPin, 
    "Enter target on and off switch state switch pin, Is Digital Pin Number, [Enter 5 if unsure]",
    0, 13
  );

  SetLongViaMsg(
    &potPin, 
    "Enter target potentiometer pin, Is Analog Pin Number, [Enter 0 if unsure]",
    0, 5
  );

  potPin += A0;
}

void setupTargetedPins(void) {
  //parsePins();

  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(controlPin[0], OUTPUT);
  pinMode(controlPin[1], OUTPUT);
  pinMode(enablePin, OUTPUT);

  digitalWrite(enablePin, LOW);
}
void setup() {
  Serial.begin(9600);
  delay(100);

  setupTargetedPins();
}


void loop() {
  static int previouslyOn = 0;
  static int previousDirection = 0;
  static bool motorEnabled = 0;

  uint8_t isOn = digitalRead(onOffSwitchStateSwitchPin);

  delay(1);

  enum DIRECTIONS { LEFT=0, RIGHT=1 }; 
  
  enum DIRECTIONS direction = (enum DIRECTIONS) digitalRead(directionSwitchPin);

  int motorSpeed = analogRead(potPin)>>2;


  if (isOn != previouslyOn && isOn == HIGH) {
    motorEnabled = !motorEnabled;
  }

  switch (direction) {
    case LEFT:
      digitalWrite(controlPin[0], LOW);
      digitalWrite(controlPin[1], HIGH);
      break;
    case RIGHT:
      digitalWrite(controlPin[0], HIGH);
      digitalWrite(controlPin[1], LOW);
      break;
  }

  analogWrite(enablePin, motorEnabled ? motorSpeed : 0);

  previousDirection = direction;

  previouslyOn = isOn;
}
