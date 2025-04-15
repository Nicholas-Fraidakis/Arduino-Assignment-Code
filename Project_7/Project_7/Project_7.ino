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

#define PIEZOPIN 8

void setup() {
  Serial.begin(9600);
}

/*
  Returns true if note is played, false if not,
  Also this is called beep instead of note because
  beep sounds cooler :D
*/
bool beep(void) {
  // Reads the key input
  int keyVal = analogRead(A0);

  Serial.print("Key = ");
  Serial.println(keyVal);

  /*
    This is better in static memory instead of pushing
    it to stack memory every time is wasteful so we use
    statically allocated memory bc that's epic
  */

  // I could have used one array of an anonymous struct instead of three arrays but nah

  static int notes[] = {262, 294, 330, 349};
  static int lower_bounds[] = {1023, 990, 505, 5};
  static int upper_bounds[] = {1023, 1010, 515, 10};

  // Asserts that the size of the notes, lower_bounds, and upper_bounds are equal
  // This is to avoid a unsafe condition bc that would lead to undefined behavior
  static_assert(
    sizeof(lower_bounds) == sizeof(upper_bounds) 
    && sizeof(lower_bounds) == sizeof(notes), 
    "There are amount of notes, upper_bounds, and lower_bounds are unequal!"
  );

  // Checks all upper and lower bounds and plays that note if true
  for (uint8_t i = 0; i < sizeof(lower_bounds) / sizeof(int); i++) {
    
    // If it's not this note we go to the next iteration and keep looking
    if (keyVal < lower_bounds[i] || keyVal > upper_bounds[i]) continue;


    // If we found the note we plays it in D8
    tone(PIEZOPIN, notes[i]);

    return true;
  }

  // The beep ain't beeping
  return false;
}

void loop() {
  if (beep()) return;

  // If no note is played, so the tone is zeroed
  noTone(PIEZOPIN);
}
