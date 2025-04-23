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

/* 
  D8 is the switch pin so send stuff there is you want
  to Bikini Atol it
*/
#define SWITCHPIN 8

// 1 hour in ms
#define INTERVAL 600000

void setup() {
  Serial.begin(9600);

  // These are where the output
  for (uint8_t i = 2; i < 8; i++) {
    pinMode(i, OUTPUT);
  }

  // These are where the input
  pinMode(SWITCHPIN, INPUT);
}

// Nuke your progress
void reset_timer(uint8_t * led) {
  for (uint8_t i = 2; i < 8; i++) {
    digitalWrite(i, LOW);
  } 

  *led = 2;
}

void loop() {
  // Static variable stuff :)
  static uint32_t previousTime = 0;
  static uint32_t previousState = 0;
  static uint8_t led = 2;

  // The current time in ms
  uint32_t currentTime = millis();

  // Wait an hour pal
  if (currentTime - previousTime > INTERVAL) {
    previousTime = currentTime;

    // Turn that led on
    digitalWrite(led, HIGH);

    led++; // Adds uno to the current led pin

    if (led >= 8) led = 2;
  }

  // Reseting your process shangians

  uint8_t switchState = digitalRead(SWITCHPIN);

  if (switchState != previousState) reset_timer(&led);

  previousState = switchState;

  /*
    No delay, let it overheat >:)
    (in all seriousness, I'm not sure if that would affects millis because it's single threaded,
    and idk how it is implemented on the Arduino)
   */
}
