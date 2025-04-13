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

// Pin constants
#define gLEDPin 9
#define rLEDPin 10
#define bLEDPin 11

// Settings
bool DebugPrint = false;

// Setting up pins D9-11 as output pins and initizling them
void setup() 
{
  Serial.begin(9600);
  while (!Serial);

  // Sets D9-11 to output
  pinMode(rLEDPin, OUTPUT);
  pinMode(gLEDPin, OUTPUT);                                                                                                                                       
  pinMode(bLEDPin, OUTPUT);

  // Sets D9-11 to be LOW
  analogWrite(rLEDPin, LOW);
  analogWrite(gLEDPin, LOW);
  analogWrite(bLEDPin, LOW);

  delay(500);

  // If you want you can enable debug printing
  Serial.println("\n\n\nEnter 1 if you want to enable debug print!");
  Serial.println("Enter anything else if not!");

  // Waits for serial to be ready
  while (!Serial.available());

  if (Serial.parseInt() == 1) DebugPrint = true;

}

// Holds the sensor values for A0-2
int SVal[3] = {0};

// Holds the RGB values that will be written to D9-11
int Val[3] = {0};

// Handler function to easily modify any of the RGB arrays (type int[3])
void HandleRGBArray(int * target, void (*RGBAdjustFunc)(int * target, int pin), int startPin)
{
  for (int i = 0; i < 3; i++)
  {
    RGBAdjustFunc(target + i, i + startPin);
  }
}

// Creates a function that HandleRGBArray can use
#define RGBArrayFunc(name) void name (int * target, int pin)

// HandleRGBArray function - Reads all the sensors and outputs them to SVal
RGBArrayFunc(readSensors)
{
  *target = analogRead(pin);
  delay(5);
}

// HandleRGBArray function - Processes SVal and outputs to Val
RGBArrayFunc(setEpekValue)
{
  // Gets the index value based off getting the difference of the target and Val's mem address
  // This works because we know at comp-time that we will only 
  uint8_t index = (uint32_t)(target - Val);

  // Safety check to avoid memory errors
  if (index >= 3)
  {
    Serial.println("WARNING: You can only use setEpekValue with the target being Val!");
    Serial.println("         Otherwise you the index can not be determined at comp-time");
    Serial.println("         And this will result in reading outside the SVal array!");
    Serial.println("         TO AVOID UNSAFE CODE, EXECUTION HAS BEEN HALTED, PLEASE FIX THIS ERROR!");

    exit(EXIT_FAILURE); // Crashes programs on purpose to avoid bugs
  }

  // Reads the sensor and divides by 4 (a bit-shift of 2 does the same thing but faster)
  *target = SVal[index] >> 2;
}

// Writes Val to D9-11
RGBArrayFunc(setPins)
{
  analogWrite(pin, *target);

  if (DebugPrint)
  {
    // You can see the what D_ be
    Serial.print("Value ");
    Serial.print(*target);
    Serial.print(" At Pin D");
    Serial.println(pin);
  }
}

void loop()                                                                                                                                                                                  
{ 
  // Uses the handler to read the light sensors
  HandleRGBArray(SVal, readSensors, A0);
  
  // Uses the handler to calculate the RGB values
  HandleRGBArray(Val, setEpekValue, 9);

  // Uses the handler to set pins D9-11
  HandleRGBArray(Val, setPins, 9);
}
