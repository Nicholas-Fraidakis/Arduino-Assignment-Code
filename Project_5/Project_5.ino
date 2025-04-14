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

#include <Servo.h>

// Globally allocate a servo
Servo leServo;

// The potentimeter pin
#define POT_PIN A0

void setup() {
  // Zeros the servo (not nessary but good practice)
  memset(&leServo, 0, sizeof(leServo));

  // Attaches to the servo at D9
  leServo.attach(9);

  Serial.begin(9600);
}

void loop() {
  // Reads the potentiometer
  int potVal = analogRead(POT_PIN);

  // Normalizes the reading to 0-179
  int angle = map(potVal, 0, 1023, 0, 179);

  // Sends angle to the servo motor
  leServo.write(angle);

  // We wait 15ms so we don't blow the thing up ;)
  delay(15);
}
