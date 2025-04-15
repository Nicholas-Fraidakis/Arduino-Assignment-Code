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

int sensorHigh = 0;
int sensorLow = 1023;

uint8_t piezoPin = 8;
uint8_t photoPin = A0;

void setup() {
  Serial.begin(9600);
  while (Serial.available() != 0);


  // Proper wait time
  unsigned long start_time = millis();

// Calibration time
#define CAL_TIME 5000

  int sensorValue = 0;

  // Calibration
  while (millis() - start_time < CAL_TIME) {
    sensorValue = analogRead(photoPin);

    sensorHigh = sensorValue > sensorHigh ? 
                  sensorValue : sensorHigh;

    sensorLow = sensorValue < sensorLow ? 
                  sensorValue : sensorLow;
  }

}

void loop() {
  int sensorValue = analogRead(photoPin);

  int pitch =
    map(sensorValue, sensorLow, sensorHigh, 50, 4000);

  tone(piezoPin, pitch, 20);

  delay(10);
}
